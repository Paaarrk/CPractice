#ifndef __CH10_H__
#define __CH10_H__
#include <iostream>
using std::ostream;
using std::istream;

void Ch10_00();
void Ch10_01();
void Ch10_02();
void Ch10_03();

class Point
{
private:
	int x, y;
public:
	Point(int, int);
	~Point();
	void ShowPointInfo() const;
	Point& operator+=(const Point&);
	Point& operator-=(const Point&);
	friend Point operator+(const Point&, const Point&);
	friend Point operator-(const Point&, const Point&);
	friend bool operator==(const Point&, const Point&);
	friend bool operator!=(const Point&, const Point&);
	Point& operator++();
	friend Point& operator--(Point&);
	Point& operator-();
	friend Point& operator~(Point&);
	const Point operator++(int);
	friend const Point operator--(Point&, int);
	Point operator*(int n);
	friend Point operator*(int n, Point& ref);
	friend ostream& operator<<(ostream&, const Point&);
	friend istream& operator>>(istream&, Point&);
	Point& operator=(const Point&);
};
#endif
