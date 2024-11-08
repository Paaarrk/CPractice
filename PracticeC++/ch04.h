#ifndef __CH04_H__
#define __CH04_H__
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
void Ch04_00();
void Ch04_01();
void Ch04_02();

class FruitSeller
{
private:
	int APPLE_PRICE;
	int numOfApples;
	int myMoney;
public:
	void InitMemebers(int, int, int);
	int SaleApples(int);
	void ShowSalesResult() const;
};

class FruitBuyer
{
private:
	int myMoney;
	int numOfApples;
public:
	void InitMembers(int);
	void BuyApples(FruitSeller&, int);
	void ShowBuyResult() const;
};
class Point
{
private:
	int xpos, ypos;
public:
	void  Init(int x, int y)
	{
		xpos = x; ypos = y;
	}
	void ShowPointInfo() const
	{
		cout << "[" << xpos << ", " << ypos << "]" << endl;
	}
};

class Circle {
private:
	Point center;
	int rad;
public:
	void Init(Point& p, int r)
	{
		center = p, rad = r;
	}
	void ShowPointInfo() const
	{
		cout << "Center: ";
		center.ShowPointInfo();
		cout << "Radius: " << rad << endl;
	}
	int GetR() const
	{
		return rad;
	}
};

class Ring {
private:
	Circle c1;
	Circle c2;
public:
	void Init(Circle& cr1, Circle& cr2)
	{
		if (cr1.GetR() < cr2.GetR())
		{
			c1 = cr1; c2 = cr2;
		}
		else
		{
			c1 = cr2; c2 = cr1;
		}	
	}
	void ShowPointInfo() const
	{
		cout << "내부 원: " << endl;
		c1.ShowPointInfo();
		cout << "외부 원: " << endl;
		c2.ShowPointInfo();
	}
};
class NameCard
{
private:
	char* _name;
	char* _companyName;
	char* _phoneNum;
	int _tier;
public:
	NameCard(const char* name, const char* companyName, const char* phoneNum, int n) : _tier(n)
	{
		_name = new char[strlen(name) + 1];
		strcpy(_name, name);
		_companyName = new char[strlen(companyName) + 1];
		strcpy(_companyName, companyName);
		_phoneNum = new char[strlen(phoneNum) + 1];
		strcpy(_phoneNum, phoneNum);
		cout << "생성자 호출!: " << _name << endl;
	}
	NameCard(NameCard& ref) : _tier(ref._tier)
	{
		_name = new char[strlen(ref._name) + 2];
		strcpy(_name, ref._name);
		strcat(_name, "+");

		cout << "복사 생성자 호출! 생성결과: " << _name << endl;
		_companyName = new char[strlen(ref._companyName) + 1];
		strcpy(_companyName, ref._companyName);
		//_phoneNum = ref._phoneNum;
		_phoneNum = new char[strlen(ref._phoneNum) + 1];
		strcpy(_phoneNum, ref._phoneNum);
	}
	~NameCard()
	{
		cout << "소멸자 호출!: " << _name << endl;
		delete[] _name;
		delete[] _companyName;
		delete[] _phoneNum;
	}
	void ShowNameCardInfo() const;
};

enum COMP_POS{ CLERK, SENIOR, ASSIST, MANAGER };
#endif