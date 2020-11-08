#pragma once
#include <assert.h>
#include <algorithm>
#include <list>

template<class Type1, class Type2>
class mmap_iterator;

template <class Type1, class Type2>
struct pair
{
	Type1 first;
	Type2 second;

	pair(Type1 first, Type2 second)
	{
		this->first = first;
		this->second = second;
	}
};

template <class Type1, class Type2>
class mmap
{
private:
	const unsigned int SIZE_CAPACITY = 128;

	std::list<pair<Type1, Type2>> _data;
	unsigned int _size;

public:
	friend class mmap_iterator<Type1, Type2>;
	using iterator = mmap_iterator<Type1, Type2>;

public:
	mmap();
	mmap(const mmap<Type1, Type2>& other);
	~mmap();

public:
	const unsigned int size() const;
	const bool empty() const;

public:
	const Type2& operator[](const unsigned int key) const;
	const Type2& at(const Type1 key) const;

public:
	void insert(const pair<Type1, Type2>& item);
	void swap(mmap<Type1, Type2>& other);
	void clear();

public:
	typename iterator begin();
	typename iterator end();

public:
	iterator find(const Type2 key);
};

template <class Type1, class Type2>
mmap<Type1, Type2>::mmap()
	:_size(0),
	_data()
{
}

template <class Type1, class Type2>
mmap<Type1, Type2>::mmap(const mmap<Type1, Type2>& other)
	:_size(other._size)
{
	_data = other._data;
}

template <class Type1, class Type2>
mmap<Type1, Type2>::~mmap()
{
}

template <class Type1, class Type2>
const unsigned int mmap<Type1, Type2>::size() const
{
	return _size;
}

template <class Type1, class Type2>
const bool mmap<Type1, Type2>::empty() const
{
	if (_size > 0)
	{
		return true;
	}

	return false;
}

template <class Type1, class Type2>
const Type2& mmap<Type1, Type2>::operator[](const unsigned int key) const
{
	return at(key);
}

template <class Type1, class Type2>
const Type2& mmap<Type1, Type2>::at(const Type1 key) const
{
	for (auto i = _data.begin(); i != _data.end(); i++)
	{
		if (key == i->first)
		{
			return i->second;
		}
	}

	return Type2();
}

template <class Type1, class Type2>
void mmap<Type1, Type2>::insert(const pair<Type1, Type2>& item)
{
	for (auto i = _data.begin(); i != _data.end(); i++)
	{
		if (i->first == item.first)
		{
			return;
		}
	}

	for (auto i = _data.begin(); i != _data.end(); i++)
	{
		if (item.first <= i->first)
		{
			_data.insert(i, item);
			_size++;
			return;
		}
	}

	_data.push_back(item);
	_size++;
}

template <class Type1, class Type2>
void mmap<Type1, Type2>::swap(mmap<Type1, Type2>& other)
{
	unsigned int size_temp = _size;
	_size = other._size;
	other._size = size_temp;

	std::list<pair<Type1, Type2>> buffer_temp = _data;
	_data = other._data;
	other._data = buffer_temp;
}

template <class Type1, class Type2>
void mmap<Type1, Type2>::clear()
{
	_size = 0;
	_data.clear();
}

template <class Type1, class Type2>
typename mmap<Type1, Type2>::iterator mmap<Type1, Type2>::begin()
{
	mmap<Type1, Type2>::iterator iter(0, this);
	return iter;
}

template <class Type1, class Type2>
typename mmap<Type1, Type2>::iterator mmap<Type1, Type2>::end()
{
	mmap<Type1, Type2>::iterator iter(_size, this);
	return iter;
}

template<class Type1, class Type2>
typename mmap<Type1, Type2>::iterator mmap<Type1, Type2>::find(const Type2 key)
{
	auto i = this->begin();
	for (; i != this->end(); i++)
	{
		if (key == i->first)
		{
			break;
		}
	}
	return i;
}


//
//
//mmap_iterator class
//
//

template<class Type1, class Type2>
class mmap_iterator
{
private:
	mmap<Type1, Type2>* pMap;
	unsigned int _index;

public:
	friend class mmap<Type1, Type2>;
	mmap_iterator();
	mmap_iterator(const unsigned int index, mmap<Type1, Type2>* vector);

	mmap_iterator& operator++();
	mmap_iterator operator++(int);
	mmap_iterator& operator--();
	mmap_iterator operator--(int);

	const pair<Type1, Type2>& operator*() const;

	const pair<Type1, Type2>* operator->() const;

	mmap_iterator& operator+=(const unsigned int n);
	mmap_iterator operator+(const unsigned int n);
	mmap_iterator& operator-=(const unsigned int n);
	mmap_iterator operator-(const unsigned int n);

	bool operator==(const mmap_iterator<Type1, Type2> right);
	bool operator!=(const mmap_iterator<Type1, Type2> right);
	bool operator<(const mmap_iterator<Type1, Type2> right);
	bool operator<=(const mmap_iterator<Type1, Type2> right);
	bool operator>(const mmap_iterator<Type1, Type2> right);
	bool operator>=(const mmap_iterator<Type1, Type2> right);
};

template<class Type1, class Type2>
mmap_iterator<Type1, Type2>::mmap_iterator()
	:_index(0),
	pMap(nullptr)
{
}

template<class Type1, class Type2>
mmap_iterator<Type1, Type2>::mmap_iterator(const unsigned int index, mmap<Type1, Type2>* map)
	:_index(index),
	pMap(map)
{
}

