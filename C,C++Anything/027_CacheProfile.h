#ifndef __CACHE_PROFILE_H__
#define __CACHE_PROFILE_H__

#define CACHE_WAYS		12
#define CACHE_LINENUM	64

struct CacheLine
{
	const void* ptr;
	CacheLine() :ptr(nullptr) {}
};
class cachequeue
{
public:
	void push(const void* ptr);
	void pop();
	cachequeue() :_cnt(0), _r(0), _f(0) {}
	bool isHit(const void* ptr) const;
private:
	CacheLine _line[CACHE_WAYS];
	int _cnt;
	int _r;
	int _f;
};

class CacheProfile
{
public:
	static CacheProfile& getInstance()
	{
		static CacheProfile cp;
		return cp;
	}
	void push(const char* file, int line, const void* rd, size_t szrd, const void* w = nullptr, size_t szw = 0);
private:
	CacheProfile();
	~CacheProfile();
	CacheProfile(const CacheProfile& ref) = delete;
	CacheProfile& operator= (const CacheProfile& ref) = delete;
	cachequeue* _cache;
	FILE* _file;
};

#define CACHE	CacheProfile::getInstance()

#endif