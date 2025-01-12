#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <tchar.h>
#include <Windows.h>
#include "Ch03.h"

static UINT CallDist(UINT a, UINT b)
{
	return a - b;
}

static UINT_PTR CallDistance(UINT_PTR a, UINT_PTR b)
{
	return a - b;
}

void Ex01()
{
	INT val1 = 10;
	INT val2 = 20;

	_tprintf(_T("Position %x, %x \n"), (UINT)&val1, (UINT)&val2);
	_tprintf(
		_T("Distance : %x \n"), CallDist((UINT)&val1, (UINT)&val2)
	);
}

void Ex02()
{
	UINT_PTR a = 1;
	UINT_PTR b = 2;

	_tprintf(_T("Position %llx, %llx\n"), (UINT_PTR)&a, (UINT_PTR)&b);
	_tprintf(
		_T("Distance : %x \n"), CallDistance((UINT_PTR)&a, (UINT_PTR)&b)
	);
}

void Ex03()
{
	HANDLE hFile = CreateFile(	//Windows 시스템 함수
		_T("ABC.DAT"), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,
	NULL );
	if (hFile == INVALID_HANDLE_VALUE)
	{
		_tprintf(_T("error code: %d \n"), GetLastError());
		// error code 2 :  The system cannot find the file specified
	}
}

void Ex04()
{
	HANDLE hFile = CreateFile(	// GetLastError() 로 반드시 에러 호출을 하기를 바란다.
		_T("ABC2.DAT"), GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL,
	NULL);
	_tprintf(_T("error code: %d \n"), GetLastError());
	//존재하는 파일이라면 실행 시 80오류가 난다. : The file exists
}