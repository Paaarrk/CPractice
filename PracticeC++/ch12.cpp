#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "ch12.h"

using std::cout;
using std::endl;
using std::cin;
using std::ostream;
using std::istream;

void Ch12_00()
{
	String s0;
	cin >> s0;
	cout << s0 << endl;
	String s1("Myname");
	String s2(" is Mi");
	String s3;
	s3 = s1 + s2;
	s1 += s2;
	cout << (s1 != s2) << endl;
	cout << (s0 == s1) << endl;
	cout << (s3 == s1) << endl;
	cout << s0 << endl << s1 << endl << s2 << endl << s3 << endl;
}

String::String()
{
	cout << "String()" << this << endl;
	str = NULL;
}

String::String(const char* s)
{
	cout << "String(const char*)" << this << endl;
	str = (char*)malloc(sizeof(char) * (strlen(s) + 1));
	strcpy(str, s);
}

String::String(const String& s)
{
	cout << "String(String&)" << this << endl;
	if (s.str != NULL)
	{
		str = (char*)malloc(sizeof(char) * (strlen(s.str) + 1));
		strcpy(str, s.str);
	}
	else {
		str = NULL;
	}
}

String::~String()
{
	cout << "~String()" << this << endl;
	if(str != NULL)
		free(str);
}

String& String::operator=(const String& s)
{
	cout << "operator=()" << this << endl;
	if (str == NULL)
	{
		if (s.str != NULL)
		{
			str = (char*)malloc(sizeof(char) * (strlen(s.str) + 1));
			strcpy(str, s.str);
		}
	}
	else
	{
		free(str);
		if (s.str != NULL)
		{
			str = (char*)malloc(sizeof(char) * (strlen(s.str) + 1));
			strcpy(str, s.str);
		}
		else
		{
			str = NULL;
		}
	}
	return *this;
}

String String::operator+(const String& s) const
{
	cout << "operator+()" << endl;
	String res(str);
	if (str != NULL)
	{
		if (s.str != NULL)
		{
			res.str = (char*)realloc(res.str, sizeof(char) * (strlen(res.str) + strlen(s.str) + 1));
			strcat(res.str, s.str);
		}
		else
		{
			//None
		}
	}
	else
	{
		if (s.str != NULL)
		{
			res = s;
		}
		else
		{
			//None
		}
	}


	return res;
}

String& String::operator+=(const String& s)
{
	if (str == NULL)
	{
		*this = s;
	}

	if (s.str != NULL)
	{
		str = (char*)realloc(str, (sizeof(char) * (strlen(str) + strlen(s.str) + 1)));
		strcat(str, s.str);
	}
	return *this;
}

bool String::operator==(const String& s)
{
	if (str == NULL && s.str == NULL)
		return true;
	if (s.str == NULL || str == NULL)
		return false;

	int r = strcmp(str, s.str);
	if (r == 0)
		return true;
	else
		return false;
}

bool String::operator!=(const String& s)
{
	return !(str == s.str);
}

ostream& operator<<(ostream& os, const String& s)
{
	os << s.str;
	return os;
}

istream& operator>>(istream& is, String& s)
{
	char str[100];
	is >> str;
	s = String(str);
	return is;
}
