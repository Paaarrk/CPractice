#ifndef __CH13_H__
#define __CH13_H__
#include <iostream>
using std::cout;
using std::endl;
using std::ostream;

void Ch13_00();
void Ch13_01();
void Ch13_02();

class Point
{
private:
	int x; int y;
public:
	Point(int x = 0, int y = 0) :x(x), y(y) {}
	void Info() const { cout << "[" << x << ", " << y << "]" << endl; }
	void SetPos(int x, int y) { this->x = x; this->y = y; }
	Point& operator+=(const Point& p)
	{
		x += p.x; y += p.y;
		return *this;
	}
	friend ostream& operator<<(ostream& os, const Point& p);
};

template <class T>
void SwapData(T& s1, T& s2);

template <class T>
T& sumArray(const T arr[], int len);

template <>
Point& sumArray(const Point arr[], int len);

template <class T>
class SmartPtr
{
private:
	T* posptr;
public:
	SmartPtr(T * ptr) : posptr(ptr) {}
	T& operator*() const { return *posptr; }
	T* operator->() const { return posptr; }
	~SmartPtr() { delete posptr; }
};
#endif
