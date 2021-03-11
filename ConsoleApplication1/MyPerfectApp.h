#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include "Tocken.h"
#include <memory>
#include <unordered_map>
#include "RelFunction.h"
class MyPerfectApp
{
public:
	MyPerfectApp(int argc, char* argv[]);
	~MyPerfectApp();

	int exec();


protected:

	void ParseFile();

	double ProcessString(const std::string& src, int startPos = 0);

	bool isCharADigit(char src);
	bool isCharAnOperator(char src);
	bool isCharALetter(char src);
	int GetPriority(char action);

	void ClearBuffer(char target[], int size);
	void StringToLower(std::string& src);


	bool isAllCorrect;
	
	std::vector<std::string> vLines;
	std::string nameOfInputFile;

	//на будущее
	std::vector<std::string> vUnarOperations = {"-"};

	static const int maxStringSize = 80;

	std::unordered_map<std::string,std::unique_ptr<RelFunction>> MapOfFuncs;
};

