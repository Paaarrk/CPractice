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
	// SmartPointer : ���� �Ҵ� ��ü�� ������ ���� ���� : �ڵ� ����
	SmartPointer sp(new Points(3, 1));
	sp->ShowInfo();
}

void Ch11_05()
{
	// Functor : ��ü�� �Լ�ó��
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
	cout << "Gun �⺻������" << this << endl;
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
	cout << "Gun ���û�����" << this << endl;
	_name = (char*)malloc(sizeof(char) * (strlen(name) + 1));
	strcpy(_name, name);
}
Gun::Gun(Gun& ref) : _bullet(ref._bullet)
{
	cout << "Gun ���������" << this << endl;
	_name = (char*)malloc(sizeof(char) * (strlen(ref._name) + 1));
	strcpy(_name, ref._name);
}
Gun::~Gun()
{
	cout << "Gun �Ҹ���" << this << endl;
	free(_name);
}
Gun& Gun::operator=(Gun& gun)
{
	cout << "Gun ���� ������" << this << endl;
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
	cout << "�ѱ� ����: " << _name << ", �Ѿ� ��: " << _bullet << endl;
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
	*pistol = *ref.pistol;	//���Կ����� Ȱ���� ���� ���� ����
	_handcuffs = ref._handcuffs;
	return *this;
}
bool Police::Shot()
{
	if (strcmp(pistol->_name, "N") == 0)
	{
		cout << "�ѱⰡ ����� " << this << endl;
		return false;
	}
	else {
		if (pistol->_bullet == 0)
		{
			cout << "�Ѿ��� ����� " << this << endl;
			return false;
		}
		else
		{
			pistol->SetBullet(pistol->GetBullet() - 1);
			cout << "�߻�!" << endl;
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
			cout << "ü�� !!" << endl;
		}
		else
		{
			cout << "ü�� ����" << endl;
		}
	}
	else
	{
		cout << "ü�� ����" << endl;
	}
}

void Police::ShowInfo() const
{
	cout << "���� ����: " << this << endl;
	pistol->ShowInfo();
	cout << "���� ��: " << _handcuffs << endl;
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