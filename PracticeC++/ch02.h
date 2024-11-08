#ifndef __CH02_H__
#define __CH02_H__
typedef struct {
	int xPos;
	int yPos;
}Point;

void Ch02_00(void);
void Ch02_01(void);
void Ch02_02(void);
void Ch02_03(void);
void Ch02_04(void);
void Ch02_05(void);
void Ch02_06(void);

void plusone(int& ref);
void absInt(int& ref);
void SwapPointer(int*&, int*&);
Point& PntAdder(const Point&, const Point&);


#endif