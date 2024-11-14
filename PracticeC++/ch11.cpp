#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "ch11.h"
#include "array2d.h"
using std::cout;
using std::endl;
using std::cin;

void Ch11_00()
{
	Police p = Police("G18C", 150, 3);
	p.ShowInfo();
	p.Wasted();
	p.ShowInfo();
	Police s;
	s.ShowInfo();
	s = p;
	s.ShowInfo();
}

void Ch11_01()
{
	Array arr;
	for (int i = 0; i < 10; i++)
	{
		arr[i] = i + 10;
	}
	cout << arr << endl;
}

void Ch11_02()
{
	Array2D arr;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			arr[i][j] = 10 * i + j;
		}
	}
	cout << arr << endl;
}

void Ch11_03()
{
	Points* p = new Points(3, 4);
	Points* p2 = new Points[3];
	p->ShowInfo();
	for (int i = 0; i < 3; i++)
		p2[i].ShowInfo();
	delete p;
	delete []p2;
}

void Ch11_04()
{
	// SmartPointer : 동적 할당 객체를 스택을 통해 관리 : 자동 해제
	SmartPointer sp(new Points(3, 1));
	sp->ShowInfo();
}

void Ch11_05()
{
	// Functor : 객체를 함수처럼
	DataStorage storage(5);
	storage.AddData(10);
	storage.AddData(20);
	storage.AddData(30);
	storage.AddData(40);
	storage.AddData(50);

	storage.SortData(Ascent());
	storage.ShowAllData();
	storage.SortData(Descent());
	storage.ShowAllData();
}

Gun::Gun():_bullet(0)
{
	cout << "Gun 기본생성자" << this << endl;
	char str[100];
	cin >> str;
	if (str == 0)
	{
		str[0] = 'N'; str[1] = '\0';
	}
	_name = (char*)malloc(sizeof(char*) * (strlen(str) + 1));
	strcpy(_name, str);
}
Gun::Gun(const char* name, int bullet):_bullet(bullet)
{
	cout << "Gun 세팅생성자" << this << endl;
	_name = (char*)malloc(sizeof(char) * (strlen(name) + 1));
	strcpy(_name, name);
}
Gun::Gun(Gun& ref) : _bullet(ref._bullet)
{
	cout << "Gun 복사생성자" << this << endl;
	_name = (char*)malloc(sizeof(char) * (strlen(ref._name) + 1));
	strcpy(_name, ref._name);
}
Gun::~Gun()
{
	cout << "Gun 소멸자" << this << endl;
	free(_name);
}
Gun& Gun::operator=(Gun& gun)
{
	cout << "Gun 대입 연산자" << this << endl;
	if (strlen(gun._name) != strlen(_name))
	{
		strcpy(_name, gun._name);
		_bullet = gun._bullet;
	}
	else
	{
		char* temp = _name;
		_name = (char*)realloc(_name, sizeof(char)*(strlen(gun._name) + 1));
		if (_name == 0)
			_name = temp;
		else
		{
			strcpy(_name, gun._name);
			_bullet = gun._bullet;
		}
	}
	return *this;
}
int Gun::GetBullet()
{
	return _bullet;
}
void Gun::SetBullet(int n)
{
	_bullet = n;
}
void Gun::ShowInfo() const
{
	cout << "총기 정보: " << _name << ", 총알 수: " << _bullet << endl;
}

Police::Police():_handcuffs(0)
{
	cout << "Police()" << this << endl;
	pistol = new Gun();
}
Police::Police(int cuffs, Gun& pis) : _handcuffs(cuffs)
{
	cout << "Police(int, Gun&)" << this << endl;
	pistol = new Gun(pis);
}
Police::Police(const char* gun, int n, int cuffs): _handcuffs(cuffs)
{
	cout << "Police(char*, int, int)" << this << endl;
	pistol = new Gun(gun, n);
}
Police::~Police()
{
	cout << "~Police()" << endl;
	if (pistol != NULL)
	{
		delete pistol;
	}
}
Police& Police::operator=(Police& ref)
{
	cout << "Police operator=" << this << endl;
	*pistol = *ref.pistol;	//대입연산자 활용을 위해 깊은 복사
	_handcuffs = ref._handcuffs;
	return *this;
}
bool Police::Shot()
{
	if (strcmp(pistol->_name, "N") == 0)
	{
		cout << "총기가 없어요 " << this << endl;
		return false;
	}
	else {
		if (pistol->_bullet == 0)
		{
			cout << "총알이 없어요 " << this << endl;
			return false;
		}
		else
		{
			pistol->SetBullet(pistol->GetBullet() - 1);
			cout << "발사!" << endl;
			return true;
		}
	}
}

void Police::Wasted()
{
	if (Shot())
	{
		if (_handcuffs > 0)
		{
			_handcuffs--;
			cout << "체포 !!" << endl;
		}
		else
		{
			cout << "체포 실패" << endl;
		}
	}
	else
	{
		cout << "체포 실패" << endl;
	}
}

void Police::ShowInfo() const
{
	cout << "경찰 정보: " << this << endl;
	pistol->ShowInfo();
	cout << "수갑 수: " << _handcuffs << endl;
}

void* Points::operator new(size_t size)
{
	cout << "new" << size << endl;
	void* adr = new char[size];
	return adr;
}
void* Points::operator new[](size_t size)
{
	cout << "new[]" << size << endl;
	void* adr = new char[size];
	return adr;
}
void Points::operator delete[](void* adr)
{
	cout << "delete[]" << endl;
	delete []adr;
}
void Points::operator delete(void* adr)
{
	cout << "delete" << endl;
	delete []adr;
}