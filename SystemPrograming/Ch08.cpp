#include <stdio.h>
#include <Windows.h>
#include <tchar.h>
#include "Ch08.h"

#define BUF_SIZE 1024

int AnonymousPipe()
{
	/*
		�̸� ���� �������� �⺻ ���� �ľ�
	*/

	HANDLE hReadPipe;
	HANDLE hWritePipe;

	TCHAR sendString[] = _T("anonymous pipe");
	TCHAR recvString[100];

	DWORD bytesWritten;
	DWORD bytesRead;

	BOOL success = TRUE;

	/* ������ ���� */
	success &= CreatePipe(&hReadPipe, &hWritePipe, NULL, 0);	//������ �۰� �϶�� ��
	if (success == TRUE)
		_tprintf_s(_T("CreatePipe!! readHandle: %p, writeHandle: %p\n"), hReadPipe, hWritePipe);

	/* ������ ���� ���� �̿��� ������ �۽� */
	success &= WriteFile(
		hWritePipe, sendString, lstrlen(sendString) * sizeof(TCHAR), &bytesWritten, NULL);
	if(success == TRUE)
		_tprintf_s(_T("string send: %s \n"), sendString);

	/* ������ ���� ���� �̿��� ������ ���� */
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