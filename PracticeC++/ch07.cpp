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
		emp.AddEmploy(new PermanentWorker("�躴��", 10000 + i));
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
	Book b1("���� C++", "555-5234-3423-9", 23000);
	EBook e1("���� C++ Ebook", "55534-434-34-34-4", 14990, "Adfklj2dkfj#");
	b1.ShowBookInfo();
	e1.ShowEBookInfo();

	EBook* b2 = new EBook("���� �Ҵ�� ���� C++", "555-5234-3423-9", 23000, "fhjowehoifws");
	b2->ShowBookInfo();
	b2->~EBook();
	// �����Ҵ� �ϴ��� �����ڿ� �ı����� ȣ�� ������ ���ÿ� �Ҵ��� ���� ����.
}

Rectangle::Rectangle(int x, int y):x(x), y(y)
{
	cout << "Rectangle����! : " << this << endl;
}

Rectangle::~Rectangle()
{
	cout << "Rectangle�Ҹ�! : " << this << endl;
}
void Rectangle::RectangleInfo() const
{
	cout << "���簢�� ����" << endl;
	cout << "����: " << x << "����: " << y << endl;
}

Square::Square(int n) :Rectangle(n, n)
{
	cout << "Square ����! : " << this << endl;
}
Square::~Square()
{
	cout << "Square �Ҹ�! : " << this << endl;
}
void Square::SquareInfo() const
{
	cout << "���簢�� ����" << endl;
	cout << "����, ���� : " << x << endl;
}

Book::Book(const char* title, const char* isbn, int price) : price(price)
{
	cout << "Book ������ ȣ��! " << this << endl;
	this->title = (char*)malloc(sizeof(char) * (strlen(title) + 1));
	strcpy(this->title, title);
	this->isbn = (char*)malloc(sizeof(char) * (strlen(isbn) + 1));
	strcpy(this->isbn, isbn);
}
Book::~Book()
{
	cout << "Book �Ҹ��� ȣ��! " << this << endl;
	free(title);
	free(isbn);
}

void Book::ShowBookInfo() const
{
	cout << "å ���� -----------" << endl;
	cout << "����: " << title << endl;
	cout << "ISBN: " << isbn << endl;
	cout << "����: " << price << endl;
}

EBook::EBook(const char* title, const char* isbn, int price, const char* drmKey)
	:Book(title, isbn, price) {
	cout << "EBook ������ ȣ��! " << this << endl;
	this->drmKey = (char*)malloc(sizeof(char)*(strlen(drmKey) + 1));
	strcpy(this->drmKey, drmKey);
}
EBook::~EBook()
{
	cout << "EBook �Ҹ��� ȣ��!: " << this << endl;
	free(drmKey);
}
void EBook::ShowEBookInfo() const
{
	ShowBookInfo();
	cout << "DRMŰ: " << drmKey << endl;
}