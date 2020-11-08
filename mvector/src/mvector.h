#pragma once
#include <assert.h>

template<class Type>
class mvector_iterator;

template <class Type>
class mvector
{
private:
	const unsigned int SIZE_CAPACITY = 128;

	Type* _data;
	unsigned int _capacity;
	unsigned int _size;

private:
	unsigned int getCapacity(const unsigned int& size);

public:
	friend class mvector_iterator<Type>;

	using iterator = mvector_iterator<Type>;

public:
	mvector();
	mvector(const unsigned int size);
	mvector(const unsigned int size, const Type& initial);
	mvector(const mvector<Type>& other);
	~mvector();

public:
	const unsigned int size() const;
	const unsigned int capacity() const;
	const bool empty() const;

	void reserve(const unsigned int new_capacity);
	void resize(const unsigned int new_size);
	void resize(const unsigned int new_size, const Type& initial);
	void shink_to_fit();

public:
	Type& operator[](const unsigned int index);
	const Type& operator[](const unsigned int index) const;
	Type& at(const unsigned int index);
	const Type& at(const unsigned int index) const;
	Type& front();
	const Type& front() const;
	Type& back();
	const Type& back() const;

	Type* data();
	const Type*& data() const;

public:
	void push_back(const Type& item);
	void pop_back();
	void erase(const iterator pos);
	void erase(const iterator first, const iterator last);
	void insert(const iterator pos, const Type& val);
	void insert(const iterator pos, const iterator first, const iterator last);
	void swap(mvector<Type>& other);
	void assign(iterator first, const iterator last);
	void assign(const unsigned int size, const Type& value);
	void clear();

public:
	typename iterator begin();
	typename iterator end();
};

template<class Type>
unsigned int mvector<Type>::getCapacity(const unsigned int& size)
{
	return (size / SIZE_CAPACITY) * SIZE_CAPACITY + SIZE_CAPACITY;
}

template <class Type>
mvector<Type>::mvector()
	:_size(0),
	_capacity(SIZE_CAPACITY)
{
	_data = new Type[_capacity];

	for (unsigned int i = 0; i < _capacity; i++)
	{
		_data[i] = Type();
	}

}

template<class Type>
mvector<Type>::mvector(const unsigned int size)
	:_size(size),
	_capacity(getCapacity(size))
{
	_data = new Type[_capacity];

	for (unsigned int i = 0; i < _capacity; i++)
	{
		_data[i] = Type();
	}
}

template<class Type>
mvector<Type>::mvector(const unsigned int size, const Type& initial)
	:_size(size)
{
	_capacity = getCapacity(size);
	_data = new Type[_capacity];

	for (unsigned int i = 0; i < _size; i++)
	{
		_data[i] = initial;
	}
	for (unsigned int i = _size; i < _capacity; i++)
	{
		_data[i] = Type();
	}
}


template<class Type>
mvector<Type>::mvector(const mvector<Type>& other)
	:_capacity(other._capacity),
	_size(other._size)
{
	_data = new Type[_capacity];

	for (unsigned int i = 0; i < _size; i++)
	{
		_data[i] = other._data[i];
	}

	for (unsigned int i = _size; i < _capacity; i++)
	{
		_data[i] = Type();
	}
}

template<class Type>
mvector<Type>::~mvector()
{
	if (_data)
	{
		delete[] _data;
		_data = nullptr;
	}
}

template<class Type>
const unsigned int mvector<Type>::size() const
{
	return _size;
}

template<class Type>
const unsigned int mvector<Type>::capacity() const
{
	return _capacity;
}

template<class Type>
const bool mvector<Type>::empty() const
{
	if (_size > 0)
	{
		return true;
	}

	return false;
}

template<class Type>
void mvector<Type>::reserve(const unsigned int new_capacity)
{
	if (new_capacity > _capacity)
	{
		_capacity = getCapacity(new_capacity);

		Type* buffer = new Type[_capacity];

		for (unsigned int i = 0; i < _size; i++)
		{
			buffer[i] = _data[i];
		}

		for (unsigned int i = _size; i < _capacity; i++)
		{
			buffer[i] = Type();
		}

		if (_data)
		{
			delete[] _data;
			_data = nullptr;
		}
		_data = buffer;
		buffer = nullptr;
	}
}

