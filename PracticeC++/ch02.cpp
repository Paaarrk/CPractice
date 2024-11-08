#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include "ch02.h"

using std::cout;
using std::cin;
using std::endl;


void Ch02_00()
{
	// ÂüÁ¶ÀÚ
	int num = 10;
	int* ptr = &num;
	int** dptr = &ptr;

	int& ref = num;
	int*& pref = ptr;
	int**& dpref = dptr;

	cout << num << " = " << ref << endl;
	cout << ptr << " = " << pref << endl;
	cout << dptr << " = " << dpref << endl;
}

void plusone(int& ref)
{
	++ref;
}

void absInt(int& ref)
{
	ref = -ref;
}

void Ch02_01()
{
	int a = 10;
	plusone(a);
	cout << a << endl;
	absInt(a);
	cout << a << endl;
}

void SwapPointer(int*& pref1, int*& pref2)
{
	int* temp = pref1;
	pref1 = pref2;
	pref2 = temp;
}

void Ch02_02()
{
	int num1 = 5;
	int* ptr1 = &num1;
	int num2 = 10;
	int* ptr2 = &num2;
	SwapPointer(ptr1, ptr2);
	cout << *ptr1 << ", " << *ptr2;
}

void Ch02_03()
{
	const int num = 12;
	const int* const ptr = &num;
	const int& ref = num;
	cout << num << *ptr << ref;
}

Point& PntAdder(const Point& p1, const Point& p2)
{
	Point* tmp = new Point;

	tmp->xPos = p1.xPos + p2.xPos;
	tmp->yPos = p1.yPos + p2.yPos;

	return *tmp;
}

void Ch02_04()
{
	Point* p1 = new Point{1, 2};
	Point* p2 = new Point{2, 3};
	Point& ref1 = *p1;
	Point& ref2 = *p2;
	Point& p3 = PntAdder(ref1, ref2);

	cout << p3.xPos << ", " << p3.yPos;
	delete p1;
	delete p2;
	delete &p3;
}

void Ch02_05()
{
	const char* str = "My name is myname";
	char* str2 = new char[strlen(str) + 1];
	strcpy(str2, str);
	cout << str2 << endl;
	char str3[100] = "Your name is your name, ";
	cout << str3 << endl;
	strcat(str3, str2);
	cout << str3 << endl;
	cout << strcmp(str, str2) << endl;
	
}

void Ch02_06()
{
	srand(time(NULL));
	for (int i = 0; i < 5; i++)
		cout << rand() % 100 << endl;
}