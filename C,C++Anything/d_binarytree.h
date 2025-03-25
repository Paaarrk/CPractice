#ifndef __D_BINARYTREE_H__
#define __D_BINARYTREE_H__

namespace my
{
	template<typename T>
	class stack
	{
	public:
		stack(size_t cap) :_arr(nullptr), _top(0), _size(0), _cap(cap)
		{
			if (cap != 0)
			{
				_arr = new T[cap];
			}
		}
		~stack()
		{
			if (_cap != 0)
				delete[] _arr;
		}
		void push(const T& data)
		{
			if (_arr == nullptr)
				return;
			if (_size == _cap)
			{
				T* tmp = new T[_cap * 2];
				memcpy_s(tmp, _cap*sizeof(T), _arr, _cap*sizeof(T));
				_cap *= 2;
				delete[] _arr;
				_arr = tmp;
			}
			_arr[_top] = data;
			_top++;
			_size++;
		}
		void pop()
		{
			if (_size == 0)
				return;
			_top--;
			_size--;
		}
		T* peek()
		{
			if (_size == 0)
				return nullptr;
			return &_arr[_top - 1];
		}
		bool empty() { return _size == 0; }
	private:
		T* _arr;
		size_t _top;
		size_t _size;
		size_t _cap;
	};
	//---------------------------------------
	// 중복을 허용하지 않는 일반 이진탐색트리
	// insert: O(log n) ~ O(n)
	// find: O(log n) ~ O(n)
	// Delete: O(log n) ~ O(n)
	//---------------------------------------
	template <typename T>
	class binarytree
	{
	public:
		struct node
		{
			T _data;
			node* _parent;
			node* _left;
			node* _right;
		};
		binarytree() :_root(nullptr) {}
		bool insert(const T& data)
		{
			// 새로운 노드 생성
			node* n = (node*)malloc(sizeof(node));
			n->_data = data;
			n->_left = nullptr;
			n->_right = nullptr;
			if (_root == nullptr)
			{
				n->_parent = nullptr;
				_root = n;
				return false;
			}

			// 루트가 있다면 들어갈 곳을 찾음.
			node* cur = _root;
			node* bef = nullptr;
			while (cur != nullptr)
			{
				if (cur->_data == data)
				{
					n->_data.~T();
					free(n);
					return false;
				}

				bef = cur;
				if (cur->_data < data)
					cur = cur->_right;
				else
					cur = cur->_left;
			}
			
			if (bef->_data < data)
				bef->_right = n;
			else
				bef->_left = n;
			n->_parent = bef;
			return true;
		}
		node* find(const T& data)
		{
			node* cur = _root;
			while (cur != nullptr)
			{
				if (cur->_data == data)
					return cur;

				if (cur->_data < data)
					cur = cur->_right;
				else
					cur = cur->_left;
			}
			return nullptr;
		}
		bool Delete(const T& data)
		{
			node* del = find(data);
			if (del == nullptr)
				return false;
			// 루트일 때 잊지마!
			node* p;
			node* r;
			node* l;
			node* cur;
			node* bef;
			if (del == _root)
			{
				r = del->_right;
				l = del->_left;
				if (r == nullptr && l == nullptr)
				{
					_root = nullptr;
				}
				else if (r == nullptr)
				{
					_root = l;
					l->_parent = nullptr;
				}
				else if (l == nullptr)
				{
					_root = r;
					r->_parent = nullptr;
				}
				else
				{
					_root = r;
					bef = r;
					cur = r->_left;
					while (cur != nullptr)
					{
						bef = cur;
						cur = cur->_left;
					}
					bef->_left = l;
					l->_parent = bef;
				}
			}
			else
			{
				p = del->_parent;
				l = del->_left;
				r = del->_right;
				if (r == nullptr && l == nullptr)
				{
					if (p->_left == del)
						p->_left = nullptr;
					else
						p->_right = nullptr;
				}
				else if (r == nullptr)
				{
					if (p->_left == del)
					{
						p->_left = l;
						l->_parent = p;
					}
					else
					{
						p->_right = l;
						l->_parent = p;
					}
				}
				else if (l == nullptr)
				{
					if (p->_left == del)
					{
						p->_left = r;
						r->_parent = p;
					}
					else
					{
						p->_right = r;
						r->_parent = p;
					}
				}
				else
				{
					if (p->_left == del)
					{
						r->_parent = p;
						p->_left = r;
					}
					else
					{
						r->_parent = p;
						p->_right = r;
					}
					bef = r;
					cur = r->_left;
					while (cur != nullptr)
					{
						bef = cur;
						cur = cur->_left;
					}
					bef->_left = l;
					l->_parent = bef;
				}
			}

			del->_data.~T();
			free(del);

			return true;
		}
		void ShowTree()const
		{
			node* cur = _root;
			stack<node*> st(100);
			while (cur != nullptr || (st.empty() == false))
			{
				while (cur != nullptr)
				{
					st.push(cur);
					cur = cur->_left;
				}
				cur = *st.peek();
				std::cout << cur->_data << std::endl;
				st.pop();
				cur = cur->_right;
			}
		}
		void clear()
		{
			node* tmp;
			node* cur = _root;
			stack<node*> st(100);
			while (cur != nullptr || (st.empty() == false))
			{
				while (cur != nullptr)
				{
					st.push(cur);
					cur = cur->_left;
				}
				cur = *st.peek();
				st.pop();
				tmp = cur->_right;
				cur->_data.~T();
				free(cur);
				cur = tmp;
			}

		}
	private:
		node* _root;
	};
}


#endif