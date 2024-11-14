#ifndef __CH14_H__
#define __CH14_H__
#include <iostream>
using std::ostream;
using std::cout;
using std::endl;
void Ch14_00();

template <class T>
class ArrayT
{
private:
	T* arr;
	int cap;
	int len;
	ArrayT(ArrayT&);
	ArrayT& operator=(ArrayT<T>&);
public:
	ArrayT(int cap = 10);
	~ArrayT();
	inline bool boundCheck(int) const;
	inline bool boundCheck(int);
	T& operator[](int);
	T operator[](int) const;
	int GetLen() { return len; }
	int GetCap() { return cap; }
	friend ostream& operator<<(ostream& os, const ArrayT<int>& arr)
	{
		os << "[ ";
		for (int i = 0; i < arr.cap; i++)
		{
			os << arr[i] << ' ';
		}
		os << "]";
		return os;
	}
};
// ArrayT
template <class T>
ArrayT<T>::ArrayT(int cap) : len(0), cap(cap)
{
	cout << "ArrayT()" << this << endl;
	arr = new T[cap];
}
template <class T>
ArrayT<T>::~ArrayT()
{
	cout << "~ArrayT()" << this << endl;
	delete []arr;
}
template <class T>
inline bool ArrayT<T>::boundCheck(int idx) const
{
	if (idx < 0 || idx >= cap)
		return false;
	return true;
}
template <class T>
inline bool ArrayT<T>::boundCheck(int idx)
{
	if (idx < 0 || idx >= cap)
		return false;
	return true;
}
template <class T>
T& ArrayT<T>::operator[](int idx)
{
	cout << "operator[]" << endl;
	if (boundCheck(idx))
	{
		return arr[idx];
	}
	else {
		cout << "Bound of Exception" << endl;
		exit(1);
	}
}
template <class T>
T ArrayT<T>::operator[](int idx) const
{
	cout << "operator[] const" << endl;
	if (boundCheck(idx))
	{
		return arr[idx];
	}
	else {
		cout << "Bound of Exception" << endl;
		exit(1);
	}
}




#endif