#ifndef __CH15_H__
#define __CH15_H__
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using std::cout;
using std::endl;
/*
예외처리
*/
void Ch15_00();

class BaseException
{
private:
public:
	BaseException() { cout << "BaseException()" << this << endl; }
	~BaseException() { cout << "~BaseExcpetion()" << this << endl; }
	virtual void ShowExceptionInfo() const = 0;
};

class DepositException : public BaseException
{
private:
	int reqDep;
public:
	DepositException(int money) :reqDep(money) { cout << "DepositException(int)" << this << endl; }
	~DepositException() { cout << "~DepositException()" << this << endl; }
	virtual void ShowExceptionInfo() const
	{
		cout << "[예외 메시지: " << reqDep << "은 입금 불가]" << endl;
	}
};
class WithDrawException : public BaseException
{
private:
	int balance;
public:
	WithDrawException(int money) :balance(money) { cout << "WithDrawException(int)" << this << endl; }
	~WithDrawException() { cout << "WithDrawException()" << this << endl; }
	virtual void ShowExceptionInfo() const
	{
		cout << "[예외 메시지: 잔액 " << balance << "원, 잔액 부족]" << endl;
	}
};

class Account
{
private:
	char accNum[50];
	int balance;
public:
	Account(const char* acc, int money) : balance(money) { cout << "Account()" << this << endl; strcpy(accNum, acc); }
	~Account() { cout << "~Account()" << this << endl; }
	void Deposit(int money) throw (DepositException)
	{
		cout << "Deposit" << endl;
		if (money < 0)
		{
			//expn 객체 생성
			DepositException expn(money);
			throw expn;	// 임시객체 생성(복사 생성자)
		}
		balance += money;
	}	// expn파괴, 임시객체가 넘어감 
	void Withdraw(int money) throw (WithDrawException)
	{
		cout << "WithDraw" << endl;
		if (money > balance)
			throw WithDrawException(balance);	//바로 임시객체로 초기화, 참조 그대로 넘어감
		balance -= money;
	}
	void ShowMyMoney() const
	{
		cout << "잔고: " << balance << endl << endl;
	}
};

#endif
