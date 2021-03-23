#include "RelFunction.h"



double SinFunc::Execute(std::vector<double>& data) {
	if (data.size() == 1)
		return sin(data[0]);
	return 0;
}


double CosFunc::Execute(std::vector<double>& data) {
	if (data.size() == 1)
		return cos(data[0]);
	return 0;
}


double SinDegreeFunc::Execute(std::vector<double>& data)
{
	if (data.size() == 1)
		return sin(data[0] * PI / 180);
	return 0;
}


double CosDegreeFunc::Execute(std::vector<double>& data)
{
	if (data.size() == 1)
		return cos(data[0] * PI / 180);
	return 0;
}


double MaxFunc::Execute(std::vector<double>& data)
{
	if (!data.empty()) {
		double dMax = data.at(0);
		for (auto Element : data) 
			if (Element > dMax)
				dMax = Element;
		
		return dMax;
	}
	throw -1;
	return 0;
}
