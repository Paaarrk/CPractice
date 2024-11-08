#ifndef __CH09_H__
#define __CH09_H__
void Ch09_00();

class Base
{
public:
	Base();
	~Base();
	void BaseFunc();
};

class AAA : virtual public Base
{
public:
	AAA();
	~AAA();
	void AAAFunc();
};

class BBB : virtual public Base
{
public:
	BBB();
	~BBB();
	void BBBFunc();
};

class CCC : public AAA, public BBB
{
public:
	CCC();
	~CCC();
	void CCCFunc();
};

#endif