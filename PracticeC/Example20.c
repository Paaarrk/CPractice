#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"

void Example20_00()
{
	/*
	stream : �ܹ��⼺ ������ ����
	stdout : ǥ�� ��� ��Ʈ��
	stdin : ǥ�� �Է� ��Ʈ��
	*/

	/*
	int putchar(int c) �� int fputc(int c, File * stream)
	putchar�� �Էµ� ���� �ϳ��� stdout�� ���� ���,
	fputc�� stream�� �����ؼ� ���� �ϳ��� ��� (stdout������ �ֿܼ� ���, ���Ͻ�Ʈ���� ������ ���Ϸ� ���)
	�� �Լ��� ��ȯ���� '�ƽ�Ű�ڵ尪'�̴�, ���н� EOF��ȯ
	*/ 

	//int c;
	//scanf("%c", &c);
	int c = 65;
	int n = putchar(c);
	putchar('\n');
	int m = fputc(c, stdout);
	fputc('\n', stdout);
	printf("putchar(c): %d, fputc(c, stdout): %d\n", n, m);

	/*
	int getchar(void) �� int fgetc(File * stream)
	getchar �� ���� �ϳ��� �Է� �޴µ� stdin �� ���� �Է��� ����
	fgetc �� ���� �ϳ��� �Է� �޴µ� stream �� ���� �� �� ����
	�� �Լ��� ��ȯ�� �Էµ� ������ �ƽ�Ű�ڵ尪, ������ ���� �����ϰų� �Լ�ȣ�� ���н� EOF��ȯ
	*/

	int ch1, ch2;
	ch1 = getchar();	//s
	ch2 = fgetc(stdin);	//'\n'
	putchar(ch1);
	//printf('\n'); -> �� ������ ����?
	fputc(ch2, stdout);
	// �� ������������ ġ�� ��(2����Ʈ) ��ŭ ����� ������ �ɱ�?
}

void Example20_01()
{
	int ch;
	while (1)
	{
		ch = getchar();
		if (ch == EOF)
			break;
		fputc(ch, stdout);
	}
}

/*
�� int getchar(void), int putchar(int), int fgetc(File *), int fputc(int, File *) �� int �� �޴°� ��ȯ�� int�ΰ�?
EOF �� int�� -1 �� ����̱� �����̴�. 
char�� ��� �����Ϸ����� unsigned char�� ó���ϴ� ��쵵 �ְ�, char�� ó���ϴ� ��쵵 �־ unsigned char�� ó���ϴ� �����Ϸ��� ��쿡�� ����� ���͹����⶧��

���� ����� �Լ� 4������ printf, scanf�� ���ϸ� �ξ� ������. (���� �ϳ��� �Է� ���� ���)
*/

void Example20_02()
{
	int ch;
	int enter = '\n';
LABEL1:
	ch = fgetc(stdin); 
	if (65 <= ch && ch <= 90)
	{
		ch += 32;
		fputc(ch, stdout);
		putchar(enter);
	}
	else if (97 <= ch && ch <= 122)
	{
		ch -= 32;
		fputc(ch, stdout);
		putchar(enter);
	}
	else {
		printf("���ĺ��� �Է�\n");
		goto LABEL1;
	}
}

/*
scanf�� ������ �����ϴ� ���ڿ� ������ �Ұ����ϴ�. ������ gets, fgets�� �����ϴ�.
���ڿ� ��� �Լ� : int puts(const char * s), int fputs(const char * s, File * stream)
��ȯ�� s�� ���� �ּ�, ���н� EOF

puts �Լ��� �ڵ� ���� fputs�Լ��� �ڵ����� �Ұ�
*/

void Example20_03()
{
	const char* str1 = "1. puts tests";
	const char* str2 = "2. fputs tests";	//const �� �Ⱥٿ��� ���ڿ��� ���� �Ұ��̱� ������ const�ε�
	char end = '\n';
	const char* str3 = "String Test";

	puts(str1);
	puts(str2);
	int address1 = puts(str3);
	printf("%d", address1); putchar(end);
	
	fputs(str1, stdout); printf("\n");	//���⼭ fputc(end, stdout); �� ���� ������ ����. ���ϱ�?
	fputs(str2, stdout); printf("\n");
	int address2 = fputs(str3, stdout); printf("\n");
	printf("%d", address2); printf("\n");
	
}

