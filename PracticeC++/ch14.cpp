#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "ch14.h"
using namespace std;

void Ch14_00()
{
	ArrayT<int> arr;
	for (int i = 0; i < arr.GetCap(); i++)
	{
		arr[i] = 10 * i;
	}
	cout << arr;
}