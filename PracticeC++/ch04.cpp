#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "ch04.h"

using namespace std;

void Ch04_00()
{
	FruitSeller s;
	FruitBuyer b;

	s.InitMemebers(1000, 150, 10000);
	b.InitMembers(100000);

	b.BuyApples(s, 10100);
	s.ShowSalesResult();
	b.ShowBuyResult();
}

void Ch04_01()
{
	Ring ring;
	Point p1; p1.Init(1, 1);
	p1.ShowPointInfo();
	Point p2; p2.Init(1, 1);
	Circle c1; c1.Init(p1, 4);
	c1.ShowPointInfo();
	Circle c2; c2.Init(p2, 1);
	c2.ShowPointInfo();
	ring.Init(c1, c2);
	ring.ShowPointInfo();
}

void Ch04_02()
{
	NameCard* manClerk = new NameCard("Lee", "ABC_Eng", "010-2222-3333", COMP_POS::CLERK);
	NameCard* manSenior = new NameCard("Hong", "ABC_Eng", "010-2322-3333", COMP_POS::SENIOR);
	NameCard* womanClerk = new NameCard("Kim", "LIBUT_Eng", "010-2322-3223", COMP_POS::CLERK);
	NameCard* manManager = new NameCard("Park", "NC_Eng", "010-2342-3243", COMP_POS::MANAGER);
	manClerk->ShowNameCardInfo();
	(*manSenior).ShowNameCardInfo();
	womanClerk->ShowNameCardInfo();
	manManager->ShowNameCardInfo();
	delete womanClerk;
	delete manManager;
	delete manClerk;
	delete manSenior;

	//스택에 할당하면 생성 순서의 역순으로 소멸됨 (스택 구조상)
}

void FruitSeller::InitMemebers(int x, int y, int z)
{
	APPLE_PRICE = x; numOfApples = y; myMoney = z;
}

int FruitSeller::SaleApples(int money)
{
	if (money < 0)
	{
		puts("계산 실패");
		return -1;
	}
	int num = money / APPLE_PRICE;
	numOfApples -= num;
	myMoney + money;
	return num;
}

void FruitSeller::ShowSalesResult() const 
{
	cout << "남은 사과: " << numOfApples << endl;
	cout << "판매 수익: " << myMoney << endl;
}

void FruitBuyer::InitMembers(int x)
{
	myMoney = x; numOfApples = 0;
}
void FruitBuyer::BuyApples(FruitSeller& f, int n)
{
	int x = f.SaleApples(n);
	if (x == -1)
		return;
	numOfApples += x;
	myMoney -= n;
}
void FruitBuyer::ShowBuyResult() const
{
	cout << "현재 잔액: " << myMoney << endl;
	cout << "사과 개수: " << numOfApples << endl << endl;
}

void NameCard::ShowNameCardInfo() const
{
	cout << "---회원 정보--- \n";
	cout << "이름: " << _name << endl;
	cout << "회사 이름: " << _companyName << endl;
	cout << "전화 번호: " << _phoneNum << endl;
	switch (_tier)
	{
	case COMP_POS::CLERK:
		cout << "직급: 직원" << endl;
		break;
	case COMP_POS::SENIOR:
		cout << "직급: 주임" << endl;
		break;
	case COMP_POS::ASSIST:
		cout << "직급: 대리" << endl;
		break;
	case COMP_POS::MANAGER:
		cout << "직급: 매니저" << endl;
		break;
	}
}