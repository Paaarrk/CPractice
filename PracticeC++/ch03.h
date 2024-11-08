#ifndef __CH03_H__
#define __CH03_H__

void Ch03_00(void); 
void Ch03_01(void);


class Calculator {
private:
	int add;
	int sub;
	int mul;
	int div;
public:
	void Init(void);
	double Add(double, double);
	double Sub(double, double);
	double Mul(double, double);
	double Div(double, double);
	void ShowOpCount();
};

class Printer {
private:
	char* str = 0;
	int len;
public:
	void SetString(const char*);
	void ShowString();
};
#endif
