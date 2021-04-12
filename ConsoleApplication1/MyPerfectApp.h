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
#include <Windows.h>
#include "PreprocessMethods.h"
class MyPerfectApp
{
public:
	MyPerfectApp(int argc, char* argv[]);
	~MyPerfectApp();

	int exec();


protected:

	struct BracketZoneData
	{
		int beginIndex;
		int endIndex;
	};

	void ParseFile();

	double ProcessString(const std::string& src, int startPos = 0);

	static bool isCharADigit(char src);
	static bool isCharAnOperator(char src);
	static bool isCharALetter(char src);
	static int GetPriority(char action);
	static int SkipArgs(const std::string& src, int startPos);

	static void ClearBuffer(char target[], int size);
	static void StringToLower(std::string& src);

	static void ExecuteBracketZone(int numOfRepeats, BracketZoneData zoneData, std::vector<std::string>& sourceData);

	static const char OPEN_PREPR_BRACKET = '{';
	static const char CLOSE_PREPR_BRACKET = '}';


	bool isAllCorrect;
	
	std::vector<std::string> vLines;
	std::string nameOfInputFile;

	static const int maxStringSize = 80;

	std::unordered_map<std::string,std::unique_ptr<RelFunction>> MapOfFuncs;
	std::unordered_map<std::string, std::unique_ptr<PreprocessMethod>> MapOfPrep;
};



