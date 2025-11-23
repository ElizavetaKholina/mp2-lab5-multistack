#pragma once

#include <iostream>
#include <algorithm>
using namespace std;

template<class T>
class TStack
{
protected:
	T** data;
	bool isNew;
	int size;
	int top;
public:
	TStack();
	TStack(int size_);
	TStack(T** data_, int size_);
	TStack(const TStack& s);
	TStack(TStack&& s);
	~TStack();
	
	void Push(T elem);
	T Pop();

	int GetSize();
	int GetCount();

	bool IsFull();
	bool IsStackEmpty();

	void ReSize(int newsize);
	void SetData(T** data_, int size_);

	TStack& operator=(const TStack<T>& s);
	TStack& operator=(TStack<T>&& s);

	bool operator==(const TStack<T>& s);
	bool operator!=(const TStack<T>& s);

	template<class T>
	friend istream& operator>>(istream& istr, TStack<T>& s);

	template<class T>
	friend ostream& operator<<(ostream& ostr, const TStack<T>& s);
};

template<class T>
inline TStack<T>::TStack()
{
	size = 0;
	data = nullptr;
	top = 0;
	isNew = true;
}

template<class T>
inline TStack<T>::TStack(int size_) : TStack<T>::TStack()
{
	if (size_ < 0)
	{
		throw "size should be >= 0";
	}
	else if (size_ > 0)
	{
		size = size_;
	    data = new T * [size];
		for (int i = 0; i < size; i++)
		{
			data[i] = nullptr;
		}
	}	
}

template<class T>
inline TStack<T>::TStack(T** data_, int size_) : TStack<T>::TStack()
{
	if (size_ < 0)
	{
		throw "size should be >= 0";
	}
	else if (size_ > 0)
	{
		size = size_;
		data = data_;
		isNew = false;
		for (top = 0; top < size && data[top] != nullptr; top++);
	}
}

template<class T>
inline TStack<T>::~TStack()
{
	if (isNew)
	{
		if (data != nullptr)
		{
			for (int i = 0; i < size; i++)
			{
				if (data[i] != nullptr)
				{
					delete data[i];
				}
			}
			delete[] data;
		}
	}
	data = nullptr;
	size = 0;
	top = 0;
}

template<class T>
inline TStack<T>::TStack(const TStack& s) : TStack<T>::TStack()
{
	if (s.size > 0)
	{
		size = s.size;
		top = s.top;
		data = new T * [size];

		for (int i = 0; i < size; i++)
		{
			if (i < top && s.data[i] != nullptr)
			{
				data[i] = new T(*(s.data[i]));
			}
			else
			{
				data[i] = nullptr;
			}
		}
	}
}

template<class T>
inline TStack<T>::TStack(TStack&& s)
{
	data = s.data;
	size = s.size;
	top = s.top;
	isNew = s.isNew;

	s.data = nullptr;
	s.size = 0;
	s.isNew = true;
	s.top = 0;
}

template<class T>
inline void TStack<T>::Push(T elem)
{
	if (IsFull())
	{
		throw "stack is full";
	}
	top++;
	data[top] = new T(elem);
}

template<class T>
inline T TStack<T>::Pop()
{
	if (IsStackEmpty())
	{
		throw "stack is empty";
	}
	top--;
	T p = *(data[top]);
	delete data[top];
	data[top] = nullptr;
	return p;
}

template<class T>
inline int TStack<T>::GetSize()
{
	return size;
}

template<class T>
inline int TStack<T>::GetCount()
{
	return top;
}

template<class T>
inline bool TStack<T>::IsFull()
{
	return top >= size;
}

template<class T>
inline bool TStack<T>::IsStackEmpty()
{
	return top == 0;
}

