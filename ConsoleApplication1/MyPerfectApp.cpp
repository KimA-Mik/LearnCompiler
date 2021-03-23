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


	for (auto& val : vLines)
		if (isAllCorrect && val.size() > 0) {
			std::cout << "Результат выполнения выражения: " << val << "\n>>";
			std::cout << ProcessString(val) << std::endl << std::endl;
		}
	
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
}

double MyPerfectApp::ProcessString(const std::string& src, int startPos)
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

			std::vector<double> vArgs;
			std::string sNameOfFunc = src.substr(i, length);
			StringToLower(sNameOfFunc);


			// тут короче нужно пропарсить аргументы в скобках
			//мне пока влом

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

	
	////вывод списка токенов
	//std::cout << std::endl;
	//for (auto print : lTockens)
	//	std::cout << print.value << ":" << print.operation << "\t";
	//std::cout << std::endl;
	
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

bool MyPerfectApp::isCharADigit(char src)
{
	return '0' <= src && src <= '9';
}

bool MyPerfectApp::isCharAnOperator(char src)
{
	return src == '+' || src == '-' || src == '*' || src == '/';
}

bool MyPerfectApp::isCharALetter(char src)
{
	return src >= 'A' && src <='Z' || src >= 'a' && src <= 'z';
}

int MyPerfectApp::GetPriority(char action)
{
	switch (action) {
	case '*':
	case '/': return 3;
	case '+':
	case '-': return 2;
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
	for (auto Ch : src) {
		if (Ch <= 'Z' && Ch >= 'A')
			Ch = Ch - ('Z' - 'z');
	}
}
