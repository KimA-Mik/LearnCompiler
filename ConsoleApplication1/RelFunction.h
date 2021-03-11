#pragma once
#include <string>
#include <vector>
#include "Tocken.h"
#define ARG_DEV ','
class RelFunction
{
protected:

	std::vector<double> vAgrs;

	void ProcessDataString(std::string& Src);

public:
	RelFunction();
	virtual ~RelFunction();

	virtual double Execute(std::vector<double>& data);
};

class SinFunc : public RelFunction
{
public:
	SinFunc();
	~SinFunc();
	virtual double Execute(std::vector<double>& data) override;
private:
	
};

class CosFunc : public RelFunction
{
public:
	CosFunc();
	~CosFunc();
	virtual double Execute(std::vector<double>& data) override;
private:

};