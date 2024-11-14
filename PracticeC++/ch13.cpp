#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "ch13.h"
using std::cout;
using std::endl;

void Ch13_00()
{
	Point t1(1, 2);
	Point t2(2, 3);
	SwapData<Point>(t1, t2);
	t1.Info(); t2.Info();
	int i1 = 5;
	int i2 = 3;
	SwapData(i1, i2);
	cout << i1 << i2 << endl;
}

void Ch13_01()
{
	Point p[5] = { Point(1,2), Point(2, 3), Point(3, 4), Point(4, 5), Point(5, 6) };
	int arr[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }; 
	Point p2(2);
	cout << p2 << "\n";
	cout << sumArray<Point>(p, 5) << endl;
	cout << sumArray(arr, 10);
}

void Ch13_02()
{
	SmartPtr<Point> sptr1(new Point(4, 5));
	SmartPtr<Point> sptr2(new Point(2, 6));
	sptr1->Info();
	sptr2->Info();
	sptr1->SetPos(10, 20);
	sptr2->SetPos(24, 556);
	sptr1->Info();
	sptr2->Info();
}

template <class T>
void SwapData(T& s1, T& s2)
{
	T temp = s1;
	s1 = s2;
	s2 = temp;
}

template <class T>
T& sumArray(const T arr[], int len)
{
	T sum{};
	for (int i = 0; i < len; i++)
		sum += arr[i];
	return sum;
}

template <>
Point& sumArray(const Point arr[], int len)
{
	cout << "PointÀü¿ë" << endl;
	Point sum{};
	for (int i = 0; i < len; i++)
		sum += arr[i];
	return sum;
}

ostream& operator<<(ostream& os, const Point& p)
{
	os << p.x << ", " << p.y;
	return os;
}