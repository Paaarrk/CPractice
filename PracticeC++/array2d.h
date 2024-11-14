#ifndef __ARRAY2D_H__
#define __ARRAY2D_H__
#include <iostream>
using std::ostream;
using std::cout;
using std::endl;

class Array
{
private:
	int _cap;
	int* _arr;
	Array(Array&);
	Array& operator=(Array&);
public:
	Array(int cap = 10);
	~Array();
	void BoundCheck(int) const;
	int& operator[](int);
	int operator[](int) const;
	int getCap() const { return _cap; }
	friend ostream& operator << (ostream&, const Array&);
};
typedef Array* ArrayPtr;

class Array2D
{
private:
	int _cap;
	ArrayPtr* arr;
	Array2D(Array2D&);
	Array2D& operator=(Array2D&);

public:
	Array2D(int cap = 10, int n = 10);
	~Array2D();
	void BoundCheck(int) const;
	Array& operator[](int);
	const Array& operator[](int) const;
	friend ostream& operator<<(ostream&, const Array2D&);

};
#endif