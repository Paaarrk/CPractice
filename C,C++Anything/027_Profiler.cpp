#include <windows.h>
#include <iostream>
#include "027_Profiler.h"
static ST_PROFILE profiles[TAGS_CAPACITY];
static int profileNumInIdx[TAGS_CAPACITY] = { 0, };
static FILE* file;
static ST_PROFILE* GetProfile(const char* tag)
{
	if (tag == nullptr)
	{
		return nullptr;
	}
	ST_PROFILE* value = nullptr;
	unsigned int idx = hash(tag);
	if (profileNumInIdx[idx] == 0)
	{
		profileNumInIdx[idx]++;
		profiles[idx].name = tag;
		value = &profiles[idx];
	} 
	else if (profileNumInIdx[idx] == 1)
	{
		if (strcmp(profiles[idx].name, tag) == 0)
		{
			value = &profiles[idx];
		}
		else
		{
			profiles[idx].next = new ST_PROFILE;
			value = profiles[idx].next;
			value->name = tag;
			profileNumInIdx[idx]++;
		}
	}
	else
	{
		bool find = false;
		ST_PROFILE* p;
		ST_PROFILE* b = nullptr;
		for (p = &profiles[idx]; p != nullptr; p = p-> next)
		{
			b = p;
			if (strcmp(p->name, tag) == 0)
			{
				find = true;
				value = p;
				break;
			}
		}
		if (find == false)
		{
			b->next = new ST_PROFILE;
			value = b->next;
			value->name = tag;
			profileNumInIdx[idx]++;
		}
	}
	
	return value;
}
static int compare(const void* a, const void* b)
{
	__int64* val1 = (__int64*)a;
	__int64* val2 = (__int64*)b;
	if (*val1 < *val2)return -1;
	else return 1;
}
static bool Write()
{
	char fileName[64];
	tm tm;
	time_t mytime = time(NULL);
	localtime_s(&tm, &mytime);
	sprintf_s(fileName, "Profile_%04d%02d%02d_%02d%02d%02d.txt", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_wday,
		tm.tm_hour, tm.tm_min, tm.tm_sec);
	fopen_s(&file, fileName, "w");
	if (file == nullptr)
		return false;

	LARGE_INTEGER freq;
	QueryPerformanceFrequency(&freq);

	fprintf_s(file, "+----------------------------+-------------------+-------------------+-------------------+-------------------+\n");
	fprintf_s(file, "|%27s |%18s |%18s |%18s |%18s |\n", "Name", "Average", "Min", "Max", "Call");
	fprintf_s(file, "+----------------------------+-------------------+-------------------+-------------------+-------------------+\n");
	double avg;
	double min;
	double max;
	for (int i = 0; i < TAGS_CAPACITY; i++)
	{
		if (profileNumInIdx[i] != 0)
		{
			for (ST_PROFILE* p = &profiles[i]; p != nullptr; p = p->next)
			{
				if (p->liCallCnt == 0)
				{
					avg = 0;
				}
				else if (p->liCallCnt < 4)
					avg = (double)(p->liTotalTime) / freq.QuadPart / (p->liCallCnt) * 1000000;
				else
					avg = (double)(p->liTotalTime - p->liMin[0] - p->liMin[1] - p->liMax[0] - p->liMax[1]) / freq.QuadPart / (p->liCallCnt - 4) * 1000000;
				
				min = (double)p->liMin[0] / freq.QuadPart * 1000000;
				max = (double)p->liMax[1] / freq.QuadPart * 1000000 ;
				fprintf_s(file, "|%27s |%16.4lf§Á |%16.4lf§Á |%16.4lf§Á |%18lld |\n", p->name, avg, min, max, p->liCallCnt);
			}
		}
	}
	fprintf_s(file, "+----------------------------+-------------------+-------------------+-------------------+-------------------+\n");
	fclose(file);
	return true;
}
static bool Clear()
{
	for (int i = 0; i < TAGS_CAPACITY; i++)
	{
		if (profileNumInIdx[i] != 0)
		{
			for (ST_PROFILE* p = &profiles[i]; p != nullptr; p = p->next)
			{
				p->liCallCnt = 0;
				p->liMin[0] = 0;
				p->liMin[1] = 0;
				p->liMax[0] = 0;
				p->liMax[1] = 0;
				p->liStartTime = 0;
				p->liTotalTime = 0;
			}
		}
	}
	return true;
}

void ProfileEnd(const char* tag)
{
	LARGE_INTEGER end;
	QueryPerformanceCounter(&end);
	ST_PROFILE* myProfile = GetProfile(tag);
	__int64 deltatime = end.QuadPart - myProfile->liStartTime;
	myProfile->liTotalTime += deltatime;

	__int64 temp[5];
	temp[0] = myProfile->liMin[0];
	temp[1] = myProfile->liMin[1];
	temp[2] = myProfile->liMax[0];
	temp[3] = myProfile->liMax[1];
	temp[4] = deltatime;
	std::qsort(temp, 5, sizeof(__int64), compare);
	if (myProfile->liCallCnt < 4)
	{
		myProfile->liMin[0] = temp[1];
		myProfile->liMin[1] = temp[2];
		myProfile->liMax[0] = temp[3];
		myProfile->liMax[1] = temp[4];
	}
	else
	{
		myProfile->liMin[0] = temp[0];
		myProfile->liMin[1] = temp[1];
		myProfile->liMax[0] = temp[3];
		myProfile->liMax[1] = temp[4];
	}

	myProfile->liCallCnt++;

	if (GetAsyncKeyState(VK_SPACE))
	{
		Write();
	}
	else if (GetAsyncKeyState('R'))
	{
		Clear();
	}
}
void ProfileBegin(const char* tag)
{
	ST_PROFILE* myProfile = GetProfile(tag);
	LARGE_INTEGER start;
	QueryPerformanceCounter(&start);
	myProfile->liStartTime = start.QuadPart;
}
unsigned int hash(const char* str)
{
	unsigned int hash = 5381;
	while (*str) {
		hash = ((hash << 5) + hash) + *str;
		str++;
	}
	return hash % TAGS_CAPACITY;
}
void ClearProfiles()
{
	ST_PROFILE* pfs[TAGS_CAPACITY];
	int cnt = 0;
	for (int i = 0; i < TAGS_CAPACITY; i++)
	{
		if (profileNumInIdx[i] > 1)
		{
			for (ST_PROFILE* p = profiles[i].next; p != nullptr; p = p->next)
			{
				pfs[cnt++] = p;
			}
		}
	}
	for (int i = 0; i < cnt; i++)
	{
		delete pfs[i];
	}
}