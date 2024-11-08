#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "ch07.h"
#include "EmployHandler.h"
#include "PermanentWorker.h"
using namespace std;

void Ch07_00()
{
	EmployHandler emp;
	for (int i = 0; i < 25; i++)
	{
		emp.AddEmploy(new PermanentWorker("김병만", 10000 + i));
	}

	emp.ShowAllSalaryInfo();
	emp.ShowTotalSalary();
}

void Ch07_01()
{
	Rectangle r1(2, 3);
	r1.RectangleInfo();
	Square r2(4);
	r2.SquareInfo();
	//Rectangle r3 = (Rectangle)r2;
	//r3.RectangleInfo();
}

void Ch07_02()
{
	Book b1("좋은 C++", "555-5234-3423-9", 23000);
	EBook e1("좋은 C++ Ebook", "55534-434-34-34-4", 14990, "Adfklj2dkfj#");
	b1.ShowBookInfo();
	e1.ShowEBookInfo();

	EBook* b2 = new EBook("동적 할당된 좋은 C++", "555-5234-3423-9", 23000, "fhjowehoifws");
	b2->ShowBookInfo();
	b2->~EBook();
	// 동적할당 하더라도 생성자와 파괴자의 호출 순서는 스택에 할당할 때와 같다.
}

Rectangle::Rectangle(int x, int y):x(x), y(y)
{
	cout << "Rectangle생성! : " << this << endl;
}

Rectangle::~Rectangle()
{
	cout << "Rectangle소멸! : " << this << endl;
}
void Rectangle::RectangleInfo() const
{
	cout << "직사각형 정보" << endl;
	cout << "가로: " << x << "세로: " << y << endl;
}

Square::Square(int n) :Rectangle(n, n)
{
	cout << "Square 생성! : " << this << endl;
}
Square::~Square()
{
	cout << "Square 소멸! : " << this << endl;
}
void Square::SquareInfo() const
{
	cout << "정사각형 정보" << endl;
	cout << "가로, 세로 : " << x << endl;
}

Book::Book(const char* title, const char* isbn, int price) : price(price)
{
	cout << "Book 생성자 호출! " << this << endl;
	this->title = (char*)malloc(sizeof(char) * (strlen(title) + 1));
	strcpy(this->title, title);
	this->isbn = (char*)malloc(sizeof(char) * (strlen(isbn) + 1));
	strcpy(this->isbn, isbn);
}
Book::~Book()
{
	cout << "Book 소멸자 호출! " << this << endl;
	free(title);
	free(isbn);
}

void Book::ShowBookInfo() const
{
	cout << "책 정보 -----------" << endl;
	cout << "제목: " << title << endl;
	cout << "ISBN: " << isbn << endl;
	cout << "가격: " << price << endl;
}

EBook::EBook(const char* title, const char* isbn, int price, const char* drmKey)
	:Book(title, isbn, price) {
	cout << "EBook 생성자 호출! " << this << endl;
	this->drmKey = (char*)malloc(sizeof(char)*(strlen(drmKey) + 1));
	strcpy(this->drmKey, drmKey);
}
EBook::~EBook()
{
	cout << "EBook 소멸자 호출!: " << this << endl;
	free(drmKey);
}
void EBook::ShowEBookInfo() const
{
	ShowBookInfo();
	cout << "DRM키: " << drmKey << endl;
}