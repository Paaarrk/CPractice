#ifndef __LIST_H__
#define __LIST_H__
#include <iostream>
using std::cout;
using std::endl;
template <typename T>
class Node
{
	template <class T1> friend class List;
private:
	T data;
	Node<T>* f;
	Node<T>* r;
public:
	Node(Node<T>*, const T& data, Node<T>*);
	~Node();
	void Bind(Node<T>*, Node<T>*);
};

template <typename T1>
class List
{
private:
	Node<T1>* head;
	int count;
	void PushFirst(T1&);
public:
	List();
	~List();
	void PushFront(T1&);
	void PushRear(T1&);
	T1& Delete(T1&);
	void ShowInfo() const;
	int GetCount() const { return count; }
};

template<class T>
Node<T>::Node(Node<T>* f, const T& data, Node<T>* r) :f(f), r(r), data(data)
{
	cout << "Node()" << this << endl;
}
template<class T>
Node<T>::~Node()
{
	cout << "~Node()" << this << endl;
}
template<class T>
void Node<T>::Bind(Node<T>* f, Node<T>* r)
{
	if (f == nullptr && r == nullptr)
		return;
	if (f == nullptr) {
		this->r = r;
		return;
	}
	if (r == nullptr) {
		this->f = f;
		return;
	}
	this->f = f; this->r = r;
}

// List
template<class T1>
List<T1>::List() : count((int)0)
{
	head = new Node<T1>(nullptr, T1(0), nullptr);
}
template<class T1>
List<T1>::~List()
{
	Node<T1>* ptr = head->f;
	Node<T1>* temp = nullptr;
	while (ptr != head)
	{
		temp = ptr;
		ptr = ptr->r;
		delete temp;
	}

}
template <class T1>
void List<T1>::PushFirst(T1& data)
{
	Node<T1>* n = new Node<T1>(head, data, head);
	head->Bind(n, n);
	++count;
}
template<class T1>
void List<T1>::PushFront(T1& data)
{
	if (count == 0)
	{
		PushFirst(data);
		return;
	}
	Node<T1>* n = new Node<T1>(head, data, head->f);
	(head->f)->Bind(n, nullptr);
	head->Bind(n, nullptr);
	count++;
}
template<class T1>
void List<T1>::PushRear(T1& data)
{
	if (count == 0)
		PushFirst(data);
	Node<T1>* n = new Node<T1>(head->r, data, head);
	(head->r)->Bind(nullptr, n);
	head->Bind(nullptr, n);
	count++;
}
template<class T1>
T1& List<T1>::Delete(T1& data)
{
	T1 t = T1(0);
	if (count == 0)
	{
		cout << "Empty!!" << endl;
		return t;
	}
	Node<T1>* ptr;
	for (ptr = head->f; ptr != head; ptr = ptr->r)
	{
		if (ptr->data == data)
			break;
	}

	if (ptr == head->f)
	{
		(ptr->f)->Bind(ptr->r, nullptr);
		(ptr->r)->Bind(ptr->f, nullptr);
		delete ptr;
		count--;
		return data;
	}
	else if (ptr == head->r)
	{
		(ptr->f)->Bind(nullptr, ptr->r);
		(ptr->r)->Bind(nullptr, ptr->f);
		delete ptr;
		count--;
		return data;
	}
	else if (ptr != head)
	{
		(ptr->f)->Bind(nullptr, ptr->r);
		(ptr->r)->Bind(ptr->f, nullptr);
		delete ptr;
		count--;
		return data;
	}
	else {
		cout << "없는 데이터" << endl;
		return t;
	}
}
template<class T1>
void List<T1>::ShowInfo() const
{
	cout << "count: " << count;
	if (count == 0)
		cout << "EmptyList" << endl;
	cout << "[ ";
	for (Node<T1>* ptr = head->f; ptr != head; ptr = ptr->r)
	{
		cout << ptr->data << ' ';
	}
	cout << "]" << endl;
}

#endif