template<class Type1, class Type2>
mmap_iterator<Type1, Type2>& mmap_iterator<Type1, Type2>::operator++()
{
	if (_index >= pMap->size())
	{
		assert(("out of range iterator: condition: ", _index > pMap->size()));
	}
	++(this->_index);
	return *this;
}

template<class Type1, class Type2>
mmap_iterator<Type1, Type2> mmap_iterator<Type1, Type2>::operator++(int)
{
	if (_index >= pMap->size())
	{
		assert(("out of range iterator: condition: ", _index > pMap->size()));
	}
	mmap_iterator<Type1, Type2> temp = *this;
	(this->_index)++;
	return temp;
}

template<class Type1, class Type2>
mmap_iterator<Type1, Type2>& mmap_iterator<Type1, Type2>::operator--()
{
	if (_index == 0)
	{
		assert(("out of range iterator : condition: ", _index > 0));
	}
	--(this->_index);
	return *this;
}

template<class Type1, class Type2>
mmap_iterator<Type1, Type2> mmap_iterator<Type1, Type2>::operator--(int)
{
	if (_index == 0)
	{
		assert(("out of range iterator: condition: ", _index > 0));
	}
	mmap_iterator<Type1, Type2> temp = *this;
	(this->_index)--;
	return temp;
}

template<class Type1, class Type2>
const pair<Type1, Type2>& mmap_iterator<Type1, Type2>::operator*() const
{
	unsigned int count = 0;
	for (auto i = pMap->_data.begin(); i != pMap->_data.end(); i++)
	{
		if (count == _index)
		{
			const pair<Type1, Type2>& val = *i;
			return val;
		}
		count++;
	}
}

template<class Type1, class Type2>
const pair<Type1, Type2>* mmap_iterator<Type1, Type2>::operator->() const
{
	unsigned int count = 0;
	for (auto i = pMap->_data.begin(); i != pMap->_data.end(); i++)
	{
		if (count == _index)
		{
			pair<Type1, Type2>* val = &*i;
			return val;
		}
		count++;
	}
}

template<class Type1, class Type2>
mmap_iterator<Type1, Type2>& mmap_iterator<Type1, Type2>::operator+=(const unsigned int n)
{
	if (_index + n >= pMap->size())
	{
		assert(("cannot seek map iterator after end, condition:", _index + n < pMap->size()));
	}
	(this->_index) += n;
	return *this;
}

template<class Type1, class Type2>
mmap_iterator<Type1, Type2> mmap_iterator<Type1, Type2>::operator+(const unsigned int n)
{
	if (_index + n >= pMap->size())
	{
		assert(("cannot seek map iterator after end, condition:", _index + n < pMap->size()));
	}
	mmap_iterator<Type1, Type2> temp = *this;
	(temp._index) += n;
	return temp;
}

template<class Type1, class Type2>
mmap_iterator<Type1, Type2>& mmap_iterator<Type1, Type2>::operator-=(const unsigned int n)
{
	if (static_cast<int>(_index) - static_cast<int>(n) < 0)
	{
		assert(("cannot seek map iterator before begin, condition:", static_cast<int>(_index) - static_cast<int>(n) >= 0));
	}
	(this->_index) -= n;
	return *this;
}

template<class Type1, class Type2>
mmap_iterator<Type1, Type2> mmap_iterator<Type1, Type2>::operator-(const unsigned int n)
{
	if (static_cast<int>(_index) - static_cast<int>(n))
	{
		assert(("cannot seek map iterator before begin, condition:", static_cast<int>(_index) - static_cast<int>(n) >= 0));
	}
	mmap_iterator<Type1, Type2> temp = *this;
	(temp._index) -= n;
	return temp;
}

template<class Type1, class Type2>
bool mmap_iterator<Type1, Type2>::operator==(const mmap_iterator<Type1, Type2> right)
{
	if (this->pMap != right.pMap)
	{
		assert(("map iterators incompatible, condition:", this->pMap == right.pMap));
	}

	if (this->_index == right._index)
	{
		return true;
	}

	return false;
}

template<class Type1, class Type2>
bool mmap_iterator<Type1, Type2>::operator!=(const mmap_iterator<Type1, Type2> right)
{
	if (*this == right)
	{
		return false;
	}

	return true;
}

template<class Type1, class Type2>
bool mmap_iterator<Type1, Type2>::operator<(const mmap_iterator<Type1, Type2> right)
{
	if (this->pMap != right.pMap)
	{
		assert(("map iterators incompatible, condition:", this->pMap == right.pMap));
	}

	if (this->_index < right._index)
	{
		return true;
	}

	return false;
}

template<class Type1, class Type2>
bool mmap_iterator<Type1, Type2>::operator<=(const mmap_iterator<Type1, Type2> right)
{
	if (*this > right)
	{
		return false;
	}

	return true;
}

template<class Type1, class Type2>
bool mmap_iterator<Type1, Type2>::operator>(const mmap_iterator<Type1, Type2> right)
{
	if (this->pMap != right.pMap)
	{
		assert(("map iterators incompatible, condition:", this->pMap == right.pMap));
	}

	if (this->_index > right._index)
	{
		return true;
	}

	return false;
}

template<class Type1, class Type2>
bool mmap_iterator<Type1, Type2>::operator>=(const mmap_iterator<Type1, Type2> right)
{
	if (*this < right)
	{
		return false;
	}

	return true;
}