template<class T>
inline void TStack<T>::ReSize(int newsize)
{
	if (newsize < 0)
	{
		throw "newsize should be >= 0";
	}
	else if (newsize == 0)
	{
		if (isNew)
		{
			if (data != nullptr)
			{
				for (int i = 0; i < top; i++)
				{
					if (data[i] != nullptr)
					{
						delete data[i];
					}
				}
				delete[] data;
			}
		}
		data = nullptr;
		size = 0;
		top = 0;
		isNew = true;
	}
	else if (size == newsize)
	{
		return;
	}
	else
	{
		T** newData = new T * [newsize];
		int i = 0;
		for (; i < min(size, newsize); i++)
		{
			newData[i] = data[i];
		}
		if (isNew)
		{
			for (; i < size; i++)
			{
				if (data[i] != nullptr)
				{
					delete data[i];
				}
			}
			delete[] data;
		}
		data = newData;
		size = newsize;
		isNew = true;
		top = min(top, newsize);
	}
}

template<class T>
inline void TStack<T>::SetData(T** data_, int size_)
{
	if (size_ < 0)
	{
		throw "size should be >= 0";
	}
	else if (size_ == 0)
	{
		if (isNew)
		{
			if (data != nullptr)
			{
				for (int i = 0; i < size; i++)
				{
					if (data[i] != nullptr)
					{
						delete data[i];
					}
				}
				delete[] data;
			}
		}
		data = nullptr;
		size = 0;
		isNew = true;
		top = 0;
	}
	else if (size_ > 0)
	{
		if (isNew)
		{
			if (data != nullptr)
			{
				for (int i = 0; i < size; i++)
				{
					if (data[i] != nullptr)
					{
						delete data[i];
					}
				}
				delete[] data;
			}
		}
		data = nullptr;
		data = data_;
		size = size_;
		isNew = false;
		for (top = 0; top < size && data[top] != nullptr; top++);
	}
}

template<class T>
inline TStack<T>& TStack<T>::operator=(const TStack<T>& s)
{
	if (this != &s)
	{
		if (isNew)
		{
			if (data != nullptr)
			{
				for (int i = 0; i < size; i++)
				{
					if (data[i] != nullptr)
					{
						delete data[i];
					}
				}
				delete[] data;
			}
		}
		size = s.size;
		top = s.top;
		isNew = true;

		if (size > 0)
		{
			data = new T * [size];
			for (int i = 0; i < size; i++)
			{
				if (i < top && s.data[i] != nullptr)
				{
					data[i] = new T(*(s.data[i]));
				}
				else
				{
					data[i] = nullptr;
				}
			}
		}
		else
		{
			data = nullptr;
		}
	}
	return *this;
}

template<class T>
inline TStack<T>& TStack<T>::operator=(TStack<T>&& s)
{
	if (this != &s)
	{
		if (isNew)
		{
			if (data != nullptr)
			{
				for (int i = 0; i < size; i++)
				{
					if (data[i] != nullptr)
					{
						delete data[i];
					}
				}
				delete[] data;
				data = nullptr;
			}
		}
		data = s.data;
		size = s.size;
		top = s.top;
		isNew = s.isNew;

		s.data = nullptr;
		s.size = 0;
		s.isNew = true;
		s.top = 0;
	}
	return *this;
}

template<class T>
inline bool TStack<T>::operator==(const TStack& s)
{
	if (top != s.top)
	{
		return false;
	}

	for (int i = 0; i < top; i++) 
	{
		if (*(data[i]) != *(s.data[i]))
		{
			return false;
		}
	}
	return true;
}

template<class T>
inline bool TStack<T>::operator!=(const TStack& s)
{
	return !(*this == s);
}

template<class T>
ostream& operator<<(ostream& ostr, const TStack<T>& s)
{
	for (int i = 0; i < s.size; i++) 
	{
		if (s.data[i] != nullptr)
		{
			ostr << *(s.data[i]) << " ";
		}
		else if (s.data[i] == nullptr)
		{
			ostr << "n ";
		}
	}
	return ostr;
}

template<class T>
istream& operator>>(istream& istr, TStack<T>& s)
{
	for (int i = 0; i < s.size; i++)
	{
		istr >> s.Push(T elem);
	}
	return istr;
}