#include <iostream>
#include <tchar.h>
#include <Windows.h>
#include "Ch07.h"

int MailReceiver()
{
	HANDLE hMailSlot;	// mailslot handle
	TCHAR messageBox[50];	//mailslot buffer
	DWORD bytesRead;	//number of bytes read

	//mailslot ����
	hMailSlot = CreateMailslot(
		SLOT_NAME,	// �̸�
		0,			// ���ۻ�����, �ý��� ��� �ִ�ũ��
		MAILSLOT_WAIT_FOREVER, //�ִ� ���ŷ �ð�, ������ ������� �󸶳� ��ٸ�����
		NULL		// �ڵ� ���
	);

	if (hMailSlot == INVALID_HANDLE_VALUE)
	{
		_fputts(_T("Unable to create mailslot!\n"), stdout);
		return 1;
	}

	//�޽��� ����
	_fputts(_T("******** Message ********\n"), stdout);
	while (1)
	{	// �б⿡ �����Ѵٸ�
		if (!ReadFile(hMailSlot, messageBox, sizeof(TCHAR) * 49, &bytesRead, NULL))
		{
			_fputts(_T("Unable to read!"), stdout);
			CloseHandle(hMailSlot);
			return 1;
		}

		// 0���� ������� ���� �� �ֱ� ������ 4�� ������. exit�� 4�����̹Ƿ� ������
#pragma warning(push)
#pragma warning(disable : C6054)
		if (!_tcsncmp(messageBox, _T("exit"), 4))
#pragma warning(pop)
		{	// ����޽����� �ִٸ�
			_fputts(_T("Good Bye!"), stdout);
			break;
		}

		// ������ 49 ���� �о ���� �� �ִ�.
#pragma warning(push)
#pragma warning(disable : C6386)
		messageBox[bytesRead / sizeof(TCHAR)] = 0;	//NULL���� ����
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