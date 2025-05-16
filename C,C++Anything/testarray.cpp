#include <stdio.h>
#include <memory.h>
#include <string.h>
#include "027_Profiler.h"

#define NAME   "ababc"

static void noptr();
static void useptr();

#pragma pack(push)
#pragma pack(1)
struct user
{
	int id;
	bool s;
	char name[25];
};
#pragma pack(pop)

user g_user[10000];

int main()
{
	//useptr();

	return 0;
}

static void noptr()
{
	user* pUser;
	while (1)
	{
		{
			Profile pf("noptr");

			for (int i = 0; i < 10000; i++)
			{
				pUser = &g_user[i];
				pUser->id = i;
				pUser->s = 0;
				strcpy_s(pUser->name, NAME);
			}
		}
		printf_s(".");
	}
}

static void useptr()
{
	char* pUser = (char*)g_user;
	char* pUserend = (char*)(g_user + 10000);
	int i;
	while (1)
	{
		{
			Profile pf("ptr");
			i = 0;
			while (pUser != pUserend)
			{
				*((int*)pUser) = i++;
				pUser += 4;
				*((bool*)pUser) = 0;
				pUser++;
				strcpy_s(pUser, 25, NAME);
				pUser += 25;
			}
		}
		printf_s(".");
	}
}