template<class Type>
void mvector<Type>::resize(const unsigned int new_size)
{
	if (new_size > _capacity)
	{
		reserve(new_size);
		_size = new_size;
	}
	else if (new_size < _capacity)
	{
		if (new_size < _size)
		{
			for (unsigned int i = new_size; i < _size; i++)
			{
				_data[i] = Type();
			}
		}

		_size = new_size;
	}
}

template<class Type>
void mvector<Type>::resize(const unsigned int new_size, const Type& initial)
{
	if (new_size > _capacity)
	{
		_capacity = getCapacity(new_size);

		Type* buffer = new Type[_capacity];

		for (unsigned int i = 0; i < _size; i++)
		{
			buffer[i] = _data[i];
		}

		for (unsigned int i = _size; i < new_size; i++)
		{
			buffer[i] = initial;
		}

		for (unsigned int i = new_size; i < _capacity; i++)
		{
			buffer[i] = Type();
		}

		_size = new_size;

		if (_data)
		{
			delete[] _data;
			_data = nullptr;
		}
		_data = buffer;
		buffer = nullptr;
	}
	else if (new_size < _capacity)
	{
		if (new_size < _size)
		{
			for (unsigned int i = new_size; i < _size; i++)
			{
				_data[i] = Type();
			}
		}
		else if (new_size > _size)
		{
			for (unsigned int i = _size; i < new_size; i++)
			{
				_data[i] = initial;
			}
		}

		_size = new_size;
	}
}

template<class Type>
void mvector<Type>::shink_to_fit()
{
	_capacity = getCapacity(_size);
	Type* buffer = new Type[_capacity];

	for (unsigned int i = 0; i < _size; i++)
	{
		buffer[i] = _data[i];
	}

	for (unsigned int i = _size; i < _capacity; i++)
	{
		buffer[i] = Type();
	}

	if (_data)
	{
		delete[] _data;
		_data = nullptr;
	}
	_data = buffer;
	buffer = nullptr;
}

template<class Type>
Type& mvector<Type>::operator[](const unsigned int index)
{
	return at(index);
}

template<class Type>
const Type& mvector<Type>::operator[](const unsigned int index) const
{
	return at(index);
}

template<class Type>
Type& mvector<Type>::at(const unsigned int index)
{
	if (index < _size)
	{
		return _data[index];
	}

	assert(("vector subscript out of range, condition:", index < _size));
}

template<class Type>
const Type& mvector<Type>::at(const unsigned int index) const
{
	if (index < _size)
	{
		return _data[index];
	}

	assert(("vector subscript out of range, condition:", index < _size));
}

template<class Type>
Type& mvector<Type>::front()
{
	if (_size > 0)
	{
		return _data[0];
	}

	assert(("front() called on empty vector, condition:", 0 < _size));
}

template<class Type>
const Type& mvector<Type>::front() const
{
	if (_size > 0)
	{
		return _data[0];
	}

	assert(("front() called on empty vector, condition:", 0 < _size));
}

template<class Type>
Type& mvector<Type>::back()
{
	if (_size > 0)
	{
		return _data[_size - 1];
	}

	assert(("back() called on empty vector, condition:", 0 < _size));
}

template<class Type>
const Type& mvector<Type>::back() const
{
	if (_size > 0)
	{
		return _data[_size - 1];
	}

	assert(("back() called on empty vector, condition:", 0 < _size));
}

template<class Type>
Type* mvector<Type>::data()
{
	return _data;
}

template<class Type>
const Type*& mvector<Type>::data() const
{
	return _data;
}

template<class Type>
void mvector<Type>::push_back(const Type& item)
{
	if (_size < _capacity)
	{
		_data[_size] = item;
		_size++;
	}
	else
	{
		reserve(_size + 1);
		_data[_size] = item;
		_size++;
	}
}

template<class Type>
void mvector<Type>::pop_back()
{
	if (_size > 0)
	{
		_data[_size - 1] = Type();
		_size--;
	}

	assert(("pop_back() called on empty vector, condition:", 0 < _size));
}

template<class Type>
void mvector<Type>::erase(const iterator pos)
{
	for (unsigned int index = pos._index; index < _size - 1; index++)
	{
		_data[index] = _data[index + 1];
	}
	_size--;
}

template<class Type>
void mvector<Type>::erase(const iterator first, const iterator last)
{
	unsigned range = last._index - first._index;
	for (unsigned int index = first._index; index < _size - range; index++)
	{
		_data[index] = _data[index + range];
	}
	_size -= range;
	shink_to_fit();
}

