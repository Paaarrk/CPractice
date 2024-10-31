#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"

void Example20_00()
{
	/*
	stream : 단방향성 데이터 전송
	stdout : 표준 출력 스트림
	stdin : 표준 입력 스트림
	*/

	/*
	int putchar(int c) 와 int fputc(int c, File * stream)
	putchar은 입력된 문자 하나를 stdout을 통해 출력,
	fputc는 stream을 지정해서 문자 하나를 출력 (stdout지정시 콘솔에 출력, 파일스트림을 넣으면 파일로 출력)
	두 함수의 반환값은 '아스키코드값'이다, 실패시 EOF반환
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
	int getchar(void) 와 int fgetc(File * stream)
	getchar 은 문자 하나를 입력 받는데 stdin 을 통해 입력을 받음
	fgetc 는 문자 하나를 입력 받는데 stream 을 지정 할 수 있음
	두 함수의 반환은 입력된 문자의 아스키코드값, 파일의 끝에 도달하거나 함수호출 실패시 EOF반환
	*/

	int ch1, ch2;
	ch1 = getchar();	//s
	ch2 = fgetc(stdin);	//'\n'
	putchar(ch1);
	//printf('\n'); -> 왜 오류가 날까?
	fputc(ch2, stdout);
	// 왜 ㄱㄱㄱㄱㄱ을 치면 ㄱ(2바이트) 만큼 출력이 가능한 걸까?
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
왜 int getchar(void), int putchar(int), int fgetc(File *), int fputc(int, File *) 은 int 를 받는고 반환도 int인가?
EOF 는 int인 -1 의 상수이기 때문이다. 
char의 경우 컴파일러마다 unsigned char로 처리하는 경우도 있고, char로 처리하는 경우도 있어서 unsigned char로 처리하는 컴파일러의 경우에는 양수가 나와버리기때문

문자 입출력 함수 4가지는 printf, scanf에 비하면 훨씬 빠르다. (문자 하나를 입력 받을 경우)
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
		printf("알파벳만 입력\n");
		goto LABEL1;
	}
}

/*
scanf는 공백을 포함하는 문자열 입출이 불가능하다. 하지만 gets, fgets는 가능하다.
문자열 출력 함수 : int puts(const char * s), int fputs(const char * s, File * stream)
반환은 s의 시작 주소, 실패시 EOF

puts 함수는 자동 개행 fputs함수는 자동개행 불가
*/

void Example20_03()
{
	const char* str1 = "1. puts tests";
	const char* str2 = "2. fputs tests";	//const 를 안붙여도 문자열은 수정 불가이기 때문에 const인듯
	char end = '\n';
	const char* str3 = "String Test";

	puts(str1);
	puts(str2);
	int address1 = puts(str3);
	printf("%d", address1); putchar(end);
	
	fputs(str1, stdout); printf("\n");	//여기서 fputc(end, stdout); 을 쓰면 오류가 난다. 왜일까?
	fputs(str2, stdout); printf("\n");
	int address2 = fputs(str3, stdout); printf("\n");
	printf("%d", address2); printf("\n");
	
}

/*
문자열 입력 함수: gets, fgets
char * gets(char* s) ->미리 받을 배열을 만들어둔다. (넘으면 오류가 난다.)
char * fgets(char* s, int n, File * stream) -> n을 통해 미리 받을 배열의 사이즈를 만든다.
null 문자가 자동으로 추가되니 n보다 1작은 크기의 문자열이 저장된다.
fgets 함수의 경우 \n을 만날 때 까지 입력을 받아들인다. (\n도 문자로 인정을 한다.)

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
출력 버퍼를 비우는 함수 int fflush(File * stream)
// 호출 성공시 0, 실패시 EOF 반환
// stdin 입력버퍼도 비울 수 있지만, 추천하지 않는편 (컴파일러마다 다름)

입력버퍼를 비우는 방법 - 함수를 사용 (getchar을 사용해 \n 까지 비움)
*/

void ClearReadBuffer()
{
	// \n이 아니면 계속해서 읽어온다.
	while (getchar() != '\n');
}

void Example20_05()
{
	char id[7];
	char name[10];

	fputs("주민번호 6자리 입력: ", stdout);
	fgets(id, sizeof(id), stdin);
	ClearReadBuffer();

	fputs("이름 입력: ", stdout);
	fgets(name, sizeof(name), stdin);
	ClearReadBuffer();
	fflush(stdin);
	printf("주민번호: %s, 이름: %s", id, name);
}

/*
문자열의 길이를 반환하는 함수 : size_t strlen(const char * s)
size_t 는 typedef unsigned int size_t; 즉 unsigned int가 size_t로 명명 되어있다.
하지만 uint의 경우 int에 저장 가능하기 때문에 보통 int에 저장해서 쓴다. 
반환 하는 것은 문자열의 길이를 반환한다.
*/

