#ifndef __DEBUG_NEW_DELETE_H__
#define __DEBUG_NEW_DELETE_H__
#define MAX_NUM			1000
#define HANDLER_FULL	0x00000923
#define DELETED			0x10000000
#define FILE_NAME_LEN	128

#define _DEBUG_NEW

struct AllocInfo
{
	void* ptr;
	int size;
	char filename[FILE_NAME_LEN];
	int line;
	bool array;
};

enum Error
{ //Array도 Leak의 한 종류 (배열을 일반으로 해제 혹은 일반을 배열로 해제)
	NOALLOC = 0, ARRAY, LEAK
};

class AllocInfoHandler
{
public:
	static AllocInfoHandler& getInstance()
	{
		static AllocInfoHandler instance;
		return instance;
	}
	bool push(void* ptr, size_t size, const char* file, int line, bool array);
	int find(void* ptr, bool array);
	bool Delete(void** p, bool array);
private:
	AllocInfoHandler() {
		char fileName[FILE_NAME_LEN * 2];
		tm tm;
		time_t mytime = time(NULL);
		localtime_s(&tm, &mytime);
		sprintf_s(fileName, "AllocLog_%04d%02d%02d_%02d%02d%02d.txt", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_wday,
			tm.tm_hour, tm.tm_min, tm.tm_sec);
		fopen_s(&file, fileName, "w");
	}
	~AllocInfoHandler() {
		for (int i = 0; i < cnt; i++)
		{
			if (arr[i].ptr != (void*)DELETED)
			{
				write(LEAK, arr[i].ptr, i);
			}
		}
		fclose(file);
	}
	AllocInfoHandler(AllocInfoHandler&){}
	AllocInfoHandler& operator=(const AllocInfoHandler&) {}
	void write(Error err, void* ptr, int idx);
	bool getAllocArray(int idx)	const;

	AllocInfo arr[MAX_NUM] = {};
	int cnt = 0;
	FILE* file;
};

void* operator new(size_t size, const char *File, int Line);
void* operator new[](size_t size, const char *File, int Line);
void operator delete(void* p);
void operator delete[](void* p);
void operator delete(void* p, char* File, int Line);
void operator delete[](void* p, char* File, int Line);

#ifdef _DEBUG_NEW
#define new new(__FILE__, __LINE__)
#endif
#endif