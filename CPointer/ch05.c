#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

/*
** 포인터와 문자열 **
1.	상수메모리와 배열의 차이
	상수메모리: 수정 불가한 메모리 영역. 문자열이 저장된다.
	배열: 수정 가능함.

2.	값을 읽는 기준 (배열, 상수메모리 동일), printf와 puts사용
	NULL문자('\0')이 발견되면 읽는 것을 중지한다.


3.	알면 좋은 참고사항
	1)	1		: 정수 1(10진수)
	2)	'1'		: 한 문자 1 (ASCII기준 49)
	3)	"1"		: 1이 저장된 상수 문자열 ('1'+'\0')
	4)	"123"	: 123이 저장된 상수 문자열 ('1'+'2'+'3'+'\0')
	5)	'\0'	: 한 문자 \0 (ASCII기준 0)
	6)	'0'		: 한 문자 0 (ASCII기준 48)
	7)	' '		: 한 문자 (공백) (ASCII기준 32)
	8)	''		: 한 문자지만 컴파일 오류
	9)	" "		: 공백이 저장된 상수 문자열 (' ' + '\0')
	10)	""		: NULL문자열 ('\0')
	11)	NULL	: 주소 0 ((void*)0 or 0)으로 정의되어 있다. 컴파일시간에 치환된다.

4.	*와 [] 사용해서 읽어보기	(이전과 같음. 중요한 것은 \0을 만나면 더이상 출력하지 않는다!)

*/

void Ch05_01()
{
	char* cp = "ABCD";
	char str[] = "ABCD";
	char str2[10] = "ABCD";
	char str3[10] = { 'A', 'B', 'C', 'D', '\0' };

	printf("%d, %d, %d, %d \n\n", (int)sizeof(cp), (int)sizeof(str), (int)sizeof(str2), (int)sizeof(str3));
	printf(" %s\n %s\n %s\n %s \n\n", cp, str, str2, str3);
	
	// *(cp + 1) = 'D';		컴파일 오류(쓰기 엑세스 위반 - 수정 불가능한 상수 메모리)
	str[4] = 'E';
	printf("%s\n\n", str);	//공백문자가 없으니 이상한 문자 출력

	str2[7] = 'E';
	printf("%s\n\n", str2);	//공백문자가 4에 있으므로 E를 출력하지 못함
	str2[4] = (char)32;
	str2[9] = '\0';
	puts(str2);				//공백문자를 뒤로 옮겨보기
	puts("\n\n");			//안되는 이유 : str2의 5~9까지 0으로 채워져있음
	printf("%d %d %d %d %d %d\n\n", str2[4], str2[5], str2[6], str2[7], str2[8], str2[9]);
	str2[5] = '5'; str2[6] = '6';
	puts(str2);
	puts("\n\n");

	// str3 빈 공간은 공백문자일까?
	for (int i = 0; i < 10; i++)
	{
		putchar(*(str3 + i));
		if(*(str3 + i) == '\0')
			putchar('n');
		else
			putchar('\t');
	}
	// 그렇다.


}

void Ch05_02()
{
	int i = 0x434241;
	int arr[3] = { 0x44434241, 0x48204645, 0x004b4a49 };	//00이 없어도 되지만 가시성 확보 (004b4a49 == 4b4a49 이므로)
	// 0x20 (=32) 은 ' ' (스페이스, 공백)문자이다.
	char* ip = (char*)&i;
	char* arrp = (char*)arr;	//arr에 저장된 첫주소 = &arr 과 같다.
	// == char* arrp = (char*)&arr

	printf("%s \n\n", ip);
	printf("%s \n\n", arrp+4);
	// NULL문자가 나올 때 까지 읽는다.
}

void Ch05_03()
{
	char c1 = 1;
	char c = '1';
	char* s = "1";
	char* s2 = "123";

	printf("%x %x %x %x \n\n", (int)c1, (int)c, *(short*)s, *(int*)s2);
	for (int i = 0; i < 10; i++)
	{
		printf("%X \n", s[i]);
	}
	printf("%d", (int)sizeof(s2));


	/*
	s의 구조
	[31]<- '1'
	[00]<- '0'
	[--]<- 쓰레기값 (0이 나오는 이유는 모르겠다.)
	[--]<- 쓰레기값 (0이 나오는 이유는 모르겠다.)

	여기서 *(short*)s의 값은 0x0031
	*/
	puts("\n");
	char* s3 = " ";
	printf("%x %x %x \n\n", *s3, *(s3 + 1), *(short*)s3);
	/*
	[20]<- ' '
	[00]<- '\0'	//short로 읽으면 0x0020
	*/

	char* s4 = "";
	printf("%x \n\n", *s4);

	printf("%d %d \n\n", (int)NULL, (int)'\0');
}

void Ch05_04()
{
	char arr[10] = "abcd";

	printf("%s == %s", arr, &arr);
}