#ifndef __CH_13_H__
#define __CH_13_H__

/*
	유저 모드 동기화 기법
	1) Ciritical Section
	2) Interlocked Family of Function

	1) 아직 잘 안와닿는다. Enter시 무기한 대기(indefinetely wait...)
	뭔 느낌인지를 모르겠네
	. EnterCriticalSection과 leaveCriticalSection을 통해 '한 스레드만' 임계영역에
	접근 할 수 있게 한다.
	. 뮤텍스나 세마포어보다 가볍다 (유저모드에서 처리되서)
	. 프로세스간 락은 불가능 (유저모드라서)
*/
int UseCriticalSection();

#endif