#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "ch03.h"

using namespace std;

void Ch03_00()
{
	Calculator cal;
	cal.Init();
	cout << "3.2 + 2.4 = " << cal.Add(3.2, 2.4) << endl;
	cout << "3.5 / 1.7 = " << cal.Div(3.5, 1.7) << endl;
	cout << "2.2 - 1.5 = " << cal.Sub(2.2, 1.5) << endl;
	cout << "4.9 / 1.2 = " << cal.Div(4.9, 1.2) << endl;
	cal.ShowOpCount();
}

void Ch03_01()
{
	Printer pr;
	pr.SetString("Hello World!");
	pr.ShowString();
	pr.SetString("I love C++");
	pr.ShowString();
}

void Printer::SetString(const char* s)
{
	len = strlen(s);
	if (str != 0)
		delete str;
	str = new char[len + 1];
	strcpy(str, s);
}

void Printer::ShowString()
{
	if (str == 0)
		puts("¹®ÀÚ¿­ ¾øÀ½");
	else
	{
		cout << str << endl;
	}
}

void Calculator::Init(void)
{
	add = 0; sub = 0; mul = 0; div = 0;
}
double Calculator::Add(double x, double y)
{
	++add;
	return x + y;
}
double Calculator::Sub(double x, double y)
{
	++sub;
	return x - y;
}
double Calculator::Mul(double x, double y)
{
	++mul;
	return x * y;
}
double Calculator::Div(double x, double y)
{
	++div;
	return x / y;
}
void Calculator::ShowOpCount()
{
	cout << "µ¡¼À: " << add << ", »¬¼À: " << sub << ", °ö¼À: " << mul << ", ³ª´°¼À: " << div << endl;
}