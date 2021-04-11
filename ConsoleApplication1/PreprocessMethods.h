#pragma once
#include <cmath>

class PreprocessMethod {
public:
	PreprocessMethod() = default;
	virtual ~PreprocessMethod() = default;
	virtual int getRepeatNumber(double Arg) { return 0; }
};

class IfMethod : public PreprocessMethod {
public:
	IfMethod() = default;
	~IfMethod() = default;
	int getRepeatNumber(double Arg)override
	{
		if (fabs(Arg) < 0.000001)
			return 0;
		else
			return 1;
	}

};

class ForMethod : public PreprocessMethod {
public:
	ForMethod() = default;
	~ForMethod() = default;
	int getRepeatNumber(double Arg)override
	{
		return (int)fabs(Arg);
	}
};