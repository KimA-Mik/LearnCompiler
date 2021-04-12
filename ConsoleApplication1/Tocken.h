#pragma once
#define DEL_EL ')'
#include <iostream>

//структутра токена
struct Tocken
{
	
	double value;
	char operation;
	
	void Merge(Tocken& rightValue) {
		switch (operation)
		{
		case '+':
			value += rightValue.value;
			operation = rightValue.operation;
			rightValue.operation = DEL_EL;

			break;

		case '-':
			value -= rightValue.value;
			operation = rightValue.operation;
			rightValue.operation = DEL_EL;
			break;

		case '*':
			value *= rightValue.value;
			operation = rightValue.operation;
			rightValue.operation = DEL_EL;
			break;

		case '/':
			if (rightValue.value == 0)
				throw 0;

			value /= rightValue.value;
			operation = rightValue.operation;
			rightValue.operation = DEL_EL;
			break;

		case '>':
			if (value > rightValue.value)
				value = 1;
			else
				value = 0;
			operation = rightValue.operation;
			rightValue.operation = DEL_EL;
			break;
			
		case '<':
			if (value < rightValue.value)
				value = 1;
			else
				value = 0;
			operation = rightValue.operation;
			rightValue.operation = DEL_EL;
			break;

		case '=':
			if (value == rightValue.value)
				value = 1;
			else
				value = 0;
			operation = rightValue.operation;
			rightValue.operation = DEL_EL;
			break;
			

		default:
			std::cerr << "Lol" << std::endl;
			break;
		}
	}
};
