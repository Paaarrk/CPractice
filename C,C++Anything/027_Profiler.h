#ifndef __027_PROFILER_H__
#define __027_PROFILER_H__
#define _PROFILE
#define TAGS_CAPACITY	67	// �±� �迭�� ũ�� (�ݵ�� �Ҽ� ���)

/* hash�ε��� ��ȯ */
unsigned int hash(const char* str);
void ProfileBegin(const char* tag);
void ProfileEnd(const char* tag);
void ClearProfiles();

#ifdef _PROFILE
	#define	PRO_BEGIN(TagName)		ProfileBegin(TagName)
	#define PRO_END(TagName)		ProfileEnd(TagName)
	#define PRO_EXIT()				ClearProfiles()
#else
	#define PRO_BEGIN(TagName)
	#define PRO_END(TagName)				
	#define PRO_EXIT()
#endif

/* ������, �Ҹ����� Ư���� �̿���. �Լ� ���� ���� �� ���
   ������ Profile p1(tag) */
class Profile
{
public:
	Profile(const char* tag)
	{
		PRO_BEGIN(tag);
		_tag = tag;
	}
	~Profile()
	{
		PRO_END(_tag);
	}
private:
	const char* _tag;
};

/* �������� ����ü */
struct ST_PROFILE
{
	const char* name;
	ST_PROFILE* next;
	__int64		liTotalTime;
	__int64		liStartTime;
	__int64		liMin[2];
	__int64		liMax[2];
	__int64		liCallCnt;
	ST_PROFILE():name(nullptr), liTotalTime(0), liStartTime(0),
		liCallCnt(0), next(nullptr)
	{
		liMin[0] = 0; liMin[1] = 0;
		liMax[0] = 0; liMax[1] = 0;
	}
};
#endif