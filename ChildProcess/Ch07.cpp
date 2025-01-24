#include <iostream>
#include <tchar.h>
#include <Windows.h>
#include "Ch07.h"

int MailReceiver()
{
	HANDLE hMailSlot;	// mailslot handle
	TCHAR messageBox[50];	//mailslot buffer
	DWORD bytesRead;	//number of bytes read

	//mailslot 생성
	hMailSlot = CreateMailslot(
		SLOT_NAME,	// 이름
		0,			// 버퍼사이즈, 시스템 허용 최대크기
		MAILSLOT_WAIT_FOREVER, //최대 블로킹 시간, 데이터 없을경우 얼마나 기다릴건지
		NULL		// 핸들 상속
	);

	if (hMailSlot == INVALID_HANDLE_VALUE)
	{
		_fputts(_T("Unable to create mailslot!\n"), stdout);
		return 1;
	}

	//메시지 수신
	_fputts(_T("******** Message ********\n"), stdout);
	while (1)
	{	// 읽기에 실패한다면
		if (!ReadFile(hMailSlot, messageBox, sizeof(TCHAR) * 49, &bytesRead, NULL))
		{
			_fputts(_T("Unable to read!"), stdout);
			CloseHandle(hMailSlot);
			return 1;
		}

		// 0으로 종료되지 않을 수 있기 때문에 4로 끊었다. exit는 4글자이므로 괜찮음
#pragma warning(push)
#pragma warning(disable : C6054)
		if (!_tcsncmp(messageBox, _T("exit"), 4))
#pragma warning(pop)
		{	// 종료메시지가 있다면
			_fputts(_T("Good Bye!"), stdout);
			break;
		}

		// 위에서 49 개만 읽어서 넣을 수 있다.
#pragma warning(push)
#pragma warning(disable : C6386)
		messageBox[bytesRead / sizeof(TCHAR)] = 0;	//NULL문자 삽입
#pragma warning(pop)
		_fputts(messageBox, stdout);
	}
	CloseHandle(hMailSlot);
	return 0;
}

int PartAdder(int argc, TCHAR* argv[])
{
	if (argc != 3)
		return -1;

	DWORD start = _ttoi(argv[1]);
	DWORD end = _ttoi(argv[2]);

	DWORD total = 0;
	for (DWORD i = start; i <= end; i++)
		total += i;
	return total;
}