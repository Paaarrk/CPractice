#include <iostream>
#include "ch01.h"
void Ch01_00()
{
	int in = 0;
	int sum = 0;
	for (int i = 0; i < 5; i++)
	{
		std::cout << "1��° ���� �Է�: ";
		std::cin >> in;
		sum += in;
	}
	std::cout << "�հ�: " << sum<<std::endl;
}

void Ch01_01()
{
	char name[20];
	char phoneNum[20];
	std::cin >> name >> phoneNum;
	std::cout << "�̸�: " << name << ", ��ȭ��ȣ: " << phoneNum << std::endl;
}

void Ch01_02()
{
	int n = 0;
	std::cout << "���� �Է�: ";
	std::cin >> n;

	std::cout << n << "���Դϴ�!" << std::endl;
	for (int i = 1; i < 10; i++)
	{
		std::cout << n << " x " << i << " = " << n * i << std::endl;
	}
}

void Ch01_03()
{
	int input = 0;

	while (1)
	{
		std::cout << "�Ǹűݾ��� ���� ������ �Է�(-1 to end): ";
		std::cin >> input;

		if (input == -1)
			break;
		std::cout << "�̹� �� �޿�: " << 50 + 0.12* input << "����" << std::endl;

	} 
	std::cout << "���α׷��� �����մϴ�." << std::endl;
}

void swap(int* num1, int* num2)
{
	int temp = *num1;
	*num1 = *num2;
	*num2 = temp;
}

void swap(double* num1, double* num2)
{
	double temp = *num1;
	*num1 = *num2;
	*num2 = temp;
}

void swap(char* a, char* b)
{
	char temp = *a;
	*a = *b;
	*b = temp;
}

void Ch01_04()
{
	int num1 = 20, num2 = 40;
	swap(&num1, &num2);
	std::cout << "num1: " << num1 << ", num2: " << num2 << std::endl;
	double db1 = 15.33, db2 = 2243.34;
	swap(&db1, &db2);
	std::cout << "db1: " << db1 << ", db2: " << db2 << std::endl;
	char a = 'a', b = 'b';
	swap(&a, &b);
	std::cout << "a: " << a << ", b: " << b << std::endl;
}

int BoxVolume(int l)
{
	return l;
}
int BoxVolume(int l, int w)
{
	return l * w;
}
int BoxVolume(int l, int w, int h)
{
	return l * w * h;
}

void Ch01_05()
{
	std::cout << "BV(): " << BoxVolume() << std::endl;
	std::cout << "BV(7): " << BoxVolume(7) << std::endl;
	std::cout << "BV(7,3): " << BoxVolume(7, 3) << std::endl;
	std::cout << "BV(7,3,2): " << BoxVolume(7, 3, 2) << std::endl;
}

/*
inline Ű����
1. C�� ��ũ�� �Լ��� ��ü �� �� �ִ�.
2. ���ø��� ����ؾ� ���
3. �����Ϸ��� �Ǵ��ؼ� ���̱⵵, ���⵵ �Ѵ�.
*/

void BestCom::SimpleFunc(void)
{
	fputs("BestCom�� SimpleFunc�Դϴ�. ", stdout);
	ProgCom::SimpleFunc();
	PrettyFunc();
	BestCom_2::MainFunc();
}
void BestCom::PrettyFunc(void)
{
	fputs("BestCom�� �Ƹ����. ", stdout);
}
void BestCom::BestCom_2::MainFunc(void)
{
	fputs("��� ���� MainFunc�� BestCom�� ���� BestCom_2�� �깰�Դϴ�.\n", stdout);
}
void ProgCom::SimpleFunc()
{
	fputs("ProgCom�� SimpleFunc�Դϴ�. ", stdout);
	PrettyFunc();
	BestCom::BestCom_2::MainFunc();
}
void ProgCom::PrettyFunc()
{
	fputs("���� ProgCom�� Protty ",stdout);
}

void Ch01_06()
{
	BestCom::SimpleFunc();
	ProgCom::SimpleFunc();
}