void RemoveWn(char str[])
{
	int len = strlen(str);	// null문자 제외한 길이 반환
	str[len - 1] = 0;		// \n의 위치에 0을 넣음('\0')
}
void Example20_06()
{
	char str[100];

	fputs("문자열 입력: ", stdout);
	fgets(str, sizeof(str), stdin);

	printf("길이: %d, 내용: %s \n", strlen(str), str);
	
	RemoveWn(str);
	printf("길이: %d, 내용: %s \n", strlen(str), str);

}

/*
문자열을 복사하는 함수 strcpy 와 strncpy
char * strcpy(char * dest, const char * src);
char * strcpy(char * dest, const char * src, size_t n);
strcpy 를 사용하면 dest의 배열이 src보다 작아도 n만큼만 넣는다.
*/

void Example20_07()
{
	char str1[30] = "good morning everyone\n";
	char str2[30];
	char str3[10];

	fputs("First case: 30 to 30 \n", stdout);
	printf("주소: %ld, ", strncpy(str2, str1, sizeof(str2)));
	fputs("문자열: ", stdout);
	fputs(str2, stdout);

	fputs("Second case: 30 to 10 \n", stdout);
	printf("주소: %ld, ", strncpy(str3, str1, sizeof(str3)));
	fputs("문자열: ", stdout);
	fputs(str3, stdout);

	fputs("Third case: 30 to 10 \n", stdout);
	str3[sizeof(str3) - 1] = 0;
	fputs("문자열: ", stdout);
	fputs(str3, stdout);
	
}

/*
문자열을 덧붙이는 함수 
char* strcat(char* dest, const char* src);
char* strncat(char* dest, const char* src, size_t n);

src를 dest 의 '\0' 자리부터 복사해 붙인다. ncat의 경우 n의 크기만큼 src의 문자열을 붙인다.
strncat의 경우 strncpy와 다르게 n의 크기만큼 붙이고 마지막에 '\0' 인 null 문자를 붙여준다.
dest의 크기가 붙이는 것 보다 작으면 오류가 난다.
반환은 복사된 dest의 주소
*/

void Example20_08()
{
	char str1[30] = "My Name is";
	char* str2 = "みく";
	
	strncat(str1, str2, sizeof(str2));
	fputs(str1, stdout);
}

/*
문자열을 비교하는 함수 strcmp, strncmp
int strcmp(const char* s1, const char* s2);
int strncmp(const char* s1, const char* s2, size_t n);
strcmp의 경우 비교후 다르면 0이아닌 값, 같으면 0 (보통 아스키코드 값이 s1이 크면 양수, s2가 크면 음수)
strncmp의 경우 strcmp 와 같은 결과를 반환하지만, n만큼만 비교한다.
'\0'도 비교 대상이 된다.

*/

void isEqual_strncmp(const char* s1, const char* s2, size_t n)
{
	int res = strncmp(s1, s2, n);
	if (res == 0)
		fputs("같습니다.\n", stdout);
	else
		fputs("다릅니다.\n", stdout);
}

void isEqual_strcmp(const char* s1, const char* s2)
{
	int res = strcmp(s1, s2);
	if (res == 0)
		fputs("같습니다.\n", stdout);
	else
		fputs("다릅니다.\n", stdout);
}

void Example20_09()
{
	const char* s1 = "My name ";
	const char* s2 = "My name";
	const char* s3 = "My name";
	const char* s4 = "My ";

	fputs("s1과 s2 비교: ", stdout);
	isEqual_strcmp(s1, s2);
	fputs("s1과 s2 를 일부 비교: ", stdout);
	isEqual_strncmp(s1, s2, 7);
	fputs("s2와 s3 를 일부 비교: ", stdout);
	isEqual_strncmp(s3, s2, 100);
	isEqual_strncmp(s3, s2, 8);
	isEqual_strncmp(s3, s2, 7);
	isEqual_strcmp(s3, s2);

	fputs("s3와 s4의 일부 비교: ", stdout);
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
		fputs("입력 버퍼 비우기\n", stdout);
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
		fputs("입력 버퍼 비우기\n", stdout);
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
		fputs("이름이 다릅니다. \n", stdout);
	else if (0 == strncmp(str1, str2, nameLen1))
		fputs("이름이 같습니다. \n", stdout);
	else
		fputs("이름이 다릅니다. \n", stdout);

	
	age1 = atoi(&str1[nameLen1 + 1]);
	age2 = atoi(&str2[nameLen2 + 1]);
	if (age1 != age2)
		fputs("나이가 다릅니다. \n", stdout);
	else
		fputs("나이가 같습니다. \n", stdout);
	
}