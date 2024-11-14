#ifndef __CH15_H__
#define __CH15_H__
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using std::cout;
using std::endl;
/*
����ó��
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
		cout << "[���� �޽���: " << reqDep << "�� �Ա� �Ұ�]" << endl;
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
		cout << "[���� �޽���: �ܾ� " << balance << "��, �ܾ� ����]" << endl;
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
			//expn ��ü ����
			DepositException expn(money);
			throw expn;	// �ӽð�ü ����(���� ������)
		}
		balance += money;
	}	// expn�ı�, �ӽð�ü�� �Ѿ 
	void Withdraw(int money) throw (WithDrawException)
	{
		cout << "WithDraw" << endl;
		if (money > balance)
			throw WithDrawException(balance);	//�ٷ� �ӽð�ü�� �ʱ�ȭ, ���� �״�� �Ѿ
		balance -= money;
	}
	void ShowMyMoney() const
	{
		cout << "�ܰ�: " << balance << endl << endl;
	}
};

#endif
