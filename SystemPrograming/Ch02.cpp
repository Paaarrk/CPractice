#define _CRT_SECURE_NO_WARNINGS
//#ifndef UNICODE
//#define UNICODE
//#define _UNICODE
//#endif
#include <iostream>
#include "Ch02.h"
#include <tchar.h>
#include <Windows.h>
static void Ex01()
{
	// MBCS
	char str[] = "ABC한글";
	int size = sizeof(str);
	int len = strlen(str);

	printf("%d, %d\n\n", size, len);
}

static void Ex02()
{
	// WBCS
	wchar_t str[] = L"ABC하";
	int size = sizeof(str);
 	int len = wcslen(str); 

	printf("%d, %d", size, len);
}

static void Ex03()
{
	// 한글 출력
	_wsetlocale(LC_ALL, L"korean");
	wchar_t str[] = L"ABC하つゆ";
	int size = sizeof(str);
	int len = wcslen(str);

	wprintf(L"%s \n", str);
	wprintf(L"%d \n", size);
	wprintf(L"%d \n", len);
}

static void Ex04()
{
	LPCSTR str1 = "SBCS Style String 1";
	LPCWSTR str2 = L"WBCS Style String 1";

	CHAR arr1[] = "SBCS Style String 2";
	WCHAR arr2[] = L"WBCS Style String 2";

	LPCSTR cstr1 = arr1;
	LPCWSTR cstr2 = arr2;

	printf("%s\n", str1);
	printf("%s\n", arr1);
	fputs("\n", stdout);
	wprintf(L"%s\n", str2);
	wprintf(L"%s\n", arr2);

}

static void Ex05()
{
	//_tsetlocale(LC_ALL, L"korean");
	LPCTSTR str1 = _T("MBCS or WBCS 1");
	TCHAR str2[] = _T("MBCS or WBCS 2");
	TCHAR str3[100];
	TCHAR str4[50];

	LPCTSTR pStr = str1;

	_tprintf(_T("string size: %d \n"), (int)sizeof(str2));
	_tprintf(_T("string length: %d \n"), (int)_tcslen(str2));

	_fputts(_T("Input String 1 : "), stdout);
	_tscanf(_T("%s"), str3);
	_fputts(_T("InputString 2 : "), stdout);
	_tscanf(_T("%s"), str4);

	_tcscat(str3, str4);
	_tprintf(_T("String1 + String2 : %s \n"), str3);
}
