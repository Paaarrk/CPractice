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

	fputs("�̸�: ", stdout); scanf("%s", n1.name);
	fputs("�ֹε�Ϲ�ȣ: ", stdout); scanf("%s", n1.address);
	fputs("�޿� ����: ", stdout); scanf("%d", &n1.money);

	fputs("�Էµ� ���� ����\n", stdout);
	fputs("�̸�: ", stdout); fputs(n1.name, stdout);
	fputs("�ֹε�Ϲ�ȣ: ", stdout); fputs(n1.address, stdout);
	printf("�޿� ����: %d", n1.money);
}

void Example22_02()
{
	struct employee arr[3];
	for (int i = 0; i < 3; i++)
	{
		printf("%d ��° �ι� �Է�\n", i + 1);
		fputs("�̸�: ", stdout); scanf("%s", arr[i].name);
		fputs("�ֹε�Ϲ�ȣ: ", stdout); scanf("%s", arr[i].address);
		fputs("�޿�����: ", stdout); scanf("%d", &arr[i].money);
	}
	fputs("\n\n", stdout);
	for (int i = 0; i < 3; i++)
	{
		fputs("�Էµ� ���� ����\n", stdout);
		fputs("�̸�: ", stdout); fputs(arr[i].name, stdout);
		fputs("\n�ֹε�Ϲ�ȣ: ", stdout); fputs(arr[i].address, stdout);
		printf("\n�޿� ����: %d", arr[i].money);
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
	// ���� �ѷ��� ����
	struct Circle c1 = { 4.0 };
	struct point p1 = { 1, 2 };
	c1.center = &p1;
	printf("���� ��ġ: [%d, %d]\n ���� ������: %lf\n", c1.center->xpos, c1.center->ypos, c1.radious);
	printf("���� �ѷ�: %lf\n ���� ����: %lf\n", round(&c1), area(&c1));
}

void Example22_04()
{
	// �ﰢ�� �����
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
		printf("�� %d ��° �Է�: ", i + 1);
		scanf("%d %d", &(triangle[i].xpos), &(triangle[i].ypos));
		printf("�� [%d, %d]�� �ԷµǾ����ϴ�.\n", triangle[i].xpos, triangle[i].ypos);
	}
	printf("--�ﰢ�� ����--\n");
	for (int i = 0; i < 3; i++)
	{
		printf("[%d, %d] �� [%d, %d] �� ����Ǿ����ϴ�.\n", triangle[i].xpos, triangle[i].ypos, triangle[i].con->xpos, triangle[i].con->ypos);
	}
}