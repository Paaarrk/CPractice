#define _CRT_SECURE_NO_WARNINGS
#include "array2d.h"

Array::Array(int cap) : _cap(cap)
{
	cout << "Array(int)" << this << endl;
	_arr = (int*)malloc(sizeof(int) * (_cap));
}

Array::~Array()
{
	cout << "~Array()" << this << endl;
	free(_arr);
}

void Array::BoundCheck(int idx) const
{
	if (idx < 0 || idx >= _cap)
	{
		cout << "Bound of Exception" << endl;
		exit(1);
	}
}
int& Array::operator[](int idx)
{
	cout << "operator[]" << endl;
	BoundCheck(idx);
	return _arr[idx];
}
int Array::operator[](int idx) const
{
	BoundCheck(idx);
	return _arr[idx];
}
ostream& operator<<(ostream& os, const Array& ref)
{
	os << "[ ";
	for (int i = 0; i < ref._cap; i++)
	{
		os << ref[i] << ' ';
	}
	os << ']';
	return os;
}

Array2D::Array2D(int cap, int n) :_cap(cap)
{
	cout << "Array2D(int)" << endl;
	arr = new ArrayPtr[cap];
	for (int i = 0; i < _cap; i++)
		arr[i] = new Array(n);
}
Array2D::~Array2D()
{
	cout << "~Array2D()" << this << endl;
	for (int i = 0; i < _cap; i++)
		arr[i]->~Array();
	delete arr;
	cout << "Delete Array2D arr" << this << endl;
}
void Array2D::BoundCheck(int idx)const
{
	if (idx < 0 || idx >= _cap)
	{
		cout << "BoundOfException" << endl;
		exit(1);
	}
}
Array& Array2D::operator[](int idx)
{
	BoundCheck(idx);
	return *arr[idx];
}
const Array& Array2D::operator[](int idx) const
{
	BoundCheck(idx);
	return *arr[idx];
}
ostream& operator<<(ostream& os, const Array2D& ref)
{
	os << "[ ";
	for (int i = 0; i < ref._cap; i++)
	{
		os << "[ ";
		for (int j = 0; j < ref[i].getCap(); j++)
		{
			os << ref[i][j] << ' ';
		}
		os << "] ";
	}
	os << ']';
	return os;
}
