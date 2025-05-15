#include <windows.h>
#include <stdio.h>

#include "CH19.h"

static int CommToClient(HANDLE hPipe);

int S_OverlappedIO()
{
	LPCWSTR pipeName = L"\\\\.\\pipe\\simple_piple";
	HANDLE hPipe;

	while (1)
	{
		hPipe = CreateNamedPipeW(
			pipeName,
			PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED,
			PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
			PIPE_UNLIMITED_INSTANCES,
			BUF_SIZE / 2,
			BUF_SIZE / 2,
			20000, NULL
		);
		if (hPipe == INVALID_HANDLE_VALUE)
		{
			wprintf_s(L"[%d]GetLastError: %d", __LINE__, GetLastError());
			return -1;
		}

		if (ConnectNamedPipe(hPipe, NULL) == false)
		{
			wprintf_s(L"[%d]GetLastError: %d", __LINE__, GetLastError());
			CloseHandle(hPipe);
			return -1;
		}

		if (CommToClient(hPipe))
		{
			wprintf_s(L"[%d]GetLastError: %d", __LINE__, GetLastError());
			CloseHandle(hPipe);
			return -1;
		}
	}

	return 0;
}


int C_OverlappedIO()
{


	return 0;
}









static int CommToClient(HANDLE hPipe)
{
	wchar_t fileName[MAX_PATH];
	wchar_t dataBuf[BUF_SIZE];
	BOOL isSuccess;
	DWORD fileNameSize;

	isSuccess = ReadFile(
		hPipe, fileName, MAX_PATH * sizeof(wchar_t), &fileNameSize, NULL
	);

	if (!isSuccess || fileNameSize == 0)
	{
		return 222;
	}

	FILE* filePtr;
	_wfopen_s(&filePtr, fileName, L"r", );
	if (filePtr == nullptr)
	{
		return 222;
	}

	OVERLAPPED overlappedInst;
	memset(&overlappedInst, 0, sizeof(overlappedInst));


}