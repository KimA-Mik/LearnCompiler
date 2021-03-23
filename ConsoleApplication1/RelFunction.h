#pragma once
#include <string>
#include <vector>
#include "Tocken.h"
#define ARG_DEV ','
#define PI 3.14159265 
class RelFunction
{
public:
	RelFunction() = default;
	virtual ~RelFunction() = default;

	virtual double Execute(std::vector<double>& data) { return 0; }
};

class SinFunc : public RelFunction
{
public:
	SinFunc() = default;
	~SinFunc() override = default;
	double Execute(std::vector<double>& data) override;
};

class CosFunc : public RelFunction
{
public:
	CosFunc() = default;
	~CosFunc() override = default;
	double Execute(std::vector<double>& data) override;
};

class SinDegreeFunc : public RelFunction
{
public:
	SinDegreeFunc() = default;
	~SinDegreeFunc() override = default;
	double Execute(std::vector<double>& data) override;
};

class CosDegreeFunc : public RelFunction
{
public:
	CosDegreeFunc() = default;
	~CosDegreeFunc() override = default;
	double Execute(std::vector<double>& data) override;
};

class MaxFunc : public RelFunction
{
public:
	MaxFunc() = default;
	~MaxFunc() override = default;
	double Execute(std::vector<double>& data) override;
};