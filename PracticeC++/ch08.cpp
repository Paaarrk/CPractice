#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "ch08.h"
#include "EmployHandler.h"
#include "PermanentWorker.h"
#include "SalesWorker.h"
#include "TemporaryWorker.h"

void Ch08_00()
{
	EmployHandler emp;
	
	for (int i = 0; i < 5; i++)
	{
		emp.AddEmploy(new PermanentWorker("정규직", 150000 + i * 10000));
	}
	for (int i = 0; i < 5; i++)
	{
		emp.AddEmploy((new TemporaryWorker("파트타임", 1, 15000 + i * 1000))->AddWorkTime(i));
	}
	for (int i = 0; i < 5; i++)
	{
		emp.AddEmploy((new SalesWorker("영업직", 150000, 1300000 + 100000 * i, (double)i / 10))->AddSalesResult(i * 100000));
	}

	emp.ShowAllSalaryInfo();
	emp.ShowTotalSalary();
}
