#include <stdio.h>
#include <conio.h>
#include <Windows.h>

/*
	_kbhit() : 버퍼에 누른 값을 저장해둔다.
	_getch() : 버퍼에서 누른 값을 하나씩 가져온다. (버퍼가 비어있을 때 까지)
*/
void Ch11_01()
{
	int c;
	int i = 0;
	while (1)
	{
		if (_kbhit() == 0)
		{
			printf_s("%s\r", "No input               ");
		}
		else {
			printf_s("%s ", "Clicked!");
			printf_s("%c\r", _getch());

			Sleep(1000);
		}
	}
}