template<class Type>
void mvector<Type>::insert(const iterator pos, const Type& val)
{
	reserve(_size + 1);
	_size++;
	for (unsigned int index = _size - 1; index > pos._index; index--)
	{
		_data[index] = _data[index - 1];
	}
	_data[pos._index] = val;
}

template<class Type>
void mvector<Type>::insert(const iterator pos, const iterator first, const iterator last)
{
	unsigned int range = last._index - first._index;
	reserve(_size + range);
	_size += range;
	for (unsigned int index = _size + range; index > pos._index; index--)
	{
		_data[index] = _data[index - range];
	}
	for (unsigned int index = pos._index, i = first._index; index < range + 1, i < last._index; index++, i++)
	{
		_data[index] = first.pVector->_data[i];
	}
}

template<class Type>
void mvector<Type>::swap(mvector<Type>& other)
{
	unsigned int size_temp = _size;
	_size = other._size;
	other._size = size_temp;

	unsigned int capacity_temp = _capacity;
	_capacity = other._capacity;
	other._capacity = capacity_temp;

	Type* buffer_temp = _data;
	_data = other._data;
	other._data = buffer_temp;
	buffer_temp = nullptr;
}

template<class Type>
void mvector<Type>::assign(iterator first, iterator last)
{
	_size = last._index - first._index;
	_capacity = getCapacity(_size);
	if (_data)
	{
		delete[] _data;
		_data = nullptr;
	}

	_data = new Type[_capacity];
	for (auto i = first, j = this->begin(); i != last; i++, j++)
	{
		*j = *i;
	}

	for (unsigned int i = _size; i < _capacity; i++)
	{
		_data[i] = Type();
	}
}

template<class Type>
void mvector<Type>::assign(const unsigned int size, const Type& value)
{
	_size = size;
	_capacity = getCapacity(size);

	if (_data)
	{
		delete[] _data;
		_data = nullptr;
	}

	_data = new Type[_capacity];

	for (unsigned int i = 0; i < _size; i++)
	{
		_data[i] = value;
	}

	for (unsigned int i = _size; i < _capacity; i++)
	{
		_data[i] = Type();
	}
}

template<class Type>
void mvector<Type>::clear()
{
	_size = 0;
	_capacity = 0;
	if (_data)
	{
		delete[] _data;
		_data = nullptr;
	}
}

template<class Type>
typename mvector<Type>::iterator mvector<Type>::begin()
{
	mvector<Type>::iterator iter(0, this);
	return iter;
}

template<class Type>
typename mvector<Type>::iterator mvector<Type>::end()
{
	mvector<Type>::iterator iter(_size, this);
	return iter;
}


//
//
//mvector_iterator class
//
//

template<class Type>
class mvector_iterator
{
private:
	mvector<Type>* pVector;
	unsigned int _index;

public:
	friend class mvector<Type>;
	mvector_iterator();
	mvector_iterator(const unsigned int index, mvector<Type>* vector);

	mvector_iterator& operator++();
	mvector_iterator operator++(int);
	mvector_iterator& operator--();
	mvector_iterator operator--(int);

	Type& operator*();
	const Type& operator*() const;

	Type* operator->();
	const Type* operator->() const;

	mvector_iterator& operator+=(const unsigned int n);
	mvector_iterator operator+(const unsigned int n);
	mvector_iterator& operator-=(const unsigned int n);
	mvector_iterator operator-(const unsigned int n);

	bool operator==(const mvector_iterator<Type> right);
	bool operator!=(const mvector_iterator<Type> right);
	bool operator<(const mvector_iterator<Type> right);
	bool operator<=(const mvector_iterator<Type> right);
	bool operator>(const mvector_iterator<Type> right);
	bool operator>=(const mvector_iterator<Type> right);
};

template<class Type>
mvector_iterator<Type>::mvector_iterator()
	:_index(0),
	pVector(nullptr)
{
}

template<class Type>
mvector_iterator<Type>::mvector_iterator(const unsigned int index, mvector<Type>* vector)
	:_index(index),
	pVector(vector)
{
}

template<class Type>
mvector_iterator<Type>& mvector_iterator<Type>::operator++()
{
	if (_index >= pVector->size())
	{
		assert(("out of range iterator: condition: ", _index > pVector->size()));
	}
	++(this->_index);
	return *this;
}

