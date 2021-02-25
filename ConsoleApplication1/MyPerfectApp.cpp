#include "MyPerfectApp.h"

MyPerfectApp::MyPerfectApp(int argc, char* argv[])
{
	isAllCorrect = true;
	
	if (argc > 1)
		nameOfInputFile = argv[1];
	else
		nameOfInputFile = "input.txt";
}

MyPerfectApp::~MyPerfectApp()
{
}

int MyPerfectApp::exec()
{
	if(isAllCorrect)
		ParseFile();

	for (auto& val : vLines)
		if (isAllCorrect && val.size() > 0)
			std::cout << ProcessString(val) << std::endl;
	
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

int MyPerfectApp::ProcessString(const std::string& src, int startPos)
{
	std::list <Tocken> lTockens;

	//флаг того, что у нас уже есть число и нужно ему найти оператор
	bool isDigitFound = false;

	char buffer[maxStringSize];
	
	int i;

	//проверяем всю строку
	for (i = startPos; i < src.size(); i++) {
		if (isCharADigit(src.at(i))){
			if (isDigitFound) {
				isAllCorrect = false;
				std::cerr << "incorrect mathematical expression" << std::endl;
				return INT_MAX;
			}
			
			//длина числа в символах
			int length = 1;
			while (i + length < src.size() && isCharADigit(src.at(i + length)))
				length++;
			ClearBuffer(buffer, maxStringSize);
			src.copy(buffer, length, i);
			i += length - 1;
			isDigitFound = true;
		}

		if (isCharAnOperator(src.at(i))) {
			if (!isDigitFound) {
				isAllCorrect = false;
				std::cerr << "incorrect mathematical expression" << std::endl;
				return INT_MAX;
			}
			else {
				lTockens.push_back({ std::atoi(buffer), src.at(i) });
				isDigitFound = false;
			}
		}

		if (src.at(i) == '(') {
			if (isDigitFound) {
				isAllCorrect = false;
				std::cerr << "incorrect mathematical expression" << std::endl;
				return INT_MAX;
			}

			int val = ProcessString(src, i + 1);

			strcpy_s(buffer, std::to_string(val).c_str());
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
			


		if (src.at(i) == ')') {
			break;
		}
	}

	if (isDigitFound)
		lTockens.push_back({ std::atoi(buffer), '\n' });

	int index = 0;

	/*
	* выод списка токенов
	for (auto print : lTockens)
		std::cout << print.value << ":" << print.operation << "\t";
	std::cout << std::endl;
	*/

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
	return 0;
}

void MyPerfectApp::ClearBuffer(char target[], int size)
{
	for (int i = 0; i < size; i++)
		target[i] = 'М';
}
