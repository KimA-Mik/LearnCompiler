#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include "Tocken.h"
class MyPerfectApp
{
public:
	MyPerfectApp(int argc, char* argv[]);
	~MyPerfectApp();

	int exec();


protected:

	void ParseFile();

	int ProcessString(const std::string& src, int startPos = 0);

	bool isCharADigit(char src);
	bool isCharAnOperator(char src);
	int GetPriority(char action);

	void ClearBuffer(char target[], int size);


	bool isAllCorrect;
	
	std::vector<std::string> vLines;
	std::string nameOfInputFile;

	//на будущее
	//возможно захочу использовать бор
	std::vector<std::string> vUnarOperations = {"-"};

	static const int maxStringSize = 80;
};

