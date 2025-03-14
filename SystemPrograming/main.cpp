#include <iostream>
#include <tchar.h>
#include <Windows.h>
#include "Ch12.h"


int _tmain(int argc, TCHAR* argv[])
{
	_tsetlocale(LC_ALL, _T("Korean"));

	return SuspendCount();
}