#include <iostream>
#include <windows.h>
#include "027_CacheProfile.h"
#undef CACHE

CacheProfile::CacheProfile()
{
	_cache = new cachequeue[CACHE_LINENUM];
	char fileName[64];
	tm tm;
	time_t mytime = time(NULL);
	localtime_s(&tm, &mytime);
	sprintf_s(fileName, "CacheProfile_%04d%02d%02d_%02d%02d%02d.txt", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_wday,
		tm.tm_hour, tm.tm_min, tm.tm_sec);
	fopen_s(&_file, fileName, "w");
}

CacheProfile::~CacheProfile()
{
	fclose(_file);
	delete[] _cache;
}

void CacheProfile::push(const char* file, int line, const void* rd, size_t szrd, const void* wt, size_t szwt)
{
	int rdidx;
	int wtidx;
	const char* pr = (const char*)rd;
	const char* prf = (const char*)rd;
	const char* pw = (const char*)wt;
	for (pr = (const char*)rd; pr < prf + szrd; pr += 64)
	{
		if (wt != nullptr && szwt != 0)
		{	//write a to b
			rdidx = ((int)pr & 0x00000FC0) >> 6;
			wtidx = ((int)pw & 0x00000FC0) >> 6;

			if(_cache[rdidx].isHit(pr))
			{	//cache hit
				fprintf_s(_file, "%20s : line = %d, filename = %s\n", "rd CACHE HIT!", line, file);
			}
			else
			{	//cache miss
				_cache[rdidx].push(pr);
				fprintf_s(_file, "%20s : line = %d, filename = %s\n", "rd CACHE MISS!", line, file);
			}

			if (_cache[wtidx].isHit(pw))
			{	//cache hit
				fprintf_s(_file, "%20s : line = %d, filename = %s\n", "wt CACHE HIT!", line, file);
			}
			else
			{	//cache miss
				_cache[wtidx].push(pw);
				fprintf_s(_file, "%20s : line = %d, filename = %s\n", "wt CACHE MISS!", line, file);
			}
			pw += 64;
		}
		else
		{	//read only or write immediate variable
			rdidx = ((int)pr & 0x00000FC0) >> 6;	// 인덱스 추출

			if (_cache[rdidx].isHit(pr))
			{	//cache hit
				fprintf_s(_file, "%20s : line = %d, filename = %s\n", "CACHE HIT!", line, file);
			}
			else
			{	//cache miss
				_cache[rdidx].push(pr);
				fprintf_s(_file, "%20s : line = %d, filename = %s\n", "CACHE MISS!", line, file);
			}
		}
	}
	
}


void cachequeue::push(const void* ptr)
{
	if (_cnt == CACHE_WAYS)
	{
		pop();
	}
	_line[_f].ptr = ptr;
	_f++;
	_cnt++;
	if (_f == CACHE_WAYS)
		_f = 0;
}

void cachequeue::pop()
{
	if (_cnt == 0)
	{
		return;
	}
	_r++;
	_cnt--;
	if (_r == CACHE_WAYS)
		_r = 0;
}

bool cachequeue::isHit(const void* ptr) const
{	//태그 비교
	bool find = false;
	int i = _r;
	int cnt = _cnt;
	while(cnt != 0)
	{
		if (((unsigned long long)_line[i].ptr >> 12) == ((unsigned long long)ptr >> 12))
		{
			find = true;
			break;
		}
		i++;
		if (i == CACHE_WAYS)
			i = 0;
		cnt--;
	}
	return find;
}