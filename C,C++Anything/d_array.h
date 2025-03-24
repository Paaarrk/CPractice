#ifndef _D_ARRAY_H__
#define _D_ARRAY_H__

//----------------------------------------------------------------
// 정적 배열
// std::initializer_list<T> 사용해보기
// 실제로는 잘 사용 안할 것 같은 배열
// LIFO 후입선출
//----------------------------------------------------------------

namespace my
{
	template <class T, size_t _size>
	class array
	{
	public:
		class iterator
		{
		public:
			iterator(T* ptr = nullptr) :_ptr(ptr) {}
			~iterator(){}
			T& operator* () { return *_ptr; }
			T* operator->() { return _ptr; }
			T& operator[](ptrdiff_t idx) { return *(_ptr + idx); }
			bool operator==(const iterator& other) { return (_ptr == other._ptr); }
			bool operator!=(const iterator& other) { return !(*this == other); }
			iterator& operator++()
			{
				++_ptr;
				return *this;
			}
			iterator operator++(int)
			{
				T* tmp = _ptr++;
				return iterator(tmp);
			}
			iterator& operator--()
			{
				--_ptr;
				return *this;
			}
			iterator operator--(int)
			{
				T* tmp = _ptr--;
				return iterator(tmp);
			}
			iterator operator+(ptrdiff_t idx)
			{
				return iterator(_ptr + idx);
			}
			iterator operator-(ptrdiff_t idx)
			{
				return iterator(_ptr - idx);
			}
			iterator& operator+=(ptrdiff_t idx)
			{
				_ptr += idx;
				return *this;
			}
			iterator& operator-=(ptrdiff_t idx)
			{
				_ptr -= idx;
				return *this;
			}
		private:
			T* _ptr;
		};

		array() {}
		array(std::initializer_list<T> list)
		{
			size_t i = 0;
			for (auto& elem : list)
			{
				_arr[i++] = elem;
			}
		}
		iterator begin() { return iterator(_arr); }
		iterator end() { return iterator(_arr + _size); }
		T& operator[](ptrdiff_t idx)
		{
			return _arr[idx];
		}
	private:
		T _arr[_size];
	};
}

#endif