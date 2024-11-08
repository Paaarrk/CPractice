/*
전역 static 변수나 함수 : 파일 내에서만 접근 가능함 (접근 제한자)

헤더파일 중복을 피하기 위한 매크로 정의 
1	#ifndef __A_H__
2	#define __A_H__
3	{
		...
10	}
11	#endif

__A_H__ 가 정의 되어있지 않으면 정의하고, 마친다.
__A_H__ 가 정의 되어있다면 2 ~ 10은 실행하지 않는다.

구조체는 헤더에 정의하는게 좋다.
*/

#include <stdio.h>
#include "stdiv.h"
#include "intdiv3.h"

void Example27_00()
{
	Div val = IntDiv(5, 2);
	printf("몫: %d \n", val.q);
	printf("나머지: %d \n", val.r);

}