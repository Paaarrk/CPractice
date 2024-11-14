#include <iostream>
#include "Point.h"
using namespace std;

ostream& operator<<(ostream& os, Point& p)
{
	os << "[" << p.x << ", " << p.y << "]";
	return os;
}

bool Point::operator==(Point& p)
{
	return ((x == p.x) && (y == p.y));
}