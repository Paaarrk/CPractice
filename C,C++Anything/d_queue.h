#ifndef __D_QUEUE_H__
#define __D_QUEUE_H__

//----------------------------------------------------------
// 원형 큐
// FIFO 선입선출
// FIFO 특성을 위해 반복자의 -- 연산자 구현 X
//----------------------------------------------------------

namespace my
{
	template <class T>
	class queue
	{
		friend class iterator;
	public:
		class iterator
		{
		public:
			iterator(queue<T>* q, T* ptr = nullptr) :_ptr(ptr), _q(q){}
			iterator(const iterator& ref):_ptr(ref._ptr), _q(ref._q){}
			~iterator(){}
			T& operator*() { return *_ptr; }
			T* operator->() { return _ptr; }
			bool operator==(const iterator& other) { return (_ptr == other._ptr); }
			bool operator!=(const iterator& other) { return !(*this == other); }
			iterator& operator++()
			{
				_ptr++;
				if (_ptr == _q->_queue + _q->_cap)
					_ptr = _q->_queue;
				return *this;
			}
			iterator operator++(int)
			{
				T* tmp = _ptr++;
				if (_ptr == _q->_queue + _q->_cap)
					_ptr = _q->_queue;
				return iterator(_q, tmp);
			}
		private:
			T* _ptr;
			queue<T>* _q;
		};

		queue(size_t cap = 0) :_size(0), _cap(cap), _head(0), _tail(0), _queue(nullptr) 
		{
			if (cap != 0)
				_queue = (T*)malloc(sizeof(T) * cap);
		}
		/* 기존 _cap에 cap만큼 예약을늘립니다. */
#pragma warning(push)
#pragma warning(disable : 6387)
/* malloc 의 nullptr시 강제종료가 목적입니다. */
		void reserve(size_t cap)
		{
			if (cap <= 0)
				return;
			if (_cap == 0)
				_queue = (T*)malloc(sizeof(T) * cap);
			else if (_tail > _head)
			{
				T* tmp = (T*)malloc(sizeof(T) * (_cap + cap));
				memcpy(tmp + _head, _queue + _head, sizeof(T)*(_tail - _head));
				free(_queue);
				_queue = tmp;
			}
			else
			{
				T* tmp = (T*)malloc(sizeof(T) * (_cap + cap));
				memcpy(tmp, _queue, sizeof(T)*_tail);	//앞에 복사
				memcpy(tmp + (cap +_head), _queue + _head, sizeof(T) * (_cap - _head));	//뒤에 복사
				free(_queue);
				_queue = tmp;
				_head += cap;
			}
			_cap += cap;
		}
#pragma warning(pop)
		void push(const T& data)
		{
			if (_size != 0 && _head == _tail)
			{
				reserve(_cap);
			}
			_queue[_tail] = data;

			_size++;
			_tail++;
			if (_tail == _cap)
				_tail = 0;
		}
		void pop()
		{
			if (_size == 0)
				return;
			_queue[_head].~T();

			_size--;
			_head++;
			if (_head == _cap)
				_head = 0;
		}
		T* peek()
		{
			if (_size == 0)
				return nullptr;
			return &_queue[_head];
		}
		iterator begin() { return iterator(this, _queue + _head); }
		iterator end() { return iterator(this, _queue + _tail); }
		void clear()
		{
			for (iterator it = begin(); it != end(); it++)
			{
				(*it).~T();
			}
			free(_queue);
			_size = 0;
			_head = 0;
			_tail = 0;
		}
		size_t size() { return _size; }
	private:
		T* _queue;
		size_t _head;
		size_t _tail;
		size_t _size;
		size_t _cap;
	};
}

#endif