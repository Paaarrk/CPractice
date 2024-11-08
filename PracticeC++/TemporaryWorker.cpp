#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "TemporaryWorker.h"
using std::cout;
using std::endl;
TemporaryWorker::TemporaryWorker(const char* name, int workTime = 0, int payPerHour = 10000)
	:Employ(name), _workTime(workTime), _payPerHour(payPerHour) {
	cout << "TemporaryWorker 생성자 호출!: " << this << endl;
}

TemporaryWorker::~TemporaryWorker()
{
	cout << "TemporaryWorker 파괴자 호출!: " << this << endl;
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
	printf("-------사원 정보-------\n");
	cout << "이름: " << _name << ", 급여: " << GetSalary() << endl;
}