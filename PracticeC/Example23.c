#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"

void Example23_00()
{

}

typedef struct {
	int posX;
	int posY;
} Point;

void swapPoint(Point* p1, Point* p2)
{
	Point temp = *p1;
	p1->posX = p2->posX;
	p1->posY = p2->posY;
	p2->posX = temp.posX;
	p2->posY = temp.posY;
}

void Example23_01()
{
	Point p1 = { 1, 2 };
	Point p2 = { 2, 3 };
	printf("%ld: [%d, %d], %ld: [%d, %d]\n", &p1,  p1.posX, p1.posY, &p2, p2.posX, p2.posY);
	swapPoint(&p1, &p2);
	printf("%ld: [%d, %d], %ld: [%d, %d]\n", &p1, p1.posX, p1.posY, &p2, p2.posX, p2.posY);
}

typedef struct {
	Point p1;
	Point p2;
} Rectangle;

int Rarea(Rectangle* r)
{
	return (r->p2.posX - r->p1.posX) * (r->p2.posY - r->p1.posY);
}

void ShowRecInfo(Rectangle* r)
{
	printf("�� [%d, %d], [%d, %d]�� �̷����\n", r->p1.posX, r->p1.posY, r->p2.posX, r->p2.posY);
	printf("���̴� %d\n", Rarea(r));
}

void Example23_02()
{
	Rectangle r1 = { {1, 2}, {100, 101} };
	Rectangle r2 = { {2, 4}, {4, 8} };
	ShowRecInfo(&r2);
	ShowRecInfo(&r1);
}

typedef struct udshort {
	unsigned short upper;
	unsigned short lower;
} UDshort;

typedef union newint {
	int x;
	char o[4];
	UDshort s;
} Newint;

void Example23_03()
{
	Newint getInt;
	scanf("%d", &getInt.x);

	printf("��Ʈ�� ���: %d\n", getInt.x);
	printf("1����Ʈ ���� �ƽ�Ű�ڵ� ���: %c, %c, %c, %c\n", getInt.o[0], getInt.o[1], getInt.o[2], getInt.o[3]);
	printf("2����Ʈ ���� ���: %d, %d\n", getInt.s.upper, getInt.s.lower);
}

typedef enum doremi {
	Do = 1, Re, Mi, Fa, Sol, Ra, Si = 7
} Doremi;

void Sound(Doremi d)
{
	switch (d)
	{
	case Do:
		fputs("��!\n", stdout);
		break;
	case Re:
		fputs("��!\n", stdout);
		break;
	case Mi:
		fputs("��!\n", stdout);
		break;
	case Fa:
		fputs("��!\n", stdout);
		break;
	case Sol:
		fputs("��!\n", stdout);
		break;
	case Ra:
		fputs("��!\n", stdout);
		break;
	case Si:
		fputs("��!\n", stdout);
		break;
	}
}
void Example23_04()
{
	Doremi d;
	for (d = 1; d <= 7; d++)
		Sound(d);
}