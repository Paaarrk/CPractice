#include <WS2tcpip.h>
#include <windows.h>
#include <iostream>
#include <conio.h>

#include "ch3.h"




int main(void)
{
	
	setlocale(LC_ALL, "korean");
	int a = 0;
	a = Singleton2();

	char c = _getch();
	return a;
}