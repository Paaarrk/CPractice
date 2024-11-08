#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Employ.h"
#include "PermanentWorker.h"
using std::cout;
using std::cin;
using std::endl;

Employ::Employ()
{
	_name = NULL;
}
Employ::Employ(const char* name)
{
	cout << "Employ 생성자 호출" << this << endl;
	_name = (char*)malloc(sizeof(char) * (strlen(name) + 1));
	strcpy(_name, name);
}

Employ::~Employ()
{
	cout << "Employ 파괴자 호출: " << this << endl;
	free(_name);
}