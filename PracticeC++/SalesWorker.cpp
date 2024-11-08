#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "SalesWorker.h"
using std::cout;
using std::endl;


SalesWorker::SalesWorker(const char* name, int salary = 10000, int salesResult = 0, double bonusRatio = 1.0f)
	:PermanentWorker(name, salary), _salesResult(salesResult), _bonusRatio(bonusRatio)
{
	cout << "SalesWorker ������ ȣ��!: " << this << endl;
}
SalesWorker::~SalesWorker()
{
	cout << "SalesWorker �ı��� ȣ��!: " << this << endl;
}
SalesWorker* SalesWorker::AddSalesResult(int res)
{
	_salesResult += res;
	return this;
}
int SalesWorker::GetSalary() const
{
	return PermanentWorker::GetSalary() + (int)(_salesResult * _bonusRatio);
}
void SalesWorker::SalaryInfo() const
{
	PermanentWorker::SalaryInfo();
	cout << "�ǸŽ���: " << _salesResult << ", ����: " << _bonusRatio << endl;
}