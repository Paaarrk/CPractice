/*
���� static ������ �Լ� : ���� �������� ���� ������ (���� ������)

������� �ߺ��� ���ϱ� ���� ��ũ�� ���� 
1	#ifndef __A_H__
2	#define __A_H__
3	{
		...
10	}
11	#endif

__A_H__ �� ���� �Ǿ����� ������ �����ϰ�, ��ģ��.
__A_H__ �� ���� �Ǿ��ִٸ� 2 ~ 10�� �������� �ʴ´�.

����ü�� ����� �����ϴ°� ����.
*/

#include <stdio.h>
#include "stdiv.h"
#include "intdiv3.h"

void Example27_00()
{
	Div val = IntDiv(5, 2);
	printf("��: %d \n", val.q);
	printf("������: %d \n", val.r);

}