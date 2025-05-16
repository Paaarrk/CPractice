#ifndef __RED_BLACK_TREE_H__
#define __RED_BLACK_TREE_H__


namespace my
{
	template <typename KEY, typename VAL>
	class map;
// 레드가 상위 1비트가 1, 블랙은 0
// 색상은 상위 1비트에 저장한다.
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
			VAL value;	// 값
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
				
				if (x_rAddress->r != nullptr)//nil이 아니면 
				{	
					_node = x_r;	// 오른쪽 노드로 이동
					x_l = GET_ADDRESS(_node)->l;	//왼자식 재 세팅
					x_lAddress = GET_ADDRESS(x_l);
					while (x_lAddress->l != nullptr)	// 왼자식이 nil일 때 까지
					{
						_node = x_l;	// 왼자식이 nil일때까지 내려감
						x_l = GET_ADDRESS(_node)->l;	//왼자식 재 세팅
						x_lAddress = GET_ADDRESS(x_l);
					}
				}
				else
				{	//오른쪽으로 갈 수 없는 상태-> 서브트리를 다 돌은 상태
					// 내가 처음으로 오른자식이 아닐 때 까지 올라감
					while (x_pAddress->r == _node)
					{
						_node = x_p;
						x_p = GET_ADDRESS(_node)->p;
						x_pAddress = GET_ADDRESS(x_p);
					}
					// 다 올라왔으면 이제 부모가 다음 대상임
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

				if (x_rAddress->r != nullptr)//nil이 아니면 
				{
					_node = x_r;	// 오른쪽 노드로 이동
					x_l = GET_ADDRESS(_node)->l;	//왼자식 재 세팅
					x_lAddress = GET_ADDRESS(x_l);
					while (x_lAddress->l != nullptr)	// 왼자식이 nil일 때 까지
					{
						_node = x_l;	// 왼자식이 nil일때까지 내려감
						x_l = GET_ADDRESS(_node)->l;	//왼자식 재 세팅
						x_lAddress = GET_ADDRESS(x_l);
					}
				}
				else
				{	//오른쪽으로 갈 수 없는 상태-> 서브트리를 다 돌은 상태
					// 내가 처음으로 오른자식이 아닐 때 까지 올라감
					while (x_pAddress->r == _node)
					{
						_node = x_p;
						x_p = GET_ADDRESS(_node)->p;
						x_pAddress = GET_ADDRESS(x_p);
					}
					// 다 올라왔으면 이제 부모가 다음 대상임
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

				if (x_lAddress->l != nullptr)//nil이 아니면 
				{
					_node = x_l;	// 왼쪽 노드로 이동
					x_r = GET_ADDRESS(_node)->r;	//오른자식 재 세팅
					x_rAddress = GET_ADDRESS(x_r);
					while (x_rAddress->r != nullptr)	// 오른자식이 nil일 때 까지
					{
						_node = x_r;	// 왼자식이 nil일때까지 내려감
						x_r = GET_ADDRESS(_node)->r;	//왼자식 재 세팅
						x_rAddress = GET_ADDRESS(x_r);
					}
				}
				else
				{	//왼쪽으로 갈 수 없는 상태-> 서브트리를 다 돌은 상태
					// 내가 처음으로 왼자식이 아닐 때 까지 올라감
					while (x_pAddress->l == _node)
					{
						_node = x_p;
						x_p = GET_ADDRESS(_node)->p;
						x_pAddress = GET_ADDRESS(x_p);
					}
					// 다 올라왔으면 이제 부모가 다음 대상임
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

				if (x_lAddress->l != nullptr)//nil이 아니면 
				{
					_node = x_l;	// 왼쪽 노드로 이동
					x_r = GET_ADDRESS(_node)->r;	//오른자식 재 세팅
					x_rAddress = GET_ADDRESS(x_r);
					while (x_rAddress->r != nullptr)	// 오른자식이 nil일 때 까지
					{
						_node = x_r;	// 왼자식이 nil일때까지 내려감
						x_r = GET_ADDRESS(_node)->r;	//왼자식 재 세팅
						x_rAddress = GET_ADDRESS(x_r);
					}
				}
				else
				{	//왼쪽으로 갈 수 없는 상태-> 서브트리를 다 돌은 상태
					// 내가 처음으로 왼자식이 아닐 때 까지 올라감
					while (x_pAddress->l == _node)
					{
						_node = x_p;
						x_p = GET_ADDRESS(_node)->p;
						x_pAddress = GET_ADDRESS(x_p);
					}
					// 다 올라왔으면 이제 부모가 다음 대상임
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
			// 루트가 없으면
			if (_root == nullptr)
			{
				_root = n;
				GET_ADDRESS(_root)->p = _nil;
				SET_BLACK(_root);
			}
			else
			{
				// 넣을 곳 탐색
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
					else// 같을때, 중복키, 에러
					{
						delete GET_ADDRESS(n);
						_size--;
						return false;
					}
				}

				//넣기
				if (isLeft)
					GET_ADDRESS(search)->l = n;
				else //right
					GET_ADDRESS(search)->r = n;
				GET_ADDRESS(n)->p = search;

				// 더블레드 fixedup
				fixedInsert(n);
			}
			return true;
		}
		VAL* find(const KEY& key)	// 등록한 데이터의 주소를뱉음.
		{
			// 트리가 비었으면 nullptr 
			if (_size == 0)
				return nullptr;

			node* search = _root;
			while (search != _nil)
			{
				if (GET_ADDRESS(search)->key < key)
					search = (GET_ADDRESS(search)->r);
				else if (GET_ADDRESS(search)->key > key)
					search = (GET_ADDRESS(search)->l);
				else // 같음
					return &(search->value);
			}
			return nullptr;
		}
		bool Delete(const KEY& key)
		{
			if (_size == 0)
				return false;

			node* search = _root;
			node* Delete;	// 삭제 대상
			node* fixed;	// 균형 대상
			while (search != _nil)
			{
				if (GET_ADDRESS(search)->key < key)
					search = (GET_ADDRESS(search)->r);
				else if (GET_ADDRESS(search)->key > key)
					search = (GET_ADDRESS(search)->l);
				else // 같음
					break;
			}
			if(search == _nil)
				return false;

			int originalColor;	//오른자식이 올라오면서 실제로 사라지게 되는 색 (삭제 노드 색 아님)
			node* minRight;
			//찾았으니 삭제 진행..
			if (GET_ADDRESS(search)->l == _nil)
			{	// 왼쪽 자식이 없음
				originalColor = GET_COLOR(search);
				fixed = GET_ADDRESS(search)->r;
				transparent(search, fixed, false);	//false는 fixed가 search의 오른쪽이라는뜻
				Delete = search;
			}
			else if (GET_ADDRESS(search)->r == _nil)
			{	// 오른쪽 자식이 없음
				originalColor = GET_COLOR(search);
				fixed = GET_ADDRESS(search)->l;
				transparent(search, fixed, true); // true는 fixed가 search의 왼쪽이라는 뜻
				Delete = search;
			}
			else
			{
				minRight = minRSub(search);
				// 삭제할 자리에 그대로 복사, search더이상 사용 불가
				search->key = minRight->key;
				search->value = minRight->value;

				originalColor = GET_COLOR(minRight);
				fixed = GET_ADDRESS(minRight)->r;
				transparent(minRight, fixed, false);	// minRight가 fixed의 오른쪽 이라는 뜻
				Delete = minRight;	//삭제 대상
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
			// 순회
			delete _nil;
		}
		size_t size() const { return _size; }
	private:
		node* _root;
		node* _nil;
		size_t _size;

		// x는 조부모이다.
		void rotateR(node* x)
		{
			node* x_p = GET_ADDRESS(x)->p;
			node* x_pAddress = GET_ADDRESS(x_p);
			node* x_l = GET_ADDRESS(x)->l;
			node* x_lAddress = GET_ADDRESS(x_l);
			node* x_l_r = x_lAddress->r;
			node* x_l_rAddress = GET_ADDRESS(x_l_r);
			
			// x의 왼자식을 올림
			if (x_pAddress->r == x)
				x_pAddress->r = x_l;
			else
				x_pAddress->l = x_l;
			x_lAddress->p = x_p;

			// x를 x_l의 오른자식으로 붙임
			x_lAddress->r = x;
			GET_ADDRESS(x)->p = x_l;
			
			// x의 기존 왼자식의 오른자식을 x의 왼자식으로 붙임
			GET_ADDRESS(x)->l = x_l_r;
			if (x_l_r != _nil)
				x_l_rAddress->p = x;

			if (x_pAddress->p == _nil)
				_root = GET_ADDRESS(x)->p;	// 회전이 끝났으니 x의 부모가 루트가됨.
		}
		// x는 조부모이다.
		void rotateL(node* x)
		{
			node* x_p = GET_ADDRESS(x)->p;
			node* x_pAddress = GET_ADDRESS(x_p);
			node* x_r = GET_ADDRESS(x)->r;
			node* x_rAddress = GET_ADDRESS(x_r);
			node* x_r_l = x_rAddress->l;
			node* x_r_lAddress = GET_ADDRESS(x_r_l);

			// x의 오른자식을 올림
			if (x_pAddress->r == x)
				x_pAddress->r = x_r;
			else
				x_pAddress->l = x_r;
			x_rAddress->p = x_p;

			// x를 x_r의 왼자식으로 붙임
			x_rAddress->l = x;
			GET_ADDRESS(x)->p = x_r;

			// x의 기존 오른자식의 왼자식을 x의 오른자식으로 붙임
			GET_ADDRESS(x)->r = x_r_l;
			if (x_r_l != _nil)
				x_r_lAddress->p = x;

			if (x_pAddress->p == _nil)
				_root = GET_ADDRESS(x)->p;	// 회전이 끝났으니 x의 부모가 루트가됨.
		}
		void fixedInsert(node* x)
		{	// 매개변수 x도 변경됨.
			node* x_p = GET_ADDRESS(x)->p;
			node* x_pAddress = GET_ADDRESS(x_p);
			node* x_p_p;	//아직 조부모 여부 모름

			while (GET_COLOR(x_p) == RED)
			{	//x_pAddress->p의 색은 항상 블랙 (자식이 레드라서)
				x_p = GET_ADDRESS(x)->p;
				x_pAddress = GET_ADDRESS(x_p); 
				x_p_p = x_pAddress->p;	//항상 조부모는 검정
				if (x_p_p->l == x_p)
				{	//부모가 조부모의 왼쪽자식
					if (GET_COLOR(x_p_p->r) == RED)
					{	//case 1
						SET_BLACK(x_p);
						SET_BLACK(x_p_p->r);
						SET_RED(x_p_p);
						x = x_p_p;	//변경된 x_p_p를 다음 x로 사용
						x_p = GET_ADDRESS(x)->p;
						x_pAddress = GET_ADDRESS(x_p);
						// while로 나가서 다시 조사
					}
					else
					{	//case 2
						if (x_pAddress->r == x)
						{
							x = x_p;
							rotateL(x);
							x_p = GET_ADDRESS(x)->p;
							x_pAddress = GET_ADDRESS(x_p);
							x_p_p = x_pAddress->p;	// case3 진입 준비
						}
						//case 3 : 레-레-블 1자임, x는 레드*3
						SET_BLACK(x_p);
						SET_RED(x_p_p);
						rotateR(x_p_p);	// 변한 x_p_p를 상대로 우회전
						// x_p는 블랙이므로 while문 나가짐
					}
				}
				else
				{	//부모가 조부모의 오른쪽자식
					if (GET_COLOR(x_p_p->l) == RED)
					{	//case 1
						SET_BLACK(x_p);
						SET_BLACK(x_p_p->l);
						SET_RED(x_p_p);
						x = x_p_p;
						x_p = GET_ADDRESS(x)->p;
						x_pAddress = GET_ADDRESS(x_p);
						// while로 나가서 다시 조사
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
							x_p_p = x_pAddress->p;	// case3 진입 준비
						}
						//case 3 : 레-레-블 1자임, x는 레드*3
						SET_BLACK(x_p);
						SET_RED(x_p_p);
						rotateL(x_p_p);	// 변한 x_p_p를 상대로 우회전
						// x_p는 블랙이므로 while문 나가짐
					}
				}
			}
			SET_BLACK(_root);	//루트는 항상 블랙
		}
		void fixedDelete(node* x)
		{
			while (GET_ADDRESS(x) != _root && GET_COLOR(x) == BLACK)
			{
				
			}

			SET_BLACK(x);
		}
		// 바로 옆의 자식을 위로 올릴 때 사용한다.
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
			else // u_p = _nil (u가 루트란 얘기)
			{	//루트 설정은 여기서 하지 않음.
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
		{	// x-의 오른자식이 nil인 경우는 여기 오지 않음.
			// = x_subAddress->l 은 항상 nullptr이 아님 (nullptr은 _nil을 재참조할 때 나옴)
			node* x_sub = GET_ADDRESS(x)->r;
			node* x_subAddress = GET_ADDRESS(x_sub);

			while (x_subAddress->l != _nil)
			{
				x_sub = x_subAddress->l;
				x_subAddress = GET_ADDRESS(x_sub);
			}
			return x_sub;	// r이 nil이면 x->r을 뱉음.
		}
	};
}


#endif