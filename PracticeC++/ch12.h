#ifndef __CH12_H__
#define __CH12_H__
#include <iostream>
using std::ostream;
using std::istream;
void Ch12_00();

class String
{
private:
	char* str;
public:
	String();
	String(const char*);
	String(const String&);
	~String();
	String operator+(const String&) const;
	String& operator+=(const String&);
	String& operator=(const String&);
	bool operator==(const String&);
	bool operator!=(const String&);
	friend ostream& operator<<(ostream& os, const String&);
	friend istream& operator>>(istream& is, String&);
};

#endif