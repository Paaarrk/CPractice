#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <memory.h>
#include <Sddl.h>
#include <strsafe.h>
#include <conio.h>

#pragma comment (lib, "ws2_32")

#include "ch3.h"

// �̹� ����ǰ� �ִ� �ν��Ͻ��� �ִ����� Ȯ���ϱ� ���� ���ؽ�, �ٿ����, ���ӽ����̽�
HANDLE g_hSingleton = NULL;
HANDLE g_hBoundary = NULL;
HANDLE g_hNamespace = NULL;

// ���ӽ����̽��� �����Ǿ����� Ȥ�� ������ ���� ���µǾ����� ����
BOOL g_bNamespaceOpend = FALSE;

// �ٿ���� �̸��� �����̺�Ʈ ���ӽ����̽� �̸�
LPCWSTR g_szBoundary = L"3-Boundary";
const wchar_t* g_szNamespace = L"3-Namespace";

static void CheckInstances()
{
	g_hBoundary = CreateBoundaryDescriptorW(g_szBoundary, 0);

	u_char localAdminSID[SECURITY_MAX_SID_SIZE];
	PSID pLocalAdminSID = &localAdminSID;
	DWORD cbSID = sizeof(localAdminSID);
	if (!CreateWellKnownSid(WinBuiltinAdministratorsSid, NULL, pLocalAdminSID, &cbSID))
	{
		wprintf_s(L"AddSIDToBoundaryDescriptor failed: %u\n", GetLastError());
		return;
	}

	// ���� ������ SID���� �ٿ���� ��ũ���Ϳ� �߰���
	// --> ���� ������ �������� ���ø����̼��� ����� ��쿡��
	//     ���� ���ӽ����̽� ���� Ŀ�� ������Ʈ�� ������ ����
	if (!AddSIDToBoundaryDescriptor(&g_hBoundary, pLocalAdminSID))
	{
		wprintf_s(L"AddSIDToBoundaryDescriptor failed: %u\n", GetLastError());
		return;
	}

	// ���� �����ڸ��� ���� ���ӽ����̽� ����
	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(sa);
	sa.bInheritHandle = FALSE;
	if (!ConvertStringSecurityDescriptorToSecurityDescriptorW(
		L"D:(A;;GA;;;BA)", SDDL_REVISION_1, &sa.lpSecurityDescriptor, NULL))
	{
		wprintf_s(L"Security Descriptor creation failed: %u\n", GetLastError());
		return;
	}

	g_hNamespace = CreatePrivateNamespaceW(&sa, g_hBoundary, g_szNamespace);

	// ���� ��ũ���Ͱ� ����� �޸� ������ �����ϴ� ���� �ؾ�� �ȵȴ�.
	LocalFree(sa.lpSecurityDescriptor);

	// �����̺�Ʈ ���ӽ����̽� ���� ��� Ȯ��
	DWORD dwLastError = GetLastError();
	if (g_hNamespace == NULL)
	{	// ������ �źεǴ� ��� �ƹ��͵� ���� ����
		// --> �� �ڵ�� ���� ������ ���� �Ͽ��� ����Ǿ�� �Ѵ�.
		if (dwLastError == ERROR_ACCESS_DENIED)
		{
			wprintf_s(L"���ӽ����̽� ���� �� ���� �źε�.\n");
			wprintf_s(L"�����ڷ� �����ض� !!\n");
			return;
		} //else
		else
		{
			if (dwLastError == ERROR_ALREADY_EXISTS)
			{
				// ���� �ٸ� �ν��Ͻ��� ������ ���ӽ����̽��� �̹� �����ߴٸ�
				// ������ ���ӽ����̽��� ����
				wprintf_s(L"���ӽ����̽� ��������: %u\n", dwLastError);
				g_hNamespace = OpenPrivateNamespaceW(g_hBoundary, g_szNamespace);
				if (g_hNamespace == NULL)
				{
					wprintf_s(L"OpenPrivateNamespace ����: %u\n", GetLastError());
					return;
				}
				g_bNamespaceOpend = TRUE;
				wprintf_s(L"������ ������\n");
			}
			else
			{
				wprintf_s(L"���� �����ϱ�? %u\n", GetLastError());
				return;
			}
		}
	}

	// �����̺� �۽��佺�� ����� ���ؽ� ������Ʈ ����
	wchar_t szMutexName[64];
	StringCchPrintfW(szMutexName, _countof(szMutexName), L"%s\\%s", g_szNamespace, L"Singlton");

	g_hSingleton = CreateMutexW(NULL, FALSE, szMutexName);
	if (GetLastError() == ERROR_ALREADY_EXISTS)
		wprintf_s(L"�̹� �̱��� �ν��Ͻ��� ������.\n");
	else
		wprintf_s(L"���ʷ� ������� �̱��� ���ؽ�\n");
	return;
}

int Singleton()
{
	CheckInstances();

	if (g_hSingleton != NULL)
		CloseHandle(g_hSingleton);

	if (g_hNamespace != NULL)
	{
		if (g_bNamespaceOpend)
		{
			ClosePrivateNamespace(g_hNamespace, 0);
		}
		else
		{
			ClosePrivateNamespace(g_hNamespace, PRIVATE_NAMESPACE_FLAG_DESTROY);
		}
	}

	if (g_hBoundary != NULL)
	{
		DeleteBoundaryDescriptor(g_hBoundary);
	}

	char c = _getch();
	return 0;
}

int Singleton2()
{
	wprintf_s(L"����õ�!\n");
	HANDLE hMutex = CreateMutexW(NULL, FALSE, L"MY_SINGLETON_GLOBAL_MUTEX");
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{

		wprintf_s(L"�� �̹� �������̾�\n");
		return 0;
	}
	else
	{
		wprintf_s(L"�������!\n");
	}
	return 0;
}