/*
���ڿ� �Է� �Լ�: gets, fgets
char * gets(char* s) ->�̸� ���� �迭�� �����д�. (������ ������ ����.)
char * fgets(char* s, int n, File * stream) -> n�� ���� �̸� ���� �迭�� ����� �����.
null ���ڰ� �ڵ����� �߰��Ǵ� n���� 1���� ũ���� ���ڿ��� ����ȴ�.
fgets �Լ��� ��� \n�� ���� �� ���� �Է��� �޾Ƶ��δ�. (\n�� ���ڷ� ������ �Ѵ�.)

*/

void Example20_04()
{
	char str[7];
	int i;

	for (i = 0; i < 3; i++)
	{
		fgets(str, sizeof(str), stdin);
		printf("Read %d: %s \n", i + 1, str);
	}
}

/*
��� ���۸� ���� �Լ� int fflush(File * stream)
// ȣ�� ������ 0, ���н� EOF ��ȯ
// stdin �Է¹��۵� ��� �� ������, ��õ���� �ʴ��� (�����Ϸ����� �ٸ�)

�Է¹��۸� ���� ��� - �Լ��� ��� (getchar�� ����� \n ���� ���)
*/

void ClearReadBuffer()
{
	// \n�� �ƴϸ� ����ؼ� �о�´�.
	while (getchar() != '\n');
}

void Example20_05()
{
	char id[7];
	char name[10];

	fputs("�ֹι�ȣ 6�ڸ� �Է�: ", stdout);
	fgets(id, sizeof(id), stdin);
	ClearReadBuffer();

	fputs("�̸� �Է�: ", stdout);
	fgets(name, sizeof(name), stdin);
	ClearReadBuffer();
	fflush(stdin);
	printf("�ֹι�ȣ: %s, �̸�: %s", id, name);
}

/*
���ڿ��� ���̸� ��ȯ�ϴ� �Լ� : size_t strlen(const char * s)
size_t �� typedef unsigned int size_t; �� unsigned int�� size_t�� ��� �Ǿ��ִ�.
������ uint�� ��� int�� ���� �����ϱ� ������ ���� int�� �����ؼ� ����. 
��ȯ �ϴ� ���� ���ڿ��� ���̸� ��ȯ�Ѵ�.
*/

void RemoveWn(char str[])
{
	int len = strlen(str);	// null���� ������ ���� ��ȯ
	str[len - 1] = 0;		// \n�� ��ġ�� 0�� ����('\0')
}
void Example20_06()
{
	char str[100];

	fputs("���ڿ� �Է�: ", stdout);
	fgets(str, sizeof(str), stdin);

	printf("����: %d, ����: %s \n", strlen(str), str);
	
	RemoveWn(str);
	printf("����: %d, ����: %s \n", strlen(str), str);

}

/*
���ڿ��� �����ϴ� �Լ� strcpy �� strncpy
char * strcpy(char * dest, const char * src);
char * strcpy(char * dest, const char * src, size_t n);
strcpy �� ����ϸ� dest�� �迭�� src���� �۾Ƶ� n��ŭ�� �ִ´�.
*/

void Example20_07()
{
	char str1[30] = "good morning everyone\n";
	char str2[30];
	char str3[10];

	fputs("First case: 30 to 30 \n", stdout);
	printf("�ּ�: %ld, ", strncpy(str2, str1, sizeof(str2)));
	fputs("���ڿ�: ", stdout);
	fputs(str2, stdout);

	fputs("Second case: 30 to 10 \n", stdout);
	printf("�ּ�: %ld, ", strncpy(str3, str1, sizeof(str3)));
	fputs("���ڿ�: ", stdout);
	fputs(str3, stdout);

	fputs("Third case: 30 to 10 \n", stdout);
	str3[sizeof(str3) - 1] = 0;
	fputs("���ڿ�: ", stdout);
	fputs(str3, stdout);
	
}

/*
���ڿ��� �����̴� �Լ� 
char* strcat(char* dest, const char* src);
char* strncat(char* dest, const char* src, size_t n);

src�� dest �� '\0' �ڸ����� ������ ���δ�. ncat�� ��� n�� ũ�⸸ŭ src�� ���ڿ��� ���δ�.
strncat�� ��� strncpy�� �ٸ��� n�� ũ�⸸ŭ ���̰� �������� '\0' �� null ���ڸ� �ٿ��ش�.
dest�� ũ�Ⱑ ���̴� �� ���� ������ ������ ����.
��ȯ�� ����� dest�� �ּ�
*/

void Example20_08()
{
	char str1[30] = "My Name is";
	char* str2 = "�ߪ�";
	
	strncat(str1, str2, sizeof(str2));
	fputs(str1, stdout);
}

