#include "MyPerfectApp.h"

MyPerfectApp::MyPerfectApp(int argc, char* argv[])
{
	isAllCorrect = true;
	
	if (argc > 1)
		nameOfInputFile = argv[1];
	else
		nameOfInputFile = "input.txt";

	MapOfFuncs["sin"] = std::make_unique<SinFunc>();
	MapOfFuncs["cos"] = std::make_unique<CosFunc>();
	MapOfFuncs["sindegree"] = std::make_unique<SinDegreeFunc>();
	MapOfFuncs["cosdegree"] = std::make_unique<CosDegreeFunc>();

	MapOfFuncs["max"] = std::make_unique<MaxFunc>();

	MapOfPrep["if"] = std::make_unique<IfMethod>();
	MapOfPrep["for"] = std::make_unique<ForMethod>();

}

MyPerfectApp::~MyPerfectApp()
{
}

int MyPerfectApp::exec()
{
	if(isAllCorrect)
		ParseFile();

	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);

	ExecuteBracketZone(1, { 0,(int)vLines.size() }, vLines);
	
	return 0;
}

void MyPerfectApp::ParseFile()
{
	std::ifstream input(nameOfInputFile);

	isAllCorrect = input.is_open();

	if (!isAllCorrect) {
		std::cerr << "Could not open the input file" << std::endl;
		return;
	}

	
	char inputBuffer[maxStringSize];
	char separator = '\n';
	
	while (!input.eof())
	{
		input.getline(inputBuffer, maxStringSize, separator); 
		vLines.push_back(inputBuffer);
	}

	input.close();

	//почистим пробелы в начале строки
	for (auto curLine = 0; curLine < vLines.size(); curLine++)
		for (auto curSymbol = 0; curSymbol < vLines[curLine].size(); curSymbol++)
			if (isCharASpace(vLines[curLine][curSymbol])) {
				vLines[curLine].erase(vLines[curLine].begin() + curSymbol);
				curSymbol--;
			}
			else
				break;
		
	

	vLines.push_back("}");
}

