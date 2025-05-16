#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <memory.h>
#include <Sddl.h>
#include <strsafe.h>
#include <conio.h>

#pragma comment (lib, "ws2_32")

#include "ch3.h"

// 이미 수행되고 있는 인스턴스가 있는지를 확인하기 위한 뮤텍스, 바운더리, 네임스페이스
HANDLE g_hSingleton = NULL;
HANDLE g_hBoundary = NULL;
HANDLE g_hNamespace = NULL;

// 네임스페이스가 생성되었는지 혹은 정리를 위해 오픈되었는지 여부
BOOL g_bNamespaceOpend = FALSE;

// 바운더리 이름과 프라이비트 네임스페이스 이름
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

	// 로컬 관리자 SID값을 바운더리 디스크립터에 추가함
	// --> 로컬 관리자 권한으로 애플리케이션이 수행될 경우에만
	//     동일 네임스페이스 내의 커널 오브젝트에 접근이 가능
	if (!AddSIDToBoundaryDescriptor(&g_hBoundary, pLocalAdminSID))
	{
		wprintf_s(L"AddSIDToBoundaryDescriptor failed: %u\n", GetLastError());
		return;
	}

	// 로컬 관리자만을 위한 네임스페이스 생성
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

	// 보안 디스크립터가 저장된 메모리 공간을 해제하는 것을 잊어서는 안된다.
	LocalFree(sa.lpSecurityDescriptor);

	// 프라이비트 네임스페이스 생성 결과 확인
	DWORD dwLastError = GetLastError();
	if (g_hNamespace == NULL)
	{	// 접근이 거부되는 경우 아무것도 하지 않음
		// --> 이 코드는 로컬 관리자 계정 하에서 수행되어야 한다.
		if (dwLastError == ERROR_ACCESS_DENIED)
		{
			wprintf_s(L"네임스페이스 만들 때 접근 거부됨.\n");
			wprintf_s(L"관리자로 실행해라 !!\n");
			return;
		} //else
		else
		{
			if (dwLastError == ERROR_ALREADY_EXISTS)
			{
				// 만일 다른 인스턴스가 동일한 네임스페이스를 이미 생성했다면
				// 생성된 네임스페이스를 오픈
				wprintf_s(L"네임스페이스 만들기실패: %u\n", dwLastError);
				g_hNamespace = OpenPrivateNamespaceW(g_hBoundary, g_szNamespace);
				if (g_hNamespace == NULL)
				{
					wprintf_s(L"OpenPrivateNamespace 실패: %u\n", GetLastError());
					return;
				}
				g_bNamespaceOpend = TRUE;
				wprintf_s(L"기존꺼 열었어\n");
			}
			else
			{
				wprintf_s(L"무슨 오류일까? %u\n", GetLastError());
				return;
			}
		}
	}

	// 프라이빗 넴스페스에 기반한 뮤텍스 오브젝트 생성
	wchar_t szMutexName[64];
	StringCchPrintfW(szMutexName, _countof(szMutexName), L"%s\\%s", g_szNamespace, L"Singlton");

	g_hSingleton = CreateMutexW(NULL, FALSE, szMutexName);
	if (GetLastError() == ERROR_ALREADY_EXISTS)
		wprintf_s(L"이미 싱글턴 인스턴스가 존재함.\n");
	else
		wprintf_s(L"최초로 만들어진 싱글턴 뮤텍스\n");
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
	wprintf_s(L"실행시도!\n");
	HANDLE hMutex = CreateMutexW(NULL, FALSE, L"MY_SINGLETON_GLOBAL_MUTEX");
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{

		wprintf_s(L"음 이미 실행중이야\n");
		return 0;
	}
	else
	{
		wprintf_s(L"실행시작!\n");
	}
	return 0;
}