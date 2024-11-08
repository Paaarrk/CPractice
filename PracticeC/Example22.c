#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"

struct employee
{
	char* name[20];
	char* address[20];
	int money;
};

void Example22_00()
{

}

void Example22_01()
{
	struct employee n1;

	fputs("이름: ", stdout); scanf("%s", n1.name);
	fputs("주민등록번호: ", stdout); scanf("%s", n1.address);
	fputs("급여 정보: ", stdout); scanf("%d", &n1.money);

	fputs("입력된 분의 정보\n", stdout);
	fputs("이름: ", stdout); fputs(n1.name, stdout);
	fputs("주민등록번호: ", stdout); fputs(n1.address, stdout);
	printf("급여 정보: %d", n1.money);
}

void Example22_02()
{
	struct employee arr[3];
	for (int i = 0; i < 3; i++)
	{
		printf("%d 번째 인물 입력\n", i + 1);
		fputs("이름: ", stdout); scanf("%s", arr[i].name);
		fputs("주민등록번호: ", stdout); scanf("%s", arr[i].address);
		fputs("급여정보: ", stdout); scanf("%d", &arr[i].money);
	}
	fputs("\n\n", stdout);
	for (int i = 0; i < 3; i++)
	{
		fputs("입력된 분의 정보\n", stdout);
		fputs("이름: ", stdout); fputs(arr[i].name, stdout);
		fputs("\n주민등록번호: ", stdout); fputs(arr[i].address, stdout);
		printf("\n급여 정보: %d", arr[i].money);
	}
}

struct point
{
	int xpos;
	int ypos;
	struct point* con;
};

struct Circle
{
	double radious;
	struct point* center;
};

double round(struct Circle* circle)
{
	return 2 * 3.14 * (circle->radious);
}

double area(struct Circle* circle)
{
	return 3.14 * (circle->radious) * (circle->radious);
}
void Example22_03()
{
	// 원의 둘레와 넓이
	struct Circle c1 = { 4.0 };
	struct point p1 = { 1, 2 };
	c1.center = &p1;
	printf("원의 위치: [%d, %d]\n 원의 반지름: %lf\n", c1.center->xpos, c1.center->ypos, c1.radious);
	printf("원의 둘레: %lf\n 원의 넓이: %lf\n", round(&c1), area(&c1));
}

void Example22_04()
{
	// 삼각형 만들기
	struct point triangle[3];

	for (int i = 0; i < 3; i++)
	{
		if (i == 2)
		{
			triangle[2].con = &triangle[0];
			break;
		}
		triangle[i].con = &triangle[i + 1];
	}
	for (int i = 0; i < 3; i++)
	{
		printf("점 %d 번째 입력: ", i + 1);
		scanf("%d %d", &(triangle[i].xpos), &(triangle[i].ypos));
		printf("점 [%d, %d]가 입력되었습니다.\n", triangle[i].xpos, triangle[i].ypos);
	}
	printf("--삼각형 정보--\n");
	for (int i = 0; i < 3; i++)
	{
		printf("[%d, %d] 와 [%d, %d] 가 연결되었습니다.\n", triangle[i].xpos, triangle[i].ypos, triangle[i].con->xpos, triangle[i].con->ypos);
	}
}