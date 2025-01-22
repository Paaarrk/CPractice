#include <stdio.h>

static struct _point {
	int x;
	int y;
};
void func(char, int, double, char*);

void func2(int*, int(*)[3]);

int sum(int, int);

void print1(struct _point p1);

void print2(struct _point* p2);

char* getstr(void);

void Ch8_01()
{
	printf_s("Prac 1\n");
	char c = 'Z';
	int n1 = 50;
	double d = 77.777;
	char* str = "C Programming";
	func(c, n1, d, str);
	printf_s("\nPrac 2\n");
	int arr1[6] = { 10,20,30,40,50,60 };
	int arr2[2][3] = { {100,200,300}, {400,500,600} };
	func2(arr1, arr2);
	printf_s("\nPrac 3\n");
	int n2, n3;
	scanf_s("%d %d", &n2, &n3);
	printf_s("%d + %d = %d\n", n2, n3, sum(n2, n3));
	printf_s("\n\nPrac 4\n");
	struct _point p1 = { 10, 20 }, p2 = { 20, 20 };
	print1(p1);
	print2(&p2);
	printf("\nPrac 5\n");
	puts(getstr());
	puts(getstr());
	puts(getstr());

}

void func(char c, int n, double d, char* str)
{
	printf_s("%c %d %lf %s\n", c, n, d, str);
}

void func2(int* arr, int(*arr2)[3])
{
	for (int i = 6; i != 0; i--)
	{
		printf_s("%d ", arr[6 - i]);
	}
	puts("\n");
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 3; j++)
			printf_s("%d ", arr2[i][j]);
	puts("\n");
}

int sum(int n1, int n2)
{
	return n1 + n2;
}

void print1(struct _point p)
{
	printf_s("%d %d\n", p.x, p.y);
}

void print2(struct _point* p)
{
	printf_s("%d %d\n", p->x, p->y);
}

char* getstr()
{
	static int cnt = 1;
	static char str[100];
	sprintf_s(str, 100, "call count : %d\n", cnt++);
	return str;
}