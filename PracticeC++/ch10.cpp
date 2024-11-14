#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "ch10.h"
using std::cout;
using std::endl;
using std::cin;
using std::ostream;
using std::istream;

void Ch10_00()
{
	Point p1(3, 5);
	Point p2(5, 7);
	Point p3 = p1 + p2;
	p1.ShowPointInfo();
	p3.ShowPointInfo();
	p1 += p2;
	p1.ShowPointInfo();
	p1 -= p2;
	p1.ShowPointInfo();
	cout << (p1 == p2) << endl;
	cout << (p2 != p3) << endl;
}

void Ch10_01()
{
	Point p1 = Point(3, 5);
	p1 = -p1;
	p1.ShowPointInfo();
	p1 = ~p1;
	p1.ShowPointInfo();

	p1++.ShowPointInfo();
	p1.ShowPointInfo();
	p1--.ShowPointInfo();
	p1.ShowPointInfo();
}

void Ch10_02()
{
	Point p1(4, 5);
	p1 = 3 * p1 * 5;
	cout << p1 << endl;
}

void Ch10_03()
{
	Point p0(4, 5);
	Point p1(0, 0);
	Point p2(0, 0);
	cin >> p1 >> p2;
	cout << p1 << ' ' << p2 << endl;
	p2 = p0;
	cout << p2 << endl;
}

Point::Point(int x, int y) : x(x), y(y)
{
	cout << "생성자 호출 " << this << endl;
}
Point::~Point()
{
	cout << "소멸자 호출 " << this << endl;
}
void Point::ShowPointInfo() const
{
	cout << "[" << x << ", " << y << "]" << endl;
}
Point& Point::operator+=(const Point& op2)
{
	x += op2.x; y += op2.y;
	return *this;
}
Point& Point::operator-=(const Point& op2)
{
	x -= op2.x; y -= op2.y;
	return *this;
}
Point operator+(const Point& op1, const Point& op2)
{
	return Point(op1.x + op2.x, op1.y + op2.y);
}
Point operator-(const Point& op1, const Point& op2)
{
	return Point(op1.x - op2.x, op1.y - op2.y);
}
bool operator==(const Point& op1, const Point& op2)
{
	if (op1.x == op2.x && op1.y == op2.y)
		return true;
	else
		return false;
}
bool operator!=(const Point& op1, const Point& op2)
{
	return !(operator==(op1, op2));
}
Point& Point::operator++()
{
	x++; y++;
	return *this;
}
Point& operator--(Point& ref)
{
	ref.x--; ref.y--;
	return ref;
}
Point& Point::operator-()
{
	x = -x; y = -y;
	return *this;
}
Point& operator~(Point& ref)
{
	int temp = ref.x;
	ref.x = ref.y; ref.y = temp;
	return ref;
}
const Point Point::operator++(int)
{
	Point temp(x, y);
	++this->x;
	++this->y;
	return temp;
}
const Point operator--(Point& ref, int)
{
	Point temp(ref.x, ref.y);
	--ref.x; --ref.y;
	return temp;
}
Point Point::operator*(int n)
{
	Point temp(x * n, y * n);
	return temp;
}
Point operator*(int n, Point& ref)
{
	return ref * n;
}
ostream& operator<<(ostream& os, const Point& ref)
{
	os << '[' << ref.x << ", " << ref.y << ']';
	return os;
}
istream& operator>>(istream& is, Point& ref)
{
	is >> ref.x >> ref.y;
	return is;
}
Point& Point::operator=(const Point& ref)
{
	x = ref.x; y = ref.y;
	return *this;
}