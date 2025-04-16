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
#define GET_COLOR(x)	((int)((__int64)(x) & 0x8000'0000'0000'0000) >> 63)
#define GET_ADDRESS(x)	((map<KEY, VAL>::node*)((__int64)(x) & 0x7FFF'FFFF'FFFF'FFFF))

#define SET_RED(x)		do{														\
	(x) = (map<KEY, VAL>::node*)((__int64)(x) | 0x8000'0000'0000'0000);			\
	node* xAddress = GET_ADDRESS(x);											\
	node* x_pAddress = GET_ADDRESS(xAddress->p);								\
	if(xAddress->l != _nil)														\
		GET_ADDRESS(xAddress->l)->p = (x);										\
	if(xAddress->r != _nil)														\
		GET_ADDRESS(xAddress->r)->p = (x);										\
	if(x_pAddress != nullptr && x_pAddress != _root)							\
	{																			\
		if(GET_ADDRESS(x_pAddress->r) == xAddress)								\
			x_pAddress->r = (x);												\
		else																	\
			x_pAddress->l = (x);												\
	}																			\
}while(0)

#define SET_BLACK(x)		do{													\
	((x) = (map<KEY, VAL>::node*)((__int64)(x) & 0x7FFF'FFFF'FFFF'FFFF));		\
	node* xAddress = GET_ADDRESS(x);											\
	node* x_pAddress = GET_ADDRESS(xAddress->p);								\
	if(xAddress->l != _nil)														\
		GET_ADDRESS(xAddress->l)->p = (x);										\
	if(xAddress->r != _nil)														\
		GET_ADDRESS(xAddress->r)->p = (x);										\
	if(x_pAddress != nullptr && x_pAddress != _root)							\
	{																			\
		if(GET_ADDRESS(x_pAddress->r) == xAddress)								\
			x_pAddress->r = (x);												\
		else																	\
			x_pAddress->l = (x);												\
	}																			\
}while(0)
#else //_WIN32
#define GET_COLOR(x)	((int)((__int64)(x) & 0x8000'0000) >> 31)
#define GET_ADDRESS(x)	((map<KEY, VAL>::node*)((__int64)(x) & 0x7FFF'FFFF))

#define SET_RED(x)		do{														\
	(x) = (map<KEY, VAL>::node*)((__int64)(x) | 0x8000'0000);					\
	node* xAddress = GET_ADDRESS(x);											\
	node* x_pAddress = GET_ADDRESS(xAddress->p);								\
	if(xAddress->l != _nil)														\
		GET_ADDRESS(xAddress->l)->p = (x);										\
	if(xAddress->r != _nil)														\
		GET_ADDRESS(xAddress->r)->p = (x);										\
	if(x_pAddress != nullptr && x_pAddress != _root)							\
	{																			\
		if(GET_ADDRESS(x_pAddress->r) == xAddress)								\
			x_pAddress->r = (x);												\
		else																	\
			x_pAddress->l = (x);												\
	}																			\
}while(0)

#define SET_BLACK(x)		do{													\
	((x) = (map<KEY, VAL>::node*)((__int64)(x) & 0x7FFF'FFFF));					\
	node* xAddress = GET_ADDRESS(x);											\
	node* x_pAddress = GET_ADDRESS(xAddress->p);								\
	if(xAddress->l != _nil)														\
		GET_ADDRESS(xAddress->l)->p = (x);										\
	if(xAddress->r != _nil)														\
		GET_ADDRESS(xAddress->r)->p = (x);										\
	if(x_pAddress != nullptr && x_pAddress != _root)							\
	{																			\
		if(GET_ADDRESS(x_pAddress->r) == xAddress)								\
			x_pAddress->r = (x);												\
		else																	\
			x_pAddress->l = (x);												\
	}																			\
}while(0)
#endif



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
		
		map() :_root(nullptr), _nil(new node()), _size(0)
		{ 
			// _nil�� ���� ��ü�� ��, (�ּ��� ����1��Ʈ�� 0)
			_nil->p = _nil;
			_nil->l = _nil;
			_nil->r = _nil;
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

		~map()
		{
			// ��ȸ
			delete _nil;
		}
	private:
		node* _root;
		node* _nil;
		size_t _size;

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

			if (GET_ADDRESS(x) == GET_ADDRESS(_root))
				_root = GET_ADDRESS(x)->p;	// ȸ���� �������� x�� �θ� ��Ʈ����.
		}
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

			if (GET_ADDRESS(x) == GET_ADDRESS(_root))
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
						x = x_p_p;	
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
						//case 3 : ��-��-�� 1����, x�� ��
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
						// while�� ������ �ٽ� ����
					}
					else
					{

					}
				}
			}
			SET_BLACK(_root);	//��Ʈ�� �׻� ��
		}
		void fixedDelete()
		{

		}
	};
}


#endif