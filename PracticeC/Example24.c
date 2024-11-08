#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"


int Example24_00()
{
	FILE* fp = fopen("prac.txt", "wt");
	if (fp == NULL)
	{
		puts("���� ���� ����");
		return -1;
	}

	fputc('A', fp);
	fputc('B', fp);
	fputc('C', fp);
	fputs("My name is Hong! \n", fp);
	fputs("Your name is Yoon! \n", fp);
	fclose(fp);
	return 0;
}

int Example24_01()
{
	char str[30];
	int ch;
	FILE* fp = fopen("prac.txt", "rt");
	if (fp == NULL)
	{
		puts("���� ���� ����");
		return -1;
	}

	ch = fgetc(fp);
	fputc(ch, stdout); fputc('\n', stdout);
	ch = fgetc(fp);
	fputc(ch, stdout); fputc('\n', stdout);
	ch = fgetc(fp);
	fputc(ch, stdout); fputc('\n', stdout);

	fgets(str, sizeof(str), fp);
	printf("%s", str);
	fgets(str, sizeof(str), fp);
	printf("%s", str);
	fclose(fp);

}

/*
feof => ���� �д� �κ��� ������ ������ Ȯ���Ѵ�.
������ ���� �����ϸ� 0�� �ƴѰ��� ��ȯ�Ѵ�.
*/

void Example24_02()
{
	FILE* src = fopen("prac.txt", "rt");
	FILE* des = fopen("prac_copy.txt", "wt");

	int ch;
	if (src == NULL || des == NULL)
	{
		fputs("���� �ҷ����� ����", stdout);
		return;
	}

	while ((ch = fgetc(src)) != EOF)
	{	// copy
		fputc(ch, des);
	}

	if (feof(src) != 0)
		fputs("���� ���� �Ϸ�", stdout);
	else
		puts("���� ���� ����");

	fclose(src);
	fclose(des);
}

void Example24_03()
{
	FILE* src = fopen("1.png", "rb");
	FILE* des = fopen("1_copy.png", "wb");

	char buffer[20];
	int readCount;

	if (src == NULL || des == NULL)
	{
		puts("���� �ε� ����");
		return;
	}

	// ���� ����
	while (1)
	{
		readCount = fread((void*)buffer, 1, sizeof(buffer), src);
		
		if (readCount < sizeof(buffer))
		{	//���� �� ���
			if (feof(src) != 0)	//������ ���̶��
			{
				fwrite((void*)buffer, 1, readCount, des);
				puts("���� ���� �Ϸ�");
				break;
			}
			else {
				puts("���� ���� ����");
				break;
			}
		}
		fwrite((void*)buffer, 1, sizeof(buffer), des);
	}

	fclose(src);
	fclose(des);
}

void Example24_04()
{
	FILE* f1 = fopen("mystory.txt", "wt");
	if (f1 == NULL)
	{
		puts("�ε� ����");
		return;
	}
	fputs("#name: younsu \n", f1);
	fputs("#address: 900298-1012589 \n", f1);
	fputs("#phonenum: 010-1111-2222 \n", f1);
	fclose(f1);

}

void Example24_05()
{
	FILE* f1 = fopen("mystory.txt", "at");
	if (f1 == NULL)
	{
		puts("�ε� ����");
		return;
	}
	fputs("#favorite food: jampong, tansuyuk \n", f1);
	fputs("#habbit: soccer \n", f1);

}

void Example24_06()
{
	FILE* f1 = fopen("mystory.txt", "rt");
	if (f1 == NULL)
	{
		puts("�ε� ����");
		return;
	}

	char buffer[30];
	while (1)
	{
		if (feof(f1) != 0)
			return;
		fgets(buffer, sizeof(buffer), f1);
		printf("%s", buffer);
	}
}

void Example24_07()
{
	char name[10];
	char sex;
	int age;

	FILE* fp = fopen("friend.txt", "wt");
	for (int i = 0; i < 3; i++)
	{
		fputs("�̸� ���� ���� �� �Է�: ", stdout);
		scanf("%s %c %d", name, &sex, &age);
		getchar();	//'\n' �����
		fprintf(fp, "%s %c %d", name, sex, age);
	}

	fclose(fp);
}

void Example24_08()
{
	char name[10];
	char sex;
	int age;

	FILE* fp = fopen("friend.txt", "rt");
	int ret;
	while (1)
	{
		ret = fscanf(fp, "%s %c %d", name, &sex, &age);
		if (ret == EOF)
			break;
		printf("%s %c %d \n", name, sex, age);
	}
	fclose(fp);

}

typedef struct {
	char name[10];
	char sex;
	int age;
} Friend;

void Example24_09()
{
	FILE* fp;
	Friend myfren1;
	Friend myfren2;

	fp = fopen("friend.bin", "wb");
	printf("�̸�, ����, ���� �� �Է�: ");
	scanf("%s %c %d", myfren1.name, &(myfren1.sex), &(myfren1.age));
	fwrite((void*)&myfren1, sizeof(myfren1), 1, fp);
	fclose(fp);


	fp = fopen("friend.bin", "b");
	fread((void*)&myfren2, sizeof(myfren2), 1, fp);
	printf("%s %c %d \n", myfren2.name, myfren2.sex, myfren2.age);
	fclose(fp);
	
}

void Example24_10()
{
	FILE* fp = fopen("text.txt", "wt");
	fputs("123456789", fp);
	fclose(fp);

	fp = fopen("text.txt", "rt");

	fseek(fp, -2, SEEK_END);
	putchar(fgetc(fp));

	fseek(fp, +2, SEEK_SET);
	putchar(fgetc(fp));

	fseek(fp, +2, SEEK_CUR);
	putchar(fgetc(fp));

	fclose(fp);

}

long GetFileSize(FILE* fp)
{
	long curpos = ftell(fp);
	fseek(fp, 0, SEEK_END);
	long size = ftell(fp);
	fseek(fp, curpos, SEEK_SET);
	return size;
}

void Example24_11()
{
	FILE* fp = fopen("text.txt", "rt");
	long size = GetFileSize(fp);
	fclose(fp);
	printf("%ld", size);
}