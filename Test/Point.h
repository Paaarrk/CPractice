#ifndef __POINT_H__
#define __POINT_H__
#include <iostream>
using std::ostream;

class Point
{
private:
	int x, y;
	char* name;
public:
	Point(int x = 0, int y = 0, const char* = NULL);
	~Point();
	Point(const Point& p);
	friend ostream& operator<<(ostream& os, const Point&);
};

#endif