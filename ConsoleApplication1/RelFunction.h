#pragma once
#include <string>
#include <vector>
#include "Tocken.h"
#define ARG_DEV ','
#define PI 3.14159265 
class RelFunction
{
public:
	RelFunction() {}
	virtual ~RelFunction() {}

	virtual double Execute(std::vector<double>& data) { return 0; }
};

class SinFunc : public RelFunction
{
public:
	SinFunc() {}
	~SinFunc() {}
	virtual double Execute(std::vector<double>& data) override;
};

class CosFunc : public RelFunction
{
public:
	CosFunc() {}
	~CosFunc(){}
	virtual double Execute(std::vector<double>& data) override;
};

class SinDegreeFunc : public RelFunction
{
public:
	SinDegreeFunc(){}
	~SinDegreeFunc(){}
	virtual double Execute(std::vector<double>& data) override;
};

class CosDegreeFunc : public RelFunction
{
public:
	CosDegreeFunc(){}
	~CosDegreeFunc(){}
	virtual double Execute(std::vector<double>& data) override;
};

class MaxFunc : public RelFunction
{
public:
	MaxFunc() {}
	~MaxFunc() {}
	virtual double Execute(std::vector<double>& data) override;
};