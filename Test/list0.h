#ifndef __LIST0_H__
#define __LIST0_H__
#include <iostream>
using std::cout;
using std::endl;
template<class T>
class Node0
{
	template<class T1> friend class DoublyLinkedList0;
private:
	T data;
	Node0<T>* f;
	Node0<T>* r;
public:
	Node0(Node0*, const T& data, Node0*);
	~Node0();
	void Binding(Node0*, Node0*);
};

template<class T1>
class DoublyLinkedList0
{
private:
	Node0<T1>* head;
	int count;
	void PushFirst(T1& data);
public:
	DoublyLinkedList0();
	~DoublyLinkedList0();
	bool Bound(int idx) const;
	void PushFront(T1& data);
	void PushRear(T1& data);
	void Delete(int idx);
	void ShowList() const;
};



/* Node */
template<class T>
Node0<T>::Node0(Node0* f, const T& data, Node0* r) : f(f), r(r), data(data)
{
	cout << "Node0() : " << this << endl;
}
template<class T>
Node0<T>::~Node0()
{
	cout << "~Node0() : " << data << " : " << this << endl;
}
template<class T>
void Node0<T>::Binding(Node0* f, Node0* r)
{
	if (f == NULL)
		this->r = r;
	else if (r == NULL)
		this->f = f;
	else if (f == NULL && r == NULL);
	else
	{
		this->f = f;
		this->r = r;
	}
}

/* DoublyLinkedList */
template<class T1>
DoublyLinkedList0<T1>::DoublyLinkedList0()
{
	cout << "List0 : " << this << endl;
	head = new Node0<T1>(NULL, NULL, NULL);
}
template<class T1>
DoublyLinkedList0<T1>::~DoublyLinkedList0()
{
	cout << "~List0 : " << this << endl;
	Node0<T1>* del = NULL;
	// 순회 해제
	for (Node0<T1>* ptr = head->r; ptr != head; )
	{
		del = ptr->f;
		delete ptr;
		ptr = del;
	}
	delete head;
}
template<class T1>
bool DoublyLinkedList0<T1>::Bound(int idx) const
{
	if (idx < 0 || idx >= count)
	{
		cout << "BoundOfException!!" << endl;
		return false;
	}
	return true;
}
template<class T1>
void DoublyLinkedList0<T1>::PushFirst(T1& data)
{
	Node0<T1>* n = new Node0<T1>(head, data, head);
	head->Binding(n, n);
	count++;
	cout << "PushFirst()" << n << endl;
}
template<class T1>
void DoublyLinkedList0<T1>::PushFront(T1& data)
{
	if (count == 0)
	{
		PushFirst(data);
		return;
	}

	Node0<T1>* n = new Node0<T1>(head, data, head->f);
	(head->f)->Binding(n, NULL);
	head->Binding(n, NULL);
	count++;
	cout << "PushFront()" << n << endl;
}
template <class T1>
void DoublyLinkedList0<T1>::PushRear(T1& data)
{
	if (count == 0)
	{
		PushFirst(data);
		return;
	}

	Node0<T1>* n = new Node0<T1>(head->r, data, head);
	(head->r)->Binding(NULL, n);
	head->Binding(NULL, n);
	count++;
	cout << "PushRear()" << n << endl;
}
template <class T1>
void DoublyLinkedList0<T1>::Delete(int idx)
{
	Node0<T1>* ptr = NULL;
	if (!Bound(idx))
		return;
	if (idx == 0)
	{
		ptr = head->f;
		head->Binding(ptr->r, NULL);
		(ptr->r)->Binding(head, NULL);
		// 2. 삭제
		delete ptr;		// 노드 해제
		count--;
		return;
	}
	if (idx == count - 1)
	{
		ptr = head->r;
		head->Binding(NULL, ptr->f);
		(ptr->f)->Binding(NULL, head);
		// 2. 삭제
		delete ptr;		// 노드 해제
		count--;
		return;
	}
	bool f_start = idx < count - 1 - idx ? true : false;
	int len = 0;
	if (f_start)
	{	// 앞에서 찾음
		len = idx;
		ptr = head->f;
		for (int i = 0; i < len; i++)
		{
			ptr = ptr->r;
		}
	} 
	else 
	{	// 뒤에서 찾음
		len = count - idx - 1;
		ptr = head->r;
		for (int i = 0; i < len; i++)
		{
			ptr = ptr->f;
		}
	}
	if (ptr == NULL)
		return;
	// 지우는 작업
	// 1. 바인딩
	(ptr->r)->Binding((ptr->f), NULL);
	(ptr->f)->Binding(NULL, (ptr->r));
	// 2. 삭제
	delete ptr;		// 노드 해제
	count--;
}

template <class T1>
void DoublyLinkedList0<T1>::ShowList() const
{
	if (count == 0)
	{
		cout << "Empty List" << endl;
		return;
	}
	cout << "[ ";
	for (Node0<T1>* ptr = head->f; ptr != head; ptr = ptr->r)
	{
		cout << ptr->data << ' ';
	}
	cout << "]" << endl;
}

#endif
