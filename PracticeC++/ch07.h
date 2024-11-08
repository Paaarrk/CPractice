#ifndef __CH07_H__
#define __CH07_H__

void Ch07_00();
void Ch07_01();
void Ch07_02();


class Rectangle
{
private:
	int y;
protected:
	int x;
public:
	Rectangle(int, int);
	~Rectangle();
	void RectangleInfo() const;
};

class Square :private Rectangle
{
private:
public:
	Square(int);
	~Square();
	void SquareInfo() const;
};

class Book
{
private:
	char* title;
	char* isbn;
	int price;
public:
	Book(const char*, const char*, int);
	~Book();
	void ShowBookInfo() const;
};

class EBook : public Book
{
private:
	char* drmKey;
public:
	EBook(const char*, const char*, int, const char*);
	~EBook();
	void ShowEBookInfo() const;
};
#endif
