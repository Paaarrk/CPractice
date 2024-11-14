#ifndef __CH11_H__
#define __CH11_H__
#include <iostream>
void Ch11_00();
void Ch11_01();
void Ch11_02();
void Ch11_03();
void Ch11_04();
void Ch11_05();


using std::cout;
using std::endl;
using std::ostream;

class Gun
{
	friend class Police;
private:
	char* _name;
	int _bullet;
public:
	Gun();
	Gun(const char*, int);
	Gun(Gun&);
	~Gun();
	Gun& operator=(Gun&);
	int GetBullet();
	void SetBullet(int);
	void ShowInfo() const;
};

class Police
{
private:
	int _handcuffs;
	Gun* pistol;
public:
	Police();
	Police(const char*, int, int);
	Police(int, Gun&);
	~Police();
	Police& operator=(Police&);
	bool Shot();
	void Wasted();
	void ShowInfo() const;
};

class Points
{
private:
	int x, y;
public:
	Points(int x = 0, int y = 0) : x(x), y(y) {};
	void ShowInfo() const { cout << x << ", " << y << endl; }
	void* operator new(size_t size);
	void* operator new[](size_t size);
	void operator delete[](void* adr);
	void operator delete(void* adr);
	friend ostream& operator<<(ostream& os, Points& p)
	{
		os << p.x << ", " << p.y;
		return os;
	}
	~Points() { cout << "~Points()" << endl; }
};

class SmartPointer
{
private:
	Points* sptr;
public:
	SmartPointer(Points* ptr) : sptr(ptr) {}
	~SmartPointer() { delete sptr; }
	Points& operator* () { return *sptr; }
	Points* operator->() { return sptr; }
	
};

class SortRule
{
public:
	virtual bool operator()(int x, int y) const = 0;
};	//true반환은 바꿔 야 할 필요가 있는 것
class Descent : public SortRule
{
public:
	bool operator()(int x, int y) const
	{
		if (x < y)
			return true;
		else
			return false;
	}
};
class Ascent : public SortRule
{
public:
	bool operator() (int x, int y) const
	{
		if (x > y)
			return true;
		else
			return false;
	}
};
class DataStorage
{
private:
	int* arr;
	int idx;
	const int MAX_LEN;
public:
	DataStorage(int MAXLEN) : idx(0), MAX_LEN(MAXLEN)
	{
		arr = new int[MAX_LEN];
	}
	void AddData(int x)
	{
		if (idx >= MAX_LEN)
			return;
		else
			arr[idx++] = x;
	}
	void ShowAllData()const
	{
		cout << "[ ";
		for (int i = 0; i < idx; i++)
		{
			cout << arr[i] << ' ';
		}
		cout << "]";
	}
	void SortData(const SortRule& functor)
	{
		for (int i = 0; i < idx - 1; i++)
		{
			for (int j = 0; j < idx - 1 - i; j++)
			{
				if (functor(arr[j], arr[j + 1]))
				{
					int temp = arr[j];
					arr[j] = arr[j + 1];
					arr[j + 1] = temp;
				}
			}
		}
	}
};
#endif
