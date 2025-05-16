#ifndef __RED_BLACK_TREE_H__
#define __RED_BLACK_TREE_H__


namespace my
{
	template <typename KEY, typename VAL>
	class map;
// ���尡 ���� 1��Ʈ�� 1, ���� 0
// ������ ���� 1��Ʈ�� �����Ѵ�.
#define RED		1
#define BLACK	0

#ifdef _WIN64
#define GET_COLOR(x)	((int)(((__int64)(x) & 0x8000'0000'0000'0000LL) >> 63))
#define GET_ADDRESS(x)	((map<KEY, VAL>::node*)((__int64)(x) & 0x7FFF'FFFF'FFFF'FFFFLL))

#define SET_RED(x)		do{														\
	(x) = (map<KEY, VAL>::node*)((__int64)(x) | 0x8000'0000'0000'0000LL);		\
	node* xAddress = GET_ADDRESS(x);											\
	node* x_pAddress = GET_ADDRESS((xAddress->p));								\
	if(xAddress->l != _nil)														\
		GET_ADDRESS(xAddress->l)->p = (x);										\
	if(xAddress->r != _nil)														\
		GET_ADDRESS(xAddress->r)->p = (x);										\
	if(x_pAddress != nullptr && x_pAddress != _nil)							\
	{																			\
		if(GET_ADDRESS(x_pAddress->r) == xAddress)								\
			x_pAddress->r = (x);												\
		else																	\
			x_pAddress->l = (x);												\
	}																			\
	_nil->p = nullptr; _nil->r = nullptr; _nil->l = nullptr;					\
}while(0)

#define SET_BLACK(x)		do{													\
	((x) = (map<KEY, VAL>::node*)(((__int64)(x)) & 0x7FFF'FFFF'FFFF'FFFFLL));	\
	node* xAddress = GET_ADDRESS(x);											\
	node* x_pAddress = GET_ADDRESS(xAddress->p);								\
	if(xAddress->l != _nil)														\
		GET_ADDRESS(xAddress->l)->p = (x);										\
	if(xAddress->r != _nil)														\
		GET_ADDRESS(xAddress->r)->p = (x);										\
	if(x_pAddress != nullptr && x_pAddress != _nil)							\
	{																			\
		if(GET_ADDRESS(x_pAddress->r) == xAddress)								\
			x_pAddress->r = (x);												\
		else																	\
			x_pAddress->l = (x);												\
	}																			\
	_nil->p = nullptr; _nil->r = nullptr; _nil->l = nullptr;					\
}while(0)
#else //_WIN32
#define GET_COLOR(x)	((int)((int)(x) & 0x8000'0000) >> 31)
#define GET_ADDRESS(x)	((map<KEY, VAL>::node*)((int)(x) & 0x7FFF'FFFF))

#define SET_RED(x)		do{														\
	(x) = (map<KEY, VAL>::node*)((int)(x) | 0x8000'0000);						\
	node* xAddress = GET_ADDRESS(x);											\
	node* x_pAddress = GET_ADDRESS(xAddress->p);								\
	if(xAddress->l != _nil)														\
		GET_ADDRESS(xAddress->l)->p = (x);										\
	if(xAddress->r != _nil)														\
		GET_ADDRESS(xAddress->r)->p = (x);										\
	if(x_pAddress != nullptr && x_pAddress != _nil)							\
	{																			\
		if(GET_ADDRESS(x_pAddress->r) == xAddress)								\
			x_pAddress->r = (x);												\
		else																	\
			x_pAddress->l = (x);												\
	}																			\
	_nil->p = nullptr; _nil->r = nullptr; _nil->l = nullptr;					\
}while(0)

#define SET_BLACK(x)		do{													\
	((x) = (map<KEY, VAL>::node*)((__int64)(x) & 0x7FFF'FFFF));					\
	node* xAddress = GET_ADDRESS(x);											\
	node* x_pAddress = GET_ADDRESS(xAddress->p);								\
	if(xAddress->l != _nil)														\
		GET_ADDRESS(xAddress->l)->p = (x);										\
	if(xAddress->r != _nil)														\
		GET_ADDRESS(xAddress->r)->p = (x);										\
	if(x_pAddress != nullptr && x_pAddress != _nil)							\
	{																			\
		if(GET_ADDRESS(x_pAddress->r) == xAddress)								\
			x_pAddress->r = (x);												\
		else																	\
			x_pAddress->l = (x);												\
	}																			\
	_nil->p = nullptr; _nil->r = nullptr; _nil->l = nullptr;					\
}while(0)
#endif


	template <typename KEY, typename VAL>
	struct pair
	{
		KEY key;
		VAL* value;
		char color;
		pair() :key(0), value(nullptr), color(0) {}
		pair(const KEY& key, VAL* val, char color) :key(key), value(val), color(color) {}
		pair(const pair& p) :key(p.key), value(p.value), color(p.color) {}
		void operator=(const pair& ref)
		{
			key = ref.key;
			value = ref.value;
			color = ref.color;
		}
	};
	template <typename KEY, typename VAL>
	class map
	{
	public:
		struct node
		{
			const KEY key;
			node* p;	//parent
			node* l;	//left
			node* r;	//right
			VAL value;	// ��
			node(KEY key = KEY{}, const VAL& val = VAL{}) :key(key), p(nullptr), l(nullptr), r(nullptr), value(val) {};
			node(KEY key, node* p, node* l, node* r, const VAL& val) :key(key), p(p), l(l), r(r), value(val) {};
		};
		class iterator
		{
		public:
			iterator(node* n = nullptr) :_node(n) {};
			iterator(const iterator& iter) :_node(iter._node) {};
			iterator operator++()
			{
				node* x_p = GET_ADDRESS(_node)->p;
				node* x_pAddress = GET_ADDRESS(x_p);
				node* x_r = GET_ADDRESS(_node)->r;
				node* x_rAddress = GET_ADDRESS(x_r);
				node* x_l = GET_ADDRESS(_node)->l;
				node* x_lAddress = GET_ADDRESS(x_l);
				
				if (x_rAddress->r != nullptr)//nil�� �ƴϸ� 
				{	
					_node = x_r;	// ������ ���� �̵�
					x_l = GET_ADDRESS(_node)->l;	//���ڽ� �� ����
					x_lAddress = GET_ADDRESS(x_l);
					while (x_lAddress->l != nullptr)	// ���ڽ��� nil�� �� ����
					{
						_node = x_l;	// ���ڽ��� nil�϶����� ������
						x_l = GET_ADDRESS(_node)->l;	//���ڽ� �� ����
						x_lAddress = GET_ADDRESS(x_l);
					}
				}
				else
				{	//���������� �� �� ���� ����-> ����Ʈ���� �� ���� ����
					// ���� ó������ �����ڽ��� �ƴ� �� ���� �ö�
					while (x_pAddress->r == _node)
					{
						_node = x_p;
						x_p = GET_ADDRESS(_node)->p;
						x_pAddress = GET_ADDRESS(x_p);
					}
					// �� �ö������ ���� �θ� ���� �����
					_node = x_p;
				}

				return *this;
			}

			iterator operator++(int)
			{
				node* temp = _node;

				node* x_p = GET_ADDRESS(_node)->p;
				node* x_pAddress = GET_ADDRESS(x_p);
				node* x_r = GET_ADDRESS(_node)->r;
				node* x_rAddress = GET_ADDRESS(x_r);
				node* x_l = GET_ADDRESS(_node)->l;
				node* x_lAddress = GET_ADDRESS(x_l);

				if (x_rAddress->r != nullptr)//nil�� �ƴϸ� 
				{
					_node = x_r;	// ������ ���� �̵�
					x_l = GET_ADDRESS(_node)->l;	//���ڽ� �� ����
					x_lAddress = GET_ADDRESS(x_l);
					while (x_lAddress->l != nullptr)	// ���ڽ��� nil�� �� ����
					{
						_node = x_l;	// ���ڽ��� nil�϶����� ������
						x_l = GET_ADDRESS(_node)->l;	//���ڽ� �� ����
						x_lAddress = GET_ADDRESS(x_l);
					}
				}
				else
				{	//���������� �� �� ���� ����-> ����Ʈ���� �� ���� ����
					// ���� ó������ �����ڽ��� �ƴ� �� ���� �ö�
					while (x_pAddress->r == _node)
					{
						_node = x_p;
						x_p = GET_ADDRESS(_node)->p;
						x_pAddress = GET_ADDRESS(x_p);
					}
					// �� �ö������ ���� �θ� ���� �����
					_node = x_p;
				}
				return iterator(temp);
			}
			iterator operator--()
			{
				node* x_p = GET_ADDRESS(_node)->p;
				node* x_pAddress = GET_ADDRESS(x_p);
				node* x_r = GET_ADDRESS(_node)->r;
				node* x_rAddress = GET_ADDRESS(x_r);
				node* x_l = GET_ADDRESS(_node)->l;
				node* x_lAddress = GET_ADDRESS(x_l);

				if (x_lAddress->l != nullptr)//nil�� �ƴϸ� 
				{
					_node = x_l;	// ���� ���� �̵�
					x_r = GET_ADDRESS(_node)->r;	//�����ڽ� �� ����
					x_rAddress = GET_ADDRESS(x_r);
					while (x_rAddress->r != nullptr)	// �����ڽ��� nil�� �� ����
					{
						_node = x_r;	// ���ڽ��� nil�϶����� ������
						x_r = GET_ADDRESS(_node)->r;	//���ڽ� �� ����
						x_rAddress = GET_ADDRESS(x_r);
					}
				}
				else
				{	//�������� �� �� ���� ����-> ����Ʈ���� �� ���� ����
					// ���� ó������ ���ڽ��� �ƴ� �� ���� �ö�
					while (x_pAddress->l == _node)
					{
						_node = x_p;
						x_p = GET_ADDRESS(_node)->p;
						x_pAddress = GET_ADDRESS(x_p);
					}
					// �� �ö������ ���� �θ� ���� �����
					_node = x_p;
				}


				return *this;
			}
			iterator operator--(int)
			{
				node* temp = _node;
				node* x_p = GET_ADDRESS(_node)->p;
				node* x_pAddress = GET_ADDRESS(x_p);
				node* x_r = GET_ADDRESS(_node)->r;
				node* x_rAddress = GET_ADDRESS(x_r);
				node* x_l = GET_ADDRESS(_node)->l;
				node* x_lAddress = GET_ADDRESS(x_l);

				if (x_lAddress->l != nullptr)//nil�� �ƴϸ� 
				{
					_node = x_l;	// ���� ���� �̵�
					x_r = GET_ADDRESS(_node)->r;	//�����ڽ� �� ����
					x_rAddress = GET_ADDRESS(x_r);
					while (x_rAddress->r != nullptr)	// �����ڽ��� nil�� �� ����
					{
						_node = x_r;	// ���ڽ��� nil�϶����� ������
						x_r = GET_ADDRESS(_node)->r;	//���ڽ� �� ����
						x_rAddress = GET_ADDRESS(x_r);
					}
				}
				else
				{	//�������� �� �� ���� ����-> ����Ʈ���� �� ���� ����
					// ���� ó������ ���ڽ��� �ƴ� �� ���� �ö�
					while (x_pAddress->l == _node)
					{
						_node = x_p;
						x_p = GET_ADDRESS(_node)->p;
						x_pAddress = GET_ADDRESS(x_p);
					}
					// �� �ö������ ���� �θ� ���� �����
					_node = x_p;
				}
				return iterator(temp);
			}
			pair<KEY, VAL> operator*() const
			{
				char color = 0;
				if (GET_COLOR(_node) == RED)
					color = 'R';
				else if (GET_COLOR(_node) == BLACK)
					color = 'B';
				pair<KEY, VAL> p(GET_ADDRESS(_node)->key, &(GET_ADDRESS(_node)->value), color);
				return p;
			}
			bool operator==(const iterator& other)
			{
				return (other._node == _node);
			}
			bool operator!=(const iterator& other)
			{
				return !(other._node == _node);
			}
		private:
			node* _node;
		};
		
		map() :_root(nullptr), _nil(new node), _size(0)
		{ 
			_nil->p = nullptr;
			_nil->l = nullptr;
			_nil->r = nullptr;
		};

		bool insert(const KEY& key, const VAL& val)
		{
			node* n = new node(key, nullptr, _nil, _nil, val);
			SET_RED(n);
			_size++;
			// ��Ʈ�� ������
			if (_root == nullptr)
			{
				_root = n;
				GET_ADDRESS(_root)->p = _nil;
				SET_BLACK(_root);
			}
			else
			{
				// ���� �� Ž��
				node* search = _root;
				bool isLeft = false;
				while (1)
				{
					if (GET_ADDRESS(search)->key > key)
					{
						if (GET_ADDRESS(search)->l != _nil)
							search = GET_ADDRESS(search)->l;
						else
						{
							isLeft = true;
							break;
						}
					}
					else if(GET_ADDRESS(search)->key < key)
					{
						if (GET_ADDRESS(search)->r != _nil)
							search = GET_ADDRESS(search)->r;
						else
						{
							isLeft = false;	// right
							break;
						}
					}
					else// ������, �ߺ�Ű, ����
					{
						delete GET_ADDRESS(n);
						_size--;
						return false;
					}
				}

				//�ֱ�
				if (isLeft)
					GET_ADDRESS(search)->l = n;
				else //right
					GET_ADDRESS(search)->r = n;
				GET_ADDRESS(n)->p = search;

				// ������ fixedup
				fixedInsert(n);
			}
			return true;
		}
		VAL* find(const KEY& key)	// ����� �������� �ּҸ�����.
		{
			// Ʈ���� ������� nullptr 
			if (_size == 0)
				return nullptr;

			node* search = _root;
			while (search != _nil)
			{
				if (GET_ADDRESS(search)->key < key)
					search = (GET_ADDRESS(search)->r);
				else if (GET_ADDRESS(search)->key > key)
					search = (GET_ADDRESS(search)->l);
				else // ����
					return &(search->value);
			}
			return nullptr;
		}
		bool Delete(const KEY& key)
		{
			if (_size == 0)
				return false;

			node* search = _root;
			node* Delete;	// ���� ���
			node* fixed;	// ���� ���
			while (search != _nil)
			{
				if (GET_ADDRESS(search)->key < key)
					search = (GET_ADDRESS(search)->r);
				else if (GET_ADDRESS(search)->key > key)
					search = (GET_ADDRESS(search)->l);
				else // ����
					break;
			}
			if(search == _nil)
				return false;

			int originalColor;	//�����ڽ��� �ö���鼭 ������ ������� �Ǵ� �� (���� ��� �� �ƴ�)
			node* minRight;
			//ã������ ���� ����..
			if (GET_ADDRESS(search)->l == _nil)
			{	// ���� �ڽ��� ����
				originalColor = GET_COLOR(search);
				fixed = GET_ADDRESS(search)->r;
				transparent(search, fixed, false);	//false�� fixed�� search�� �������̶�¶�
				Delete = search;
			}
			else if (GET_ADDRESS(search)->r == _nil)
			{	// ������ �ڽ��� ����
				originalColor = GET_COLOR(search);
				fixed = GET_ADDRESS(search)->l;
				transparent(search, fixed, true); // true�� fixed�� search�� �����̶�� ��
				Delete = search;
			}
			else
			{
				minRight = minRSub(search);
				// ������ �ڸ��� �״�� ����, search���̻� ��� �Ұ�
				search->key = minRight->key;
				search->value = minRight->value;

				originalColor = GET_COLOR(minRight);
				fixed = GET_ADDRESS(minRight)->r;
				transparent(minRight, fixed, false);	// minRight�� fixed�� ������ �̶�� ��
				Delete = minRight;	//���� ���
			}

			if (originalColor == BLACK)
				fixedDelete(fixed);

			delete Delete;
			return true;
		}
		void showInfo() const
		{
			int size = 0;
			if (_size == 0)
			{
				printf_s("empty!");
				return;
			}
			pair<KEY, VAL> p;
			for (iterator i = begin(); i != end(); ++i)
			{
				size++;
				p = *i;
				printf_s("size: %d / %zd, color: %c, key: %d, val: %p\n", size, _size, p.color, p.key, p.value);
			}
		}
		iterator end() const
		{
			iterator iter(_nil);
			return iter;
		}
		iterator begin() const
		{
			if (_root == nullptr)
				return end();
			node* t = _root;
			while (GET_ADDRESS(t)->l != _nil)
			{
				t = GET_ADDRESS(t)->l;
			}
			return iterator(t);
		}
		~map()
		{
			// ��ȸ
			delete _nil;
		}
		size_t size() const { return _size; }
	private:
		node* _root;
		node* _nil;
		size_t _size;

		// x�� ���θ��̴�.
		void rotateR(node* x)
		{
			node* x_p = GET_ADDRESS(x)->p;
			node* x_pAddress = GET_ADDRESS(x_p);
			node* x_l = GET_ADDRESS(x)->l;
			node* x_lAddress = GET_ADDRESS(x_l);
			node* x_l_r = x_lAddress->r;
			node* x_l_rAddress = GET_ADDRESS(x_l_r);
			
			// x�� ���ڽ��� �ø�
			if (x_pAddress->r == x)
				x_pAddress->r = x_l;
			else
				x_pAddress->l = x_l;
			x_lAddress->p = x_p;

			// x�� x_l�� �����ڽ����� ����
			x_lAddress->r = x;
			GET_ADDRESS(x)->p = x_l;
			
			// x�� ���� ���ڽ��� �����ڽ��� x�� ���ڽ����� ����
			GET_ADDRESS(x)->l = x_l_r;
			if (x_l_r != _nil)
				x_l_rAddress->p = x;

			if (x_pAddress->p == _nil)
				_root = GET_ADDRESS(x)->p;	// ȸ���� �������� x�� �θ� ��Ʈ����.
		}
		// x�� ���θ��̴�.
		void rotateL(node* x)
		{
			node* x_p = GET_ADDRESS(x)->p;
			node* x_pAddress = GET_ADDRESS(x_p);
			node* x_r = GET_ADDRESS(x)->r;
			node* x_rAddress = GET_ADDRESS(x_r);
			node* x_r_l = x_rAddress->l;
			node* x_r_lAddress = GET_ADDRESS(x_r_l);

			// x�� �����ڽ��� �ø�
			if (x_pAddress->r == x)
				x_pAddress->r = x_r;
			else
				x_pAddress->l = x_r;
			x_rAddress->p = x_p;

			// x�� x_r�� ���ڽ����� ����
			x_rAddress->l = x;
			GET_ADDRESS(x)->p = x_r;

			// x�� ���� �����ڽ��� ���ڽ��� x�� �����ڽ����� ����
			GET_ADDRESS(x)->r = x_r_l;
			if (x_r_l != _nil)
				x_r_lAddress->p = x;

			if (x_pAddress->p == _nil)
				_root = GET_ADDRESS(x)->p;	// ȸ���� �������� x�� �θ� ��Ʈ����.
		}
		void fixedInsert(node* x)
		{	// �Ű����� x�� �����.
			node* x_p = GET_ADDRESS(x)->p;
			node* x_pAddress = GET_ADDRESS(x_p);
			node* x_p_p;	//���� ���θ� ���� ��

			while (GET_COLOR(x_p) == RED)
			{	//x_pAddress->p�� ���� �׻� �� (�ڽ��� �����)
				x_p = GET_ADDRESS(x)->p;
				x_pAddress = GET_ADDRESS(x_p); 
				x_p_p = x_pAddress->p;	//�׻� ���θ�� ����
				if (x_p_p->l == x_p)
				{	//�θ� ���θ��� �����ڽ�
					if (GET_COLOR(x_p_p->r) == RED)
					{	//case 1
						SET_BLACK(x_p);
						SET_BLACK(x_p_p->r);
						SET_RED(x_p_p);
						x = x_p_p;	//����� x_p_p�� ���� x�� ���
						x_p = GET_ADDRESS(x)->p;
						x_pAddress = GET_ADDRESS(x_p);
						// while�� ������ �ٽ� ����
					}
					else
					{	//case 2
						if (x_pAddress->r == x)
						{
							x = x_p;
							rotateL(x);
							x_p = GET_ADDRESS(x)->p;
							x_pAddress = GET_ADDRESS(x_p);
							x_p_p = x_pAddress->p;	// case3 ���� �غ�
						}
						//case 3 : ��-��-�� 1����, x�� ����*3
						SET_BLACK(x_p);
						SET_RED(x_p_p);
						rotateR(x_p_p);	// ���� x_p_p�� ���� ��ȸ��
						// x_p�� ���̹Ƿ� while�� ������
					}
				}
				else
				{	//�θ� ���θ��� �������ڽ�
					if (GET_COLOR(x_p_p->l) == RED)
					{	//case 1
						SET_BLACK(x_p);
						SET_BLACK(x_p_p->l);
						SET_RED(x_p_p);
						x = x_p_p;
						x_p = GET_ADDRESS(x)->p;
						x_pAddress = GET_ADDRESS(x_p);
						// while�� ������ �ٽ� ����
					}
					else
					{
						//case 2
						if (x_pAddress->l == x)
						{
							x = x_p;
							rotateR(x);
							x_p = GET_ADDRESS(x)->p;
							x_pAddress = GET_ADDRESS(x_p);
							x_p_p = x_pAddress->p;	// case3 ���� �غ�
						}
						//case 3 : ��-��-�� 1����, x�� ����*3
						SET_BLACK(x_p);
						SET_RED(x_p_p);
						rotateL(x_p_p);	// ���� x_p_p�� ���� ��ȸ��
						// x_p�� ���̹Ƿ� while�� ������
					}
				}
			}
			SET_BLACK(_root);	//��Ʈ�� �׻� ��
		}
		void fixedDelete(node* x)
		{
			while (GET_ADDRESS(x) != _root && GET_COLOR(x) == BLACK)
			{
				
			}

			SET_BLACK(x);
		}
		// �ٷ� ���� �ڽ��� ���� �ø� �� ����Ѵ�.
		void transparent(node* u, node* x, bool isLeft)
		{
			node* u_p = GET_ADDRESS(u)->p;
			node* u_pAddress = GET_ADDRESS(u_p);
			node* u_r = GET_ADDRESS(u)->r;
			node* u_rAddress = GET_ADDRESS(u_r);
			node* u_l = GET_ADDRESS(u)->l;
			node* u_lAddress = GET_ADDRESS(u_l);
			if (u_pAddress->l == u)
			{
				u_pAddress->l = x;
				GET_ADDRESS(x)->p = u_p;
				if (isLeft)
				{
					u_rAddress->p = x;
					GET_ADDRESS(x)->r = u_r;
				}
				else
				{
					u_lAddress->p = x;
					GET_ADDRESS(x)->l = u_l;
				}
			}
			else if (u_pAddress->r == u)
			{
				u_pAddress->r = x;
				GET_ADDRESS(x)->p = u_pAddress;
				if (isLeft)
				{
					u_rAddress->p = x;
					GET_ADDRESS(x)->r = u_r;
				}
				else
				{
					u_lAddress->p = x;
					GET_ADDRESS(x)->l = u_l;
				}
			}
			else // u_p = _nil (u�� ��Ʈ�� ���)
			{	//��Ʈ ������ ���⼭ ���� ����.
				GET_ADDRESS(x)->p = _nil;
				if (isLeft)
				{
					u_rAddress->p = x;
					GET_ADDRESS(x)->r = u_r;
				}
				else
				{
					u_lAddress->p = x;
					GET_ADDRESS(x)->l = u_l;
				}
			}
		}
		node* minRSub(node* x)
		{	// x-�� �����ڽ��� nil�� ���� ���� ���� ����.
			// = x_subAddress->l �� �׻� nullptr�� �ƴ� (nullptr�� _nil�� �������� �� ����)
			node* x_sub = GET_ADDRESS(x)->r;
			node* x_subAddress = GET_ADDRESS(x_sub);

			while (x_subAddress->l != _nil)
			{
				x_sub = x_subAddress->l;
				x_subAddress = GET_ADDRESS(x_sub);
			}
			return x_sub;	// r�� nil�̸� x->r�� ����.
		}
	};
}


#endif