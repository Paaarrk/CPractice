#include <iostream>
#include "ch01.h"
void Ch01_00()
{
	int in = 0;
	int sum = 0;
	for (int i = 0; i < 5; i++)
	{
		std::cout << "1번째 정수 입력: ";
		std::cin >> in;
		sum += in;
	}
	std::cout << "합계: " << sum<<std::endl;
}

void Ch01_01()
{
	char name[20];
	char phoneNum[20];
	std::cin >> name >> phoneNum;
	std::cout << "이름: " << name << ", 전화번호: " << phoneNum << std::endl;
}

void Ch01_02()
{
	int n = 0;
	std::cout << "숫자 입력: ";
	std::cin >> n;

	std::cout << n << "단입니다!" << std::endl;
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
		std::cout << "판매금액을 만원 단위로 입력(-1 to end): ";
		std::cin >> input;

		if (input == -1)
			break;
		std::cout << "이번 달 급여: " << 50 + 0.12* input << "만원" << std::endl;

	} 
	std::cout << "프로그램을 종료합니다." << std::endl;
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
inline 키워드
1. C의 매크로 함수를 대체 할 수 있다.
2. 템플릿을 사용해야 깔끔
3. 컴파일러가 판단해서 붙이기도, 떼기도 한다.
*/

void BestCom::SimpleFunc(void)
{
	fputs("BestCom의 SimpleFunc입니다. ", stdout);
	ProgCom::SimpleFunc();
	PrettyFunc();
	BestCom_2::MainFunc();
}
void BestCom::PrettyFunc(void)
{
	fputs("BestCom은 아름답다. ", stdout);
}
void BestCom::BestCom_2::MainFunc(void)
{
	fputs("기반 엔진 MainFunc는 BestCom의 산하 BestCom_2의 산물입니다.\n", stdout);
}
void ProgCom::SimpleFunc()
{
	fputs("ProgCom의 SimpleFunc입니다. ", stdout);
	PrettyFunc();
	BestCom::BestCom_2::MainFunc();
}
void ProgCom::PrettyFunc()
{
	fputs("내가 ProgCom의 Protty ",stdout);
}

void Ch01_06()
{
	BestCom::SimpleFunc();
	ProgCom::SimpleFunc();
}
