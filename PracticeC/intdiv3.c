#include "stdiv.h"

Div IntDiv(int num1, int num2)
{
	Div dval;
	dval.q = num1 / num2;
	dval.r = num1 % num2;
	return dval;
}