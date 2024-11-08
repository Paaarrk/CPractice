#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "ch09.h"
using std::cout;
using std::endl;

void Ch09_00()
{
	CCC c;
	c.CCCFunc();
}

Base::Base()
{
	cout << "Base() : "<< this << endl;
}

Base::~Base()
{
	cout << "~Base(): " << this<< endl;
}

void Base::BaseFunc()
{
	cout << "BaseFunc()" << this << endl;
}

AAA::AAA()
{
	cout << "AAA()" << endl;
}

AAA::~AAA()
{
	cout << "~AAA()" << endl;
}

BBB::BBB()
{
	cout << "BBB()" << endl;
}

BBB::~BBB()
{
	cout << "~BBB()" << endl;
}
void BBB::BBBFunc()
{
	cout << "BBBFunc() -> ";
	BaseFunc();
}

void AAA::AAAFunc()
{
	cout << "AAAFunc() -> ";
	BaseFunc();
}

CCC::CCC()
{
	cout << "CCC()" << endl;
}

CCC::~CCC()
{
	cout << "~CCC()" << endl;
}

void CCC::CCCFunc()
{
	cout << "CCCFunc -> " << endl;
	BBBFunc();
	AAAFunc();
}