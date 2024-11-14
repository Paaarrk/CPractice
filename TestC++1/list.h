#ifndef __LIST_H__
#define __LIST_H__
#include <iostream>
using namespace std;

template <class T>
class Node
{
	template <class T1> friend class List;
private:
	T d;
	Node<T>* f;
	Node<T>* r;
public:
	Node(Node<T>* f, const T& d, Node<T>* r):f(f), d(d), r(r)
	{

	}
	~Node()
	{

	}
	void Bind(Node<T>* f, Node<T>* r)
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
		else
		{
			this->r = r; this->f = f;
		}
	}
};

template <class T1>
class List
{
private:
	Node<T1>* head;
	int count;
	void PushFirst(const T1& d)
	{
		Node<T1>* n = new Node<T1>(head, d, head);
		head->Bind(n, n);
		++count;
	}
public:
	List() :count((int)0) {
		head = new Node<T1>(nullptr, T1(0), nullptr);
	}
	~List()
	{
		if (count == 0)
		{
			delete head;
			return;
		}
		Node<T1>* ptr = head->f;
		Node<T1>* temp = nullptr;
		while (ptr == head)
		{
			temp = ptr;
			ptr = ptr->r;
			delete temp;
		}
		delete head;
	}
	void PushFront(const T1& d)
	{
		if (count == 0)
		{
			PushFirst(d);
			return;
		}
		
		Node<T1>* n = new Node<T1>(head, d, head->f);
		head->f->Bind(n, nullptr);
		head->Bind(n, nullptr);
		++count;
	}
	void PushRear(const T1& d)
	{
		if (count == 0)
		{
			PushFirst(d);
			return;
		}

		Node<T1>* n = new Node<T1>(head->r, d, head);
		head->r->Bind(nullptr, n);
		head->Bind(nullptr, n);
		++count;
	}
	T1& Delete(T1& d)
	{
		T1 n = T1(0);
		if (count == 0)
		{
			cout << "Empty" << endl;
			return n;
		}
		Node<T1>* ptr = head->f;
		while (ptr != head)
		{
			if (ptr->d == d)
				break;
			ptr = ptr->r;
		}

		if (ptr == head->f)
		{
			head->Bind(ptr->r, nullptr);
			ptr->r->Bind(head, nullptr);
			--count;
			delete ptr;
			return d;
		}
		else if(ptr == head->r)
		{
			head->Bind(nullptr, ptr->f);
			ptr->f->Bind(nullptr, head);
			--count;
			delete ptr;
			return d;
		}
		else if (ptr != head)
		{
			ptr->r->Bind(ptr->f, nullptr);
			ptr->f->Bind(nullptr, ptr->r);
			--count;
			delete ptr;
			return d;
		}
		else
		{
			cout << "No data" << endl;
			return n;
		}
	}
	void Info() const
	{
		if (count == 0)
		{
			cout << "Empty!" << endl;
			return;
		}
		Node<T1>* ptr = head->f;
		cout << "count: " << count << "[";
		while (ptr != head)
		{
			cout << ptr->d << ' ';
			ptr = ptr->r;
		}
		cout << "]" << endl;
	}
	int GetCount() const {
		return count;
	}
};

#endif