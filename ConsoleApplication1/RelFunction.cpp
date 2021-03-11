#include "RelFunction.h"

RelFunction::RelFunction()
{
}

RelFunction::~RelFunction()
{
}

double RelFunction::Execute(std::vector<double>& data)
{
	return 0.0;
}

void RelFunction::ProcessDataString(std::string& Src)
{

}

SinFunc::SinFunc()
{
}

SinFunc::~SinFunc()
{
}

double SinFunc::Execute(std::vector<double>& data) {
	if (data.size() == 1)
		return sin(data[0]);
	else return 0;
}

CosFunc::CosFunc()
{
}

CosFunc::~CosFunc()
{
}

double CosFunc::Execute(std::vector<double>& data) {
	if (data.size() == 1)
		return cos(data[0]);
	else return 0;
}