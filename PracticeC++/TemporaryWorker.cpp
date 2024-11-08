#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "TemporaryWorker.h"
using std::cout;
using std::endl;
TemporaryWorker::TemporaryWorker(const char* name, int workTime = 0, int payPerHour = 10000)
	:Employ(name), _workTime(workTime), _payPerHour(payPerHour) {
	cout << "TemporaryWorker ������ ȣ��!: " << this << endl;
}

TemporaryWorker::~TemporaryWorker()
{
	cout << "TemporaryWorker �ı��� ȣ��!: " << this << endl;
}

TemporaryWorker* TemporaryWorker::AddWorkTime(int time)
{
	_workTime += time;
	return this;
}

int TemporaryWorker::GetSalary() const
{
	return _workTime * _payPerHour;
}

void TemporaryWorker::SalaryInfo() const
{
	printf("-------��� ����-------\n");
	cout << "�̸�: " << _name << ", �޿�: " << GetSalary() << endl;
}