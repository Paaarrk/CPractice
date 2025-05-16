#ifndef __CH3_H__
#define __CH3_H__

/*
	< 커널 오브젝트 >
	. 커널오브젝트에 대해 완벽한 이해 필요.
	. 여러 타입이 존재함, 타입마다 값들도 조금씩 다름
	. usage count, security descriptor은 공통적

	. 커널에 의해서만 접근이 가능해 왜? 일관성 유지 위해서
	
	. 커널 오브젝트 내부는 프로세스마다 독립적인 핸들을 받아 함수를 통해(정제된방법)일부 접근 가능
	  -> 커널모드로 전환되겠군

	1. 사용 카운트 (usage count)
	. 프로세스의 생명주기 <= 커널오브젝트의 생명주기
	  -> 프로세스가 꺼진다고 커널오브젝트가 무조건 꺼지는 것이 아님.
	  -> usage count로 관리됨.
	. 처음 생성된 프로세스의 usage count = 1  (근데 바탕화면도 있어서 결국 우리가 보는 값은 2이긴함)
	. 우리가 설정하는 값 아님.

	2. 보안 디스크립터 (security descriptor)
	. PSECURITY_ATTRIBUTES psa, (이런 식으로 받는 함수들이 있음)
	. NULL전달도 가능 (기본 default값)
	. 직접 세팅도 가능

	typedef struct _SECURITY_ATTRIBUTES {
		DWORD nLength;
		LPVOID lpSecurityDescriptor;	// 얘만 보안과 관련이 있다.
		BOOL bInheritHandle;
	}SECURITY_ATTRIBUTES;

	. 사실 세팅할 일 거의 없음
	-------------------------------------------------------------------------------------
	** 하지만 **
	. 레지스트리의 어떤 키로부터 값을 읽어와야 한다면?
	. RegOpenKeyEx 호출 시 KEY_QUERY_VALUE 전달 (읽기만 할게요)
	. KEY_ALL_ACCESS전달-> 관리자 권한 아니면 쓰기 불가, 하지만 쓰기 하겠다고 보내는 것
	. 호출 실패
	-------------------------------------------------------------------------------------
	
	3. 커널오브젝트와 유저오브젝트의 구분
	. psecurity_attributes 형의 매개변수가 없다면 (보안 특성 지정 매개변수가 없다면) 커널
	오브젝트가 아니다.



	일단 해보자 ㅋㅋ 뒤에 먼소린지 모르겠네
*/

// 음..싱글톤이안된다.
// GPT검색한 바로는 hBoundary가 항상 달라서 private namespace이름도 항상 달라져서 그렇다고함.
int Singleton();

int Singleton2();
#endif