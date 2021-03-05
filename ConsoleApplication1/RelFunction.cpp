#include "RelFunction.h"

RelFunction::RelFunction()
{
}

RelFunction::~RelFunction()
{
}

double RelFunction::Execute(std::string& data)
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

double SinFunc::Execute(std::string& data) {
	return 0.;
}

CosFunc::CosFunc()
{
}

CosFunc::~CosFunc()
{
}

double CosFunc::Execute(std::string& data) {
	return 0.;
}