template<class Type>
mvector_iterator<Type> mvector_iterator<Type>::operator++(int)
{
	if (_index >= pVector->size())
	{
		assert(("out of range iterator: condition: ", _index > pVector->size()));
	}
	mvector_iterator<Type> temp = *this;
	(this->_index)++;
	return temp;
}

template<class Type>
mvector_iterator<Type>& mvector_iterator<Type>::operator--()
{
	if (_index == 0)
	{
		assert(("out of range iterator : condition: ", _index > 0));
	}
	--(this->_index);
	return *this;
}

template<class Type>
mvector_iterator<Type> mvector_iterator<Type>::operator--(int)
{
	if (_index == 0)
	{
		assert(("out of range iterator: condition: ", _index > 0));
	}
	mvector_iterator<Type> temp = *this;
	(this->_index)--;
	return temp;
}

template<class Type>
Type& mvector_iterator<Type>::operator*()
{
	return pVector->operator[](_index);
}

template<class Type>
const Type& mvector_iterator<Type>::operator*() const
{
	return pVector->operator[](_index);
}

template<class Type>
Type* mvector_iterator<Type>::operator->()
{
	Type* val = &pVector->data() + _index;
	return val;
}

template<class Type>
const Type* mvector_iterator<Type>::operator->() const
{
	const Type* val = &pVector->data() + _index;
	return val;
}

template<class Type>
mvector_iterator<Type>& mvector_iterator<Type>::operator+=(const unsigned int n)
{
	if (_index + n >= pVector->size())
	{
		assert(("cannot seek vector iterator after end, condition:", _index + n < pVector->size()));
	}
	(this->_index) += n;
	return *this;
}

template<class Type>
mvector_iterator<Type> mvector_iterator<Type>::operator+(const unsigned int n)
{
	if (_index + n >= pVector->size())
	{
		assert(("cannot seek vector iterator after end, condition:", _index + n < pVector->size()));
	}
	mvector_iterator<Type> temp = *this;
	(temp._index) += n;
	return temp;
}

template<class Type>
mvector_iterator<Type>& mvector_iterator<Type>::operator-=(const unsigned int n)
{
	if (static_cast<int>(_index) - static_cast<int>(n) < 0)
	{
		assert(("cannot seek vector iterator before begin, condition:", static_cast<int>(_index) - static_cast<int>(n) >= 0));
	}
	(this->_index) -= n;
	return *this;
}

template<class Type>
mvector_iterator<Type> mvector_iterator<Type>::operator-(const unsigned int n)
{
	if (static_cast<int>(_index) - static_cast<int>(n))
	{
		assert(("cannot seek vector iterator before begin, condition:", static_cast<int>(_index) - static_cast<int>(n) >= 0));
	}
	mvector_iterator<Type> temp = *this;
	(temp._index) -= n;
	return temp;
}

template<class Type>
bool mvector_iterator<Type>::operator==(const mvector_iterator<Type> right)
{
	if (this->pVector != right.pVector)
	{
		assert(("vector iterators incompatible, condition:", this->pVector == right.pVector));
	}

	if (this->_index == right._index)
	{
		return true;
	}

	return false;
}

template<class Type>
bool mvector_iterator<Type>::operator!=(const mvector_iterator<Type> right)
{
	if (*this == right)
	{
		return false;
	}

	return true;
}

template<class Type>
bool mvector_iterator<Type>::operator<(const mvector_iterator<Type> right)
{
	if (this->pVector != right.pVector)
	{
		assert(("vector iterators incompatible, condition:", this->pVector == right.pVector));
	}

	if (this->_index < right._index)
	{
		return true;
	}

	return false;
}

template<class Type>
bool mvector_iterator<Type>::operator<=(const mvector_iterator<Type> right)
{
	if (*this > right)
	{
		return false;
	}

	return true;
}

template<class Type>
bool mvector_iterator<Type>::operator>(const mvector_iterator<Type> right)
{
	if (this->pVector != right.pVector)
	{
		assert(("vector iterators incompatible, condition:", this->pVector == right.pVector));
	}

	if (this->_index > right._index)
	{
		return true;
	}

	return false;
}

template<class Type>
bool mvector_iterator<Type>::operator>=(const mvector_iterator<Type> right)
{
	if (*this < right)
	{
		return false;
	}

	return true;
}

