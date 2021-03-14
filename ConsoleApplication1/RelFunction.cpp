#include "RelFunction.h"



double RelFunction::Execute(std::vector<double>& data)
{
	return 0.0;
}

void RelFunction::ProcessDataString(std::string& Src)
{

}


double SinFunc::Execute(std::vector<double>& data) {
	if (data.size() == 1)
		return sin(data[0]);
	else return 0;
}


double CosFunc::Execute(std::vector<double>& data) {
	if (data.size() == 1)
		return cos(data[0]);
	else return 0;
}



double SinDegreeFunc::Execute(std::vector<double>& data)
{
	if (data.size() == 1)
		return sin(data[0] * PI / 180);
	else return 0;
}



double CosDegreeFunc::Execute(std::vector<double>& data)
{
	if (data.size() == 1)
		return cos(data[0] * PI / 180);
	else return 0;
}

double MaxFunc::Execute(std::vector<double>& data)
{
	if (data.size() == 2)
		return (data[0] > data[1]) ? data[0] : data[1];
	else return 0;
}