double MyPerfectApp::ProcessString(std::string& src, int startPos)
{
	std::list <Tocken> lTockens;

	//флаг того, что у нас уже есть число и нужно ему найти оператор
	bool isDigitFound = false;

	double dBuffer = 0.0;
	
	int i;
	int length = 1;
	//проверяем всю строку
	for (i = startPos; i < src.size(); i++) {
		if (isCharADigit(src.at(i))){
			if (isDigitFound) {
				isAllCorrect = false;
				std::cerr << "The char is a digit but a digit was found" << std::endl;
				return INT_MAX;
			}
			
			//длина числа в символах
			length = 1;
			while (i + length < src.size() && isCharADigit(src.at(i + length)))
				length++;

			dBuffer = std::atof(src.substr(i, length).c_str());
			
			i += length - 1;
			isDigitFound = true;
		}

		if (isCharAnOperator(src.at(i))) {
			if (!isDigitFound) {
				isAllCorrect = false;
				std::cerr << "The char is an operator but a digit was found" << std::endl;
				return INT_MAX;
			}
			else {
				lTockens.push_back({ dBuffer, src.at(i) });
				isDigitFound = false;
			}
		}

		if (isCharALetter(src.at(i))) {
			if (isDigitFound) {
				isAllCorrect = false;
				std::cerr << "The char is a letter but a digit was found" << std::endl;
				return INT_MAX;
			}
			length = 1;

			while (i + length < src.size() && isCharALetter(src.at(i + length)))
				length++;

			std::string sNameOfFunc = src.substr(i, length);
			std::vector<double> vArgs;
			StringToLower(sNameOfFunc);


			int iBraceCount = 1;
			try {
				while (src.at(i + length) != '(')
					length++;

				vArgs.push_back(ProcessString(src, ++length + i));
				while (iBraceCount) {

					if (src.at(length + i) == '(') iBraceCount++;
					else if (src.at(length + i) == ')') iBraceCount--;
					else if (src.at(length + i) == ARG_DEV) vArgs.push_back(ProcessString(src, length + i + 1));
					//пропускаем содержимое скобок функции
					else if (isCharALetter(src.at(length + i))) length = SkipArgs(src, length + i) - i;

					length++;
				}
			}
			catch (std::out_of_range&) {
				isAllCorrect = false;
				std::cerr << "Something with the function arguments went wrong" << std::endl;
				return INT_MAX;
			}

			double dResult;
			try {
				dResult = MapOfFuncs.at(sNameOfFunc)->Execute(vArgs);
			}
			catch (std::out_of_range&) {
				isAllCorrect = false;
				std::cerr << "incorrect function" << std::endl;
				return INT_MAX;
			}

			dBuffer = dResult;

			i += length;
			isDigitFound = true;
		}

		if (i < src.size() && src.at(i) == '(') {
			if (isDigitFound) {
				isAllCorrect = false;
				std::cerr << "An operator was expected, not a brace" << std::endl;
				return INT_MAX;
			}

			double val = ProcessString(src, i + 1);

			dBuffer = val;
			
			isDigitFound = true;

			//пропускаем скобки
			int numOfSKOBOK = 1;
			i++;
			
			while (numOfSKOBOK && i < src.size() - 1){
				if (src.at(i) == '(') numOfSKOBOK++;

				if (src.at(i) == ')') numOfSKOBOK--;
				
				i++;
			}
		}
		
		if (i < src.size()  && (src.at(i) == ')' || src.at(i) == ARG_DEV)) {
			break;
		}
	}

	if (isDigitFound)
		lTockens.push_back({ dBuffer, '\n' });

	int index = 0;	
	
	try {
		while (lTockens.size() > 1) {

			auto begin{ lTockens.begin() };
			auto prevEl{ lTockens.begin() };
			auto end{ lTockens.end() };


			for (auto el{ begin }; el != end; ++el) {
				if (el->operation == DEL_EL) {
					el = lTockens.erase(el);
				}

				if (prevEl != el) {

					if (GetPriority(prevEl->operation) >= GetPriority(el->operation)) {
						prevEl->Merge(*el);
						el = lTockens.erase(el);
						--el;
					}
				}
				
				prevEl = el;

			}
		}
	}
	catch (int iEx) {
		switch (iEx)
		{
		case 0:
			std::cerr << "Attempted to divide by zero" << std::endl;
			break;
		default:
			std::cerr << "An unknown exeption has been occuerd" << std::endl;
			break;
		}
		return INT_MAX;
	}

	return lTockens.begin()->value;
}

