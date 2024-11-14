#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "ch15.h"
using std::cout;
using std::endl;
using std::cin;

void Ch15_00()
{
	Account myAcc("56565-24523", 15000);
	try
	{
		myAcc.Deposit(3000);
		myAcc.Deposit(-400);
	}
	catch (BaseException& expn)
	{
		expn.ShowExceptionInfo();
	}
	myAcc.ShowMyMoney();
	try
	{
		myAcc.Withdraw(3500);
		myAcc.Withdraw(200000);
	}
	catch (BaseException& expn)
	{
		expn.ShowExceptionInfo();
	}
	myAcc.ShowMyMoney();
}