#ifndef __CH_13_H__
#define __CH_13_H__

/*
	���� ��� ����ȭ ���
	1) Ciritical Section
	2) Interlocked Family of Function

	1) ���� �� �ȿʹ�´�. Enter�� ������ ���(indefinetely wait...)
	�� ���������� �𸣰ڳ�
	. EnterCriticalSection�� leaveCriticalSection�� ���� '�� �����常' �Ӱ迵����
	���� �� �� �ְ� �Ѵ�.
	. ���ؽ��� ��������� ������ (������忡�� ó���Ǽ�)
	. ���μ����� ���� �Ұ��� (��������)
*/
int UseCriticalSection();

#endif