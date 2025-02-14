#include <stdio.h>
#include <Windows.h>
#include <tchar.h>
#include <conio.h>
#include <TlHelp32.h>
#include "Ch08.h"

#define BUF_SIZE 1024

int AnonymousPipe()
{
	/*
		이름 없는 파이프의 기본 원리 파악
	*/

	HANDLE hReadPipe;
	HANDLE hWritePipe;

	TCHAR sendString[] = _T("anonymous pipe");
	TCHAR recvString[100];

	DWORD bytesWritten;
	DWORD bytesRead;

	BOOL success = TRUE;

	/* 파이프 생성 */
	success &= CreatePipe(&hReadPipe, &hWritePipe, NULL, 0);	//사이즈 작게 하라는 뜻
	if (success == TRUE)
		_tprintf_s(_T("CreatePipe!! readHandle: %p, writeHandle: %p\n"), hReadPipe, hWritePipe);

	/* 파이프 한쪽 끝을 이용한 데이터 송신 */
	success &= WriteFile(
		hWritePipe, sendString, lstrlen(sendString) * sizeof(TCHAR), &bytesWritten, NULL);
	if(success == TRUE)
		_tprintf_s(_T("string send: %s \n"), sendString);

	/* 파이프 한쪽 끝을 이용한 데이터 수신 */
	success &= ReadFile(
		hReadPipe, recvString, bytesWritten, &bytesRead, NULL);

	recvString[bytesRead / sizeof(TCHAR)] = '\0';
	if (success == TRUE)
		_tprintf_s(_T("String recv: %s \n"), recvString);

	CloseHandle(hReadPipe);
	CloseHandle(hWritePipe);
}

int CommToClient(HANDLE);

int NamedPipeServer()
{
	LPCTSTR pipeName = _T("\\\\.\\pipe\\simple_pipe");
	HANDLE hPipe;

	while (true)
	{
		hPipe = CreateNamedPipe(
			pipeName,
			PIPE_ACCESS_DUPLEX,
			PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
			PIPE_UNLIMITED_INSTANCES,
			BUF_SIZE,
			BUF_SIZE,
			20000,
			NULL
		);

		if (hPipe == INVALID_HANDLE_VALUE)
		{
			_tprintf_s(_T("Create Pipe Failed\n"));
			return -1;
		}

		BOOL isSuccess = 0;
		isSuccess = ConnectNamedPipe(hPipe, NULL)
			? TRUE : (GetLastError() == ERROR_PIPE_CONNECTED);

		if (isSuccess)
			CommToClient(hPipe);
		else
			CloseHandle(hPipe);
	}
	return 1;
}

int CommToClient(HANDLE hPipe)
{
	TCHAR fileName[MAX_PATH];
	TCHAR dataBuf[BUF_SIZE];

	BOOL isSuccess;
	DWORD fileNameSize;
	isSuccess = ReadFile(
		hPipe,
		fileName,
		MAX_PATH * sizeof(TCHAR),
		&fileNameSize,
		NULL);

	if (isSuccess == false || fileNameSize == 0)
	{
		_tprintf_s(_T("Pipe read message error! \n"));
		return -1;
	}


	FILE* filePtr;
	if (_tfopen_s(&filePtr, fileName, _T("r"))!= 0)
	{
		_tprintf_s(_T("File open fault! \n"));
		return -1;
	}

	DWORD bytesWritten = 0;
	DWORD bytesRead = 0;

	while (!feof(filePtr))
	{
		bytesRead = fread(dataBuf, 1, BUF_SIZE, filePtr);

		WriteFile(
			hPipe,
			dataBuf,
			bytesRead,
			&bytesWritten,
			NULL
		);

		if (bytesRead != bytesWritten)
		{
			_tprintf(_T("Pipe write message error! \n"));
			break;
		}
	}
	
	FlushFileBuffers(hPipe);
	DisconnectNamedPipe(hPipe);
	CloseHandle(hPipe);
	return 1;
}

int EnvParent()
{
	SetEnvironmentVariable(_T("Good"), _T("morning"));
	SetEnvironmentVariable(_T("Hey"), _T("Ho!"));
	SetEnvironmentVariable(_T("Big"), _T("Boy"));

	STARTUPINFO si = { 0, };
	PROCESS_INFORMATION pi = { 0, };
	si.cb = sizeof(si);

	TCHAR command[] = _T("EnvChild");
	CreateProcess(NULL, command, NULL, NULL,FALSE,
		CREATE_NEW_CONSOLE|CREATE_UNICODE_ENVIRONMENT,
		NULL	//lpEnvironment : 부모 프로세스의 환경변수 등록
		, NULL, &si, &pi);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	_getch();
	return 0;
}

int ListProcessInfo()
{
	HANDLE hProcessSnap =
		CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE)
	{
		_tprintf_s(_T("CreateToolhelp32Snapshot error! \n"));
		return -1;
	}

	// 프로세스 정보를 얻기 위한 구조체 변수
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(pe32);
	if (!Process32First(hProcessSnap, &pe32))
	{
		_tprintf_s(_T("Process32First error!\n"));
		CloseHandle(hProcessSnap);
		return -1;
	}

	do
	{
		/* 프로세스 이름, ID 정보 출력 */
		_tprintf_s(_T("%40s\t%5d \n"), 
			pe32.szExeFile, pe32.th32ProcessID);
		count++;
	} while (Process32Next(hProcessSnap, &pe32));
	CloseHandle(hProcessSnap);

	Sleep(10000);
	return 0;
}