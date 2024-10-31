#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"

void Example5_00()
{
	char num1 = 1, num2 = 2, result1 = 0;
	short num3 = 300, num4 = 400, result2 = 0;
	printf("int의 크기: %d\n", sizeof(int));
	printf("long의 크기: %d\n", sizeof(long));
	printf("long long의 크기: %d\n", sizeof(long long));

	// 일반적으로 CPU에서 연산하기 좋은 경우는 int이기 때문에 보통 연산은 int로 형변환 후 진행된다. (가장 빠름)
	printf("num1, num2 의 크기: %d, %d\n", sizeof(num1), sizeof(num2));
	printf("num3, num4 의 크기: %d, %d\n", sizeof(num3), sizeof(num4));
	printf("합 계산은 int로 형변환 후 계산되어 결과가 반환된다.\n");
	printf("num1 + num2의 크기: %d\n", sizeof(num1 + num2));
	printf("num3 + num4의 크기: %d\n", sizeof(num3 + num4));
	// result에 합연산 결과를 저장할 때는 먼저 int로 계산 한 결과를 형변환 후 저장된다.
	result1 = num1 + num2;
	result2 = num3 + num4;
	printf("result1, result2 의 크기: %d, %d\n", sizeof(result1), sizeof(result2));

	printf("float 크기: %d\n",sizeof(float));
	printf("double 크기: %d\n", sizeof(double));
	printf("long double 크기: %d\n", sizeof(long double));	//여긴 8로 double과 같다. 12바이트인 경우도 있다.

	unsigned char c1 = -1;
	signed char c2 = -2;
	char c3 = -3;
	printf("unsigned c1, signed c2, char c3: %d, %d, %d : 나의 컴파일러는 char을 기본적으로 unsigned char로 처리함을 알 수 있다.\n", c1, c2, c3);

	char hangul = 'ㄱ';
	printf("sizeof 한글: %d, 글자: %c\n : 한글은 3바이트이기 때문에 잘려나가서 깨진다.(char은 아스키코드를 위함)", sizeof(hangul), hangul);
}

void Example5_01()
{
	int x1; int y1; int x2; int y2;
	printf("좌상단의 x, y 좌표: ");
	scanf("%d %d", &x1, &y1);
	printf("우하단의 x, y 좌표: ");
	scanf("%d %d", &x2, &y2);
	printf("사각형의 넓이: %d\n", (x2 - x1) * (y1 - y2));
}
void Example5_02()
{
	double d1, d2;
	printf("두개의 실수 입력: ");
	scanf("%lf %lf", &d1, &d2);
	printf("합: %f, 곱: %f, 차: %f, 분: %f\n", d1 + d2, d1 * d2, d1 - d2, d1 / d2);
	printf("%d", sizeof(d1 + d2));
}

void Example5_03()
{
	char x = -3;
	printf("%c\n", x);
	/*
	아스키코드의 값의 범위는 0 ~ 127
	영어 대문자는 65 ~ 90
	영어 소문자는 97 ~ 122
	(32 차이)
	*/
}
void Example5_04()
{
	// 이렇게 입력받으면 큰일난다.
	//char y;
	//scanf("%d", &y);
	//printf("%c\n", y);
	int y;
	scanf("%d", &y);
	printf("%c\n", y);	// 1바이트만큼 읽어서 문자로 반환
	//[90]
	y = y >> 8;
	//[90][0]
	y += 122;
	//[90][122]
	printf("%c\n", y);	// 끝에서 부터 읽어나간다. [122] 출력
}

void Example5_05()
{
	char c;
	scanf("%c", &c);
	printf("%d", c);
}