/*
���ڿ��� ���ϴ� �Լ� strcmp, strncmp
int strcmp(const char* s1, const char* s2);
int strncmp(const char* s1, const char* s2, size_t n);
strcmp�� ��� ���� �ٸ��� 0�̾ƴ� ��, ������ 0 (���� �ƽ�Ű�ڵ� ���� s1�� ũ�� ���, s2�� ũ�� ����)
strncmp�� ��� strcmp �� ���� ����� ��ȯ������, n��ŭ�� ���Ѵ�.
'\0'�� �� ����� �ȴ�.

*/

void isEqual_strncmp(const char* s1, const char* s2, size_t n)
{
	int res = strncmp(s1, s2, n);
	if (res == 0)
		fputs("�����ϴ�.\n", stdout);
	else
		fputs("�ٸ��ϴ�.\n", stdout);
}

void isEqual_strcmp(const char* s1, const char* s2)
{
	int res = strcmp(s1, s2);
	if (res == 0)
		fputs("�����ϴ�.\n", stdout);
	else
		fputs("�ٸ��ϴ�.\n", stdout);
}

void Example20_09()
{
	const char* s1 = "My name ";
	const char* s2 = "My name";
	const char* s3 = "My name";
	const char* s4 = "My ";

	fputs("s1�� s2 ��: ", stdout);
	isEqual_strcmp(s1, s2);
	fputs("s1�� s2 �� �Ϻ� ��: ", stdout);
	isEqual_strncmp(s1, s2, 7);
	fputs("s2�� s3 �� �Ϻ� ��: ", stdout);
	isEqual_strncmp(s3, s2, 100);
	isEqual_strncmp(s3, s2, 8);
	isEqual_strncmp(s3, s2, 7);
	isEqual_strcmp(s3, s2);

	fputs("s3�� s4�� �Ϻ� ��: ", stdout);
	isEqual_strncmp(s3, s4, 3);
	isEqual_strncmp(s3, s4, 4);
	isEqual_strncmp(s3, s4, 5);
	
}

void Example20_10()
{
	int sum = 0;
	char c;

	while (1)
	{
		c = fgetc(stdin);
		if (49 <= c && c <= 57)
			sum += (c - 48);

		if (c == '\n')
			break;
	}
	printf("Sum: %d", sum);
}

void Example20_11()
{
	char str1[20];
	char str2[20];
	char str3[40];

	fgets(str1, sizeof(str1), stdin);
	
	if (str1[19] == 0)
	{
		fputs("�Է� ���� ����\n", stdout);
		while (getchar() != '\n');
	}
	else
	{
		for (int i = 0; i < 20; i++)
		{
			if (str1[i] == '\n')
			{
				str1[i] = '\0';
				break;
			}
		}
	}

	fgets(str2, sizeof(str2), stdin);

	if (str2[19] == 0)
	{
		fputs("�Է� ���� ����\n", stdout);
		while (getchar() != '\n');
	}
	else
	{
		for (int i = 0; i < 20; i++)
		{
			if (str2[i] == '\n')
			{
				str2[i] = '\0';
				break;
			}
		}
	}

	strncpy(str3, str1, strlen(str1) + 1);
	printf("str3: %s\n", str3);

	strncat(str3, str2, strlen(str2));
	fputs("str3: ", stdout);
	fputs(str3, stdout);

}

void Example20_12()
{
	char str1[20];
	char str2[20];
	int nameLen1 = 0;
	int nameLen2 = 0;
	int age1 = 0;
	int age2 = 0;

	fgets(str1, sizeof(str1), stdin);
	str1[strlen(str1) - 1] = 0;
	fgets(str2, sizeof(str2), stdin);
	str2[strlen(str2) - 1] = 0;

	for (int i = 0; i < 20; i++)
	{
		if (str1[i] == ' ')
			nameLen1 = i;
	}
	for (int i = 0; i < 20; i++)
		if (str2[i] == ' ')
			nameLen2 = i;
	printf("namelen1: %d, namelen2: %d\n", nameLen1, nameLen2);
	if (nameLen1 != nameLen2)
		fputs("�̸��� �ٸ��ϴ�. \n", stdout);
	else if (0 == strncmp(str1, str2, nameLen1))
		fputs("�̸��� �����ϴ�. \n", stdout);
	else
		fputs("�̸��� �ٸ��ϴ�. \n", stdout);

	
	age1 = atoi(&str1[nameLen1 + 1]);
	age2 = atoi(&str2[nameLen2 + 1]);
	if (age1 != age2)
		fputs("���̰� �ٸ��ϴ�. \n", stdout);
	else
		fputs("���̰� �����ϴ�. \n", stdout);
	
}