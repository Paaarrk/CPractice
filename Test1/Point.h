#ifndef __POINT_H__
#define __POINT_H__
#include <iostream>
using namespace std;
class Point
{
private:
	int x, y;
public:
	Point(int x = 0, int y = 0) :x(x), y(y) { cout << "Point()" << this << endl; }
	Point(const Point& p) : x(p.x), y(p.y) { cout << "Point(&)" << this << endl; }
	~Point() { cout << "~Point()" << this << endl; }
	friend ostream& operator<<(ostream& os, Point& p);
	bool operator==(Point& p);
};

#endif
