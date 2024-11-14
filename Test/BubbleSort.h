#ifndef __BUBBLE_SORT_H__
#define __BUBBLE_SORT_H__

template <class T>
class BaseSort
{
public:
	virtual bool operator()(T&, T&) const = 0;
};

template <class T1>
class DesSort : public BaseSort<T1>
{
public:
	virtual bool operator()(T1& a, T1& b) const
	{
		return (a < b);
	}
};

template <class T2>
class AscSort : public BaseSort<T2>
{
public:
	virtual bool operator() (T2& a, T2& b) const
	{
		return (a > b);
	}
};


template<typename T3>
void Sort(T3* arr, int len, BaseSort<T3>& func)
{
	for (int i = 0; i < len - 1; i++)
	{
		for (int j = 0; j < len - 1 - i; j++)
		{
			if (func(arr[j], arr[j + 1]))
			{
				T3 temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}
#endif