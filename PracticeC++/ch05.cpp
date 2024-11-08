#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "ch05.h"
#include "ch04.h"
using namespace std;

void Ch05_00()
{
	NameCard manClerk("Lee", "ABC_Eng", "010-2222-3333", COMP_POS::CLERK);
	NameCard copy1(manClerk);
	manClerk.ShowNameCardInfo();
	copy1.ShowNameCardInfo();
	
}

void Ch05_01()
{
	NameCard manClerk("Lee", "ABC_Eng", "010-2222-3333", COMP_POS::CLERK);
	NameCard womanClerk("Jung", "ABC_Eng", "010-2222-3333", COMP_POS::CLERK);
	CopyNameCard(manClerk);
	CopyNameCard(womanClerk);
}

NameCard CopyNameCard(NameCard cp)
{
	cout << "¹ÝÈ¯ Àü" << endl;
	return cp;
}