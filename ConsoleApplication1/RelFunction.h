#pragma once
#include <string>
#include <vector>
#include "Tocken.h"
#define ARG_DEV ','
#define PI 3.14159265 
class RelFunction
{
protected:

	std::vector<double> vAgrs;

	void ProcessDataString(std::string& Src);

public:
	RelFunction() {}
	virtual ~RelFunction() {}

	virtual double Execute(std::vector<double>& data);
};

class SinFunc : public RelFunction
{
public:
	SinFunc() {}
	~SinFunc() {}
	virtual double Execute(std::vector<double>& data) override;
private:
	
};

class CosFunc : public RelFunction
{
public:
	CosFunc() {}
	~CosFunc(){}
	virtual double Execute(std::vector<double>& data) override;
private:

};

class SinDegreeFunc : public RelFunction
{
public:
	SinDegreeFunc(){}
	~SinDegreeFunc(){}
	virtual double Execute(std::vector<double>& data) override;
private:

};

class CosDegreeFunc : public RelFunction
{
public:
	CosDegreeFunc(){}
	~CosDegreeFunc(){}
	virtual double Execute(std::vector<double>& data) override;
private:

};