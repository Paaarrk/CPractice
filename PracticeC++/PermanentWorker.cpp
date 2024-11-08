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
	cout << "PermanentWorker 생성자 호출!!: " << this << endl;
}

PermanentWorker::PermanentWorker(const PermanentWorker& ref) : _salary(ref._salary)
{
	cout << "PermanentWorker 복사생성자 호출!!: " << this << endl;
}

PermanentWorker::~PermanentWorker()
{
	cout << "PermanentWorker 소멸자 호출!!: " << this << endl;
}

int PermanentWorker::GetSalary() const
{
	return _salary;
}

void PermanentWorker::SalaryInfo() const
{
	printf("-------사원 정보-------\n");
	cout << "이름: " << _name << ", 급여: " << _salary << endl;
}