void MyPerfectApp::ExecuteBracketZone(int numOfRepeats, BracketZoneData zoneData,
	std::vector<std::string>& sourceData)
{
	try {
		
		
		for (int repeatCount = 0; repeatCount < numOfRepeats; repeatCount++) {

			bool doWeSkip = false;
			int curLine = 0;
			/*
			 * количество не закрытых на данный момент скобок
			 * в нормальном состоянии всегда одна
			 * больше - значит мы в блоке, который нужно пропустить
			 */
			int bracketsCount = 1;
			BracketZoneData tempData{ 0,0 };
			int tempRepeatNum = 0;
			double tempExp = 0.;
			std::string tempMethodName;
			

			/*
			 * этот цикл проходит по всем строкам
			 * ищет ключевые слова блоков
			 * находит - рекурсивно передает управление найденым блоком
			 * с учетом посчитанных данных
			 */
			for (curLine = zoneData.beginIndex; bracketsCount && curLine < zoneData.endIndex; curLine++) {

				doWeSkip = false;
				
				for (auto curCharIndex = 0; curCharIndex < sourceData.at(curLine).size(); curCharIndex++) {

					
					//выделяем ключевые слова и проверяем из вхождение в требуемый перечень
					if (isCharALetter(sourceData.at(curLine).at(curCharIndex))){
						int wordBeginIndex = curCharIndex;
						while ((isCharALetter(sourceData.at(curLine).at(curCharIndex))))
							curCharIndex++;

						tempMethodName = sourceData.at(curLine).substr(wordBeginIndex, curCharIndex - wordBeginIndex);
						StringToLower(tempMethodName);

						if(MapOfPrep.find(tempMethodName) != MapOfPrep.end() && bracketsCount == 1){
							while (sourceData.at(curLine).at(curCharIndex) != '(')
								curCharIndex++;
							tempExp = ProcessString(sourceData.at(curLine), curCharIndex + 1);

							tempRepeatNum = MapOfPrep[tempMethodName]->getRepeatNumber(tempExp);

							doWeSkip = true;
								
						}
					}
					
					if (sourceData.at(curLine).at(curCharIndex) == OPEN_PREPR_BRACKET){
						if (bracketsCount == 1)
							tempData.beginIndex = curLine + 1;
						bracketsCount++;
						doWeSkip = true;
					}

					if (sourceData.at(curLine).at(curCharIndex) == CLOSE_PREPR_BRACKET) {
						if (bracketsCount == 2){
							//не уверен насчет смещения конца блока
							tempData.endIndex = curLine;

							std::cout << "Следующие выражения будут вполены " << tempRepeatNum << " раз\n";
							ExecuteBracketZone(tempRepeatNum, tempData, sourceData);
							std::cout << "Конец выражения, выполнявшегося " << tempRepeatNum << " раз\n\n";
							
							tempRepeatNum = 0;
							tempData = { 0,0 };
						}
						bracketsCount--;
						doWeSkip = true;
						
					}
				}
				

				if (!doWeSkip && isAllCorrect && sourceData.at(curLine).size() > 0 && bracketsCount == 1) {
					std::cout << "Результат выполнения выражения: " << sourceData.at(curLine) << "\n>>";
					std::cout << ProcessString(sourceData.at(curLine)) << std::endl << std::endl;
				}
			}
		}
	}catch (std::out_of_range&)
	{
		std::cerr << "Something went wrong while executing bracket zone\n";
	}
}

bool MyPerfectApp::isCharADigit(char src)
{
	return '0' <= src && src <= '9';
}

bool MyPerfectApp::isCharAnOperator(char src)
{
	return src == '+' || src == '-' || src == '*' || src == '/' || src == '<' || src == '=' || src == '>';
}

bool MyPerfectApp::isCharALetter(char src)
{
	return src >= 'A' && src <='Z' || src >= 'a' && src <= 'z';
}

//пустое пространство,которое нужно очистить
bool MyPerfectApp::isCharASpace(char src) {
	return src == ' ' || src == '\t';
}

int MyPerfectApp::GetPriority(char action)
{
	switch (action) {
	case '*':
	case '/': return 3;
	case '+':
	case '-': return 2;
	case '<':
	case '>':
	case '=': return 1;
	default:
		return 0;
	}
}

int MyPerfectApp::SkipArgs(const std::string& src, int startPos)
{
	int iBraceCount = 1;
	int iResPos = startPos;

	while (src.at(iResPos) != '(')
		iResPos++;

	while (iBraceCount)
	{
		iResPos++;

		if (src.at(iResPos) == '(') iBraceCount++;
		if (src.at(iResPos) == ')') iBraceCount--;
 	}

	return iResPos;
}

void MyPerfectApp::ClearBuffer(char target[], int size)
{
	for (int i = 0; i < size; i++)
		target[i] = 'М';
}

void MyPerfectApp::StringToLower(std::string& src)
{
	for (int chInd = 0; chInd < src.size(); chInd++) {
		if (src[chInd] <= 'Z' && src[chInd] >= 'A')
			src[chInd] -= ('Z' - 'z');
	}
}
