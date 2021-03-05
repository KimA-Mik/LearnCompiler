#pragma once
#include <string>
#include <vector>
#include "Tocken.h"
class RelFunction
{
protected:

	const char mArgDev = ',';
	std::vector<double> vAgrs;

	void ProcessDataString(std::string& Src);

public:
	RelFunction();
	virtual ~RelFunction();

	virtual double Execute(std::string& data);
};

class SinFunc : public RelFunction
{
public:
	SinFunc();
	~SinFunc();
	virtual double Execute(std::string& data) override;
private:
	
};

class CosFunc : public RelFunction
{
public:
	CosFunc();
	~CosFunc();
	virtual double Execute(std::string& data) override;
private:

};