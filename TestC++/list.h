#ifndef __LIST_H__
#define __LIST_H__
#include <iostream>
using namespace std;

template <class T>
class node
{
	template <class T1> friend class list;
private:
	T data;
	node<T>* f;
	node<T>* r;
public:
	node(node<T>*, const T&, node<T>*);
	~node();
	void bind(node<T>*, node<T>*);
};

template <class T1>
class list
{
private:
	node<T1>* head;
	int count;
	void pushfirst(const T1&);
public:
	list();
	~list();
	void pushfront(const T1&);
	void pushrear(const T1&);
	T1& del(T1&);
	void showlist() const;
	int getcount() const { return count; }
};

template<class T>
node<T>::node(node<T>* f, const T& data, node<T>* r):f(f),data(data), r(r)
{
	
}
template<class T>
node<T>::~node()
{
	
}
template<class T>
void node<T>::bind(node<T>* f, node<T>* r)
{
	if (f == nullptr && r == nullptr)
	{

	}
	else if (f == nullptr)
	{
		this->r = r;
	}
	else if (r == nullptr)
	{
		this->f = f;
	}
	else {
		this->r = r; this->f = f;
	}
}


//list
template<class T1>
list<T1>::list() :count((int)0)
{
	head = new node<T1>(nullptr, T1(0), nullptr);
}
template<class T1>
list<T1>::~list()
{
	node<T1>* ptr = head->f;
	node<T1>* temp = nullptr;
	while (ptr != head)
	{
		temp = ptr;
		ptr = ptr->r;
		delete temp;
	}
}
template<class T1>
void list<T1>::pushfirst(const T1& d)
{
	node<T1>* n = new node<T1>(head, d, head);
	head->bind(n, n);
	count++;
}

template<class T1>
void list<T1>::pushfront(const T1& d)
{
	if (count == 0)
	{
		pushfirst(d);
		return;
	}
	node<T1>* n = new node<T1>(head, d, head->f);
	(head->f)->bind(n, nullptr);
	head->bind(n, nullptr);
	count++;
}

template<class T1>
void list<T1>::pushrear(const T1& d)
{
	if (count == 0)
	{
		pushfirst(d);
		return;
	}
	node<T1>* n = new node<T1>(head->r, d, head);
	(head->r)->bind(nullptr, n);
	head->bind(nullptr, n);
	count++;
}

template<class T1>
T1& list<T1>::del(T1&d)
{
	T1 n = T1(0);
	if (count == 0)
	{
		cout << "Empty list" << endl;
		return n;
	}
	node<T1>* ptr = head->f;
	while (ptr != head)
	{
		if (ptr->data == d)
			break;
		ptr = ptr->r;
	}

	if (ptr == head->f)
	{
		head->bind(ptr->r, nullptr);
		ptr->r->bind(head, nullptr);
		delete ptr;
		count--;
		return d;
	}
	else if (ptr == head->r)
	{
		head->bind(nullptr, ptr->f);
		ptr->f->bind(nullptr, head);
		delete ptr;
		count--;
		return d;
	}
	else if (ptr != head)
	{
		(ptr->f)->bind(nullptr, ptr->r);
		(ptr->r)->bind(ptr->f, nullptr);
		delete ptr;
		count--;
		return d;
	}
	else
	{
		cout << "no data" << endl;
		return n;
	}
}

template<class T1>
void list<T1>::showlist() const
{
	if (count == 0)
	{
		cout << "EmptyList" << endl;
		return;
	}
	node<T1>* ptr = head->f;
	cout << "count: " << count << "[ ";
	while (ptr != head)
	{
		cout << ptr->data << ' ';
		ptr = ptr->r;
	}
	cout << "]\n";
}
#endif