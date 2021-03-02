#pragma once
#define DEL_EL ')'

//структутра токена
struct Tocken
{
	
	int value;
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
			value /= rightValue.value;
			operation = rightValue.operation;
			rightValue.operation = DEL_EL;
			break;
		default:
			std::cerr << "Lol" << std::endl;
			break;
		}
	}
};
