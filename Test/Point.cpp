#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Point.h"
using std::cout;
using std::endl;
using std::ostream;


Point::Point(int x, int y, const char* n) : x(x), y(y)
{
	if (n == NULL)
		n = "Head";
	name = static_cast<char*>(malloc(sizeof(char) * (strlen(n) + 1)));
	strcpy(name, n);
	cout << "Point() [" << x << ", " << y << "] : " << name << ": " << this << endl;
}
Point::Point(const Point& p) : x(p.x), y(p.y)
{
	name = static_cast<char*>(malloc(sizeof(char) * (strlen(p.name) + 1)));
	strcpy(name, p.name);
	cout << "Point() [" << x << ", " << y << "] : " << name << ": " << this << endl;
}
Point::~Point()
{
	cout << "~Point() [" << x << ", " << y << "] : " << name << ": " << this << endl;
	free(name);
}
ostream& operator<<(ostream& os, const Point& p)
{
	os << "[" << p.x << ", " << p.y << "]";
	return os;
}