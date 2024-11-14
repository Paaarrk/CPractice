#ifndef __POINT_H__
#define __POINT_H__
#include <iostream>
using namespace std;
class Point
{
private:
	int x, y;
public:
	Point(int x = 0, int y = 0) :x(x), y(y){}
	Point(const Point& p):x(p.x), y(p.y){}
	~Point(){}
	friend ostream& operator<<(ostream& os, Point& p)
	{
		os << "[" << p.x << ", " << p.y << "]";
		return os;
	}
	bool operator==(const Point& p)
	{
		return ((x == p.x) && (y == p.y));
	}
};

#endif
