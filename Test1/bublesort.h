#ifndef __BUBBLESORT_H__
#define __BUBBLESORT_H__

template <class T>
class Base
{
public:
	virtual bool operator()(T&, T&) const = 0;
};
template <class T1>
class Des : public Base<T1>
{
public:
	virtual bool operator()(T1& a, T1& b) const
	{
		return (a < b);
	}
};
template <class T2>
class Asc : public Base<T2>
{
public:
	virtual bool operator()(T2& a, T2& b) const
	{
		return (a > b);
	}
};

template <typename T3>
void bsort(T3* arr, int len, Base<T3>& s)
{
	for (int i = 0; i < len - 1; i++)
	{
		for (int j = 0; j < len - 1 - i; j++)
		{
			if (s(arr[j], arr[j + 1]))
			{
				T3 temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}

#endif