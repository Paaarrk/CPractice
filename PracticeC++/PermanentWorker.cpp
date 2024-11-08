#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "PermanentWorker.h"
using namespace std;
PermanentWorker::PermanentWorker()
{
	_salary = 0;
}

PermanentWorker::PermanentWorker(const char* name, int salary) : Employ(name), _salary(salary)
{
	cout << "PermanentWorker ������ ȣ��!!: " << this << endl;
}

PermanentWorker::PermanentWorker(const PermanentWorker& ref) : _salary(ref._salary)
{
	cout << "PermanentWorker ��������� ȣ��!!: " << this << endl;
}

PermanentWorker::~PermanentWorker()
{
	cout << "PermanentWorker �Ҹ��� ȣ��!!: " << this << endl;
}

int PermanentWorker::GetSalary() const
{
	return _salary;
}

void PermanentWorker::SalaryInfo() const
{
	printf("-------��� ����-------\n");
	cout << "�̸�: " << _name << ", �޿�: " << _salary << endl;
}