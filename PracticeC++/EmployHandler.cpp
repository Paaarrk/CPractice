#define _CRT_SECURE_NO_WARNINGS
#define SIZE 10
#include <iostream>
#include "EmployHandler.h"

using namespace std;



EmployHandler::EmployHandler() : _empNum(0), _capacity(SIZE)
{
	cout << "EmployHandler ������ ȣ��!" << endl;
	_empList = new Employ*[SIZE];
}
void EmployHandler::IncCap()
{
	cout << "������ ����! " << _capacity << " ���� "<<_capacity + SIZE << "��" << endl;
	Employ** temp = new Employ *[_capacity + SIZE];
	cout << "���ּ�: " << _empList << ", �ٲ�� �ּ�: " << temp << endl;
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
	cout << "-----��ü ��� ���-----" << endl;
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
	cout << "�� �޿� ��: " << sum << endl;
}

EmployHandler::~EmployHandler()
{
	cout << "EmployHandler �Ҹ��� ȣ��!" << endl;
	for (int i = 0; i < _empNum; i++)
		delete _empList[i];
	delete _empList;
	cout << "EmployHandler �Ҹ�" << endl;
}