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
	cout << "Employ ������ ȣ��" << this << endl;
	_name = (char*)malloc(sizeof(char) * (strlen(name) + 1));
	strcpy(_name, name);
}

Employ::~Employ()
{
	cout << "Employ �ı��� ȣ��: " << this << endl;
	free(_name);
}