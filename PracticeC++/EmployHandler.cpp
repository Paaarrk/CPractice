#define _CRT_SECURE_NO_WARNINGS
#define SIZE 10
#include <iostream>
#include "EmployHandler.h"

using namespace std;



EmployHandler::EmployHandler() : _empNum(0), _capacity(SIZE)
{
	cout << "EmployHandler 생성자 호출!" << endl;
	_empList = new Employ*[SIZE];
}
void EmployHandler::IncCap()
{
	cout << "사이즈 증가! " << _capacity << " 에서 "<<_capacity + SIZE << "로" << endl;
	Employ** temp = new Employ *[_capacity + SIZE];
	cout << "현주소: " << _empList << ", 바뀌는 주소: " << temp << endl;
	for (int i = 0; i < _capacity; i++)
	{
		temp[i] = _empList[i];
	}
	delete _empList;
	_empList = temp; _capacity += 10;
}
void EmployHandler::AddEmploy(Employ* p)
{
	if (_empNum >= _capacity)
	{
		IncCap();
	}
	_empList[_empNum++] = p;
}
void EmployHandler::ShowAllSalaryInfo() const
{
	cout << "-----전체 사원 목록-----" << endl;
	for (int i = 0; i < _empNum; i++)
	{
		_empList[i]->SalaryInfo();
	}
}

void EmployHandler::ShowTotalSalary() const
{
	int sum = 0;
	for (int i = 0; i < _empNum; i++)
		sum += _empList[i]->GetSalary();
	cout << "총 급여 합: " << sum << endl;
}

EmployHandler::~EmployHandler()
{
	cout << "EmployHandler 소멸자 호출!" << endl;
	for (int i = 0; i < _empNum; i++)
		delete _empList[i];
	delete _empList;
	cout << "EmployHandler 소멸" << endl;
}