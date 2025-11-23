#include <iostream>
#include "Stack.h"
using namespace std;

template<class T>
class TMultiStack
{
protected:
	T** data;
	int size;
	TStack<T>* stacks;
	int stackCount;
	int* stackStarts;
	void Repack(int curStack);
public:
	TMultiStack();
	TMultiStack(int size_, int stackCount_);
	TMultiStack(const TMultiStack& m);
	TMultiStack(TMultiStack&& m);
	~TMultiStack();	
	
	int GetSize();
	int GetStackCount();
	void ReSize(int newsize);

	void Push(T elem, int i);
	T Pop(int i);

	bool IsFull(int i);
	bool IsStackEmpty(int i);
	
	TStack<T>& operator [](int i);

	TMultiStack& operator=(const TMultiStack<T>& m);
	TMultiStack& operator=(TMultiStack<T>&& m);

	bool operator==(const TMultiStack<T>& m);
	bool operator!=(const TMultiStack<T>& m);

	template<class T>
	friend istream& operator>>(istream& istr, TMultiStack<T>& m);

	template<class T>
	friend ostream& operator<<(ostream& ostr, const TMultiStack<T>& m);
};

template<class T>
inline void TMultiStack<T>::Repack(int curStack)
{
	int* newStart = new int[stackCount];
	int* newSizes = new int[stackCount];
	int filled = 0;

	for (int i = 0; i < stackCount; i++)
	{
		filled += stacks[i].GetCount();
	}

	int freeCells = size - filled;
	int ns = int(freeCells / stackCount);
	int tail = freeCells - ns * stackCount;

	newStart[0] = 0;
	newSizes[0] = stacks[0].GetCount() + ns;

	for (int i = 1; i < stackCount; i++)
	{
		newSizes[i] = stacks[i].GetCount() + ns;
		if (i == curStack)
		{
			newSizes[i] += tail;
		}
		newStart[i] = newStart[i - 1] + newSizes[i - 1];
	}

	for (int i = 1; i < stackCount; i++)
	{
		if (newStart[i] == stackStarts[i])
		{
			continue;
		}
		else if (newStart[i] < stackStarts[i])
		{
			int n, j = 0, k = 0;
			for (n = 0, j = stackStarts[i], k = newStart[i]; n < stacks[i].GetCount(); j++, k++, n++)
			{
				data[k] = data[j];
			}
			for (; k < stackStarts[i] + stacks[i].GetSize(); k++)
			{
				data[k] = nullptr;
			}
		}
		else if (newStart[i] > stackStarts[i])
		{
			int q = i;
			while (newStart[q] > stackStarts[q])
			{
				q++;
			}
			for (int w = q - 1; w >= i; w--)
			{
				int n = 0, j = 0, k = 0;
				for (j = stackStarts[w] + stacks[w].GetCount() - 1, k = newStart[w] + stacks[w].GetCount() - 1, n = stacks[w].GetCount() - 1; n >= 0; j--, k--, n--)
				{
					data[k] = data[j];
				}
				for (; k >= stackStarts[w]; k--)
				{
					data[k] = nullptr;
				}
			}
			i = q - 1;
		}
	}

	for (int i = 0; i < stackCount; i++)
	{
		stacks[i].SetData(&(data[newStart[i]]), newSizes[i]);
	}
}

template<class T>
inline TMultiStack<T>::TMultiStack()
{
	data = nullptr;
	size = 0;
	stacks = nullptr;
	stackCount = 0;
	stackStarts = nullptr;
}

template<class T>
inline TMultiStack<T>::TMultiStack(int size_, int stackCount_)
{
	if (size_ < 0 || stackCount_ < 0)
	{
		throw "size_ < 0 || stackCount_ < 0";
	}
	else if (size_ == 0 || stackCount == 0)
	{
		data = nullptr;
		size = 0;
		stacks = nullptr;
		stackCount = 0;
		stackStarts = nullptr;
	}
	else
	{
		size = size_;
		stackCount = stackCount_;
		data = new T * [size];
		for (int j = 0; j < size; j++)
		{
			data[j] = nullptr;
		}
		stackStarts = new int[stackCount];
		stackStarts[0] = 0;
		int stackSize = int(size / stackCount);
		for (int i = 1; i < stackCount; i++)
		{
			stackStarts[i] = stackStarts[i - 1] + stackSize;
		}
		stacks = new TStack<T>[stackCount];
		for (int i = 0; i < stackCount - 1; i++)
		{
			stacks[i].SetData(data + stackStarts[i], stackSize);
		}
		stacks[stackCount - 1].SetData(data + stackStarts[stackCount - 1], stackSize + (size - stackCount * stackSize));
	}
}

template<class T>
inline TMultiStack<T>::TMultiStack(const TMultiStack& m)
{
	if (m.size == 0 || m.stackCount == 0)
	{
		data = nullptr;
		size = 0;
		stacks = nullptr;
		stackCount = 0;
		stackStarts = nullptr;
	}
	else if (m.size < 0 || m.stackCount < 0)
	{
		throw "m.size < 0 || m.stackCount < 0";
	}
	else
	{
		size = m.size;
		stackCount = m.stackCount;
		data = new T * [size];
		for (int j = 0; j < size; j++)
		{
			data[j] = new T(*(m.data[j]));
		}
		stackStarts = new int[stackCount];
		for (int i = 0; i < stackCount; i++)
		{
			stackStarts[i] = m.stackStarts[i];
		}
		stacks = new TStack<T>[stackCount];
		for (int i = 0; i < stackCount - 1; i++)
		{
			stacks[i].SetData(data + stackStarts[i], stackStarts[i + 1] - stackStarts[i]);
		}
		stacks[stackCount - 1].SetData(data + stackStarts[stackCount - 1], size - stackStarts[stackCount - 1]);
		}
}

template<class T>
inline TMultiStack<T>::TMultiStack(TMultiStack&& m)
{
	data = m.data;
	size = m.size;
	stacks = m.stacks;
	stackCount = m.stackCount;
	stackStarts = m.stackStarts;

	m.data = nullptr;;
	m.size = 0;
	m.stacks = nullptr;
	m.stackCount = 0;
	m.stackStarts = nullptr;

}

template<class T>
inline TMultiStack<T>::~TMultiStack()
{
	if (data != nullptr)
	{
		for (int j = 0; j < size; j++)
		{
			delete data[j];
		}
		delete[] data;
		delete[] stacks;
		delete[] stackStarts;

		data = nullptr;
		size = 0;
		stacks = nullptr;
		stackCount = 0;
		stackStarts = nullptr;
	}
}

template<class T>
inline void TMultiStack<T>::Push(T elem, int i)
{
	if (i < 0 || i >= stackCount)
	{
		throw "i < 0 || i >= stackCount";
	}
	if (stacks[i].IsFull())
	{
		Repack(i);
	}
	stacks[i].Push(elem);
}

template<class T>
inline T TMultiStack<T>::Pop(int i)
{
	if (i < 0 || i >= stackCount)
	{
		throw "-1";
	}
	if (stacks[i].IsStackEmpty())
	{
		throw "stack is empty";
	}
	return stacks[i].Pop();
}

template<class T>
inline bool TMultiStack<T>::IsFull(int i) 
{
	if (i < 0 || i >= stackCount)
	{
		throw "i < 0 || i >= stackCount";
	}
	return stacks[i].IsFull();
}

template<class T>
inline bool TMultiStack<T>::IsStackEmpty(int i)
{
	if (i < 0 || i >= stackCount)
	{
		throw "i < 0 || i >= stackCount";
	}
	return stacks[i].IsStackEmpty();
}

template<class T>
inline TStack<T>& TMultiStack<T>::operator[](int i)
{
	if (i < 0 || i >= stackCount)
	{
		throw "i < 0 || i >= stackCount";
	}
	return stacks[i];
}

template<class T>
inline int TMultiStack<T>::GetSize()
{
	return size;
}

template<class T>
inline int TMultiStack<T>::GetStackCount()
{
	return stackCount;
}

template<class T>
inline TMultiStack<T>& TMultiStack<T>::operator=(const TMultiStack<T>& m)
{
	if (this != &m)
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
		if (stacks != nullptr)
		{
			delete[] stacks;
		}
		if (stackStarts != nullptr)
		{
			delete[] stackStarts;
		}

		size = m.size;
		stackCount = m.stackCount;

		data = new T * [size];
		for (int i = 0; i < size; i++)
		{
			if (m.data[i] != nullptr)
			{
				data[i] = new T(*(m.data[i]));
			}
			else
			{
				data[i] = nullptr;
			}
		}

		stackStarts = new int[stackCount];
		for (int i = 0; i < stackCount; i++)
		{
			stackStarts[i] = m.stackStarts[i];
		}

		stacks = new TStack<T>[stackCount];
		for (int i = 0; i < stackCount; i++)
		{
			stacks[i] = m.stacks[i];
		}
	}
	return *this;
}

template<class T>
inline TMultiStack<T>& TMultiStack<T>::operator=(TMultiStack<T>&& m)
{
	if (this != &m)
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
		if (stacks != nullptr)
		{
			delete[] stacks;
		}
		if (stackStarts != nullptr)
		{
			delete[] stackStarts;
		}

		data = m.data;
		size = m.size;
		stacks = m.stacks;
		stackCount = m.stackCount;
		stackStarts = m.stackStarts;

		m.data = nullptr;
		m.size = 0;
		m.stacks = nullptr;
		m.stackCount = 0;
		m.stackStarts = nullptr;
	}
	return *this;
}

template<class T>
inline bool TMultiStack<T>::operator==(const TMultiStack<T>& m)
{
	if (size != m.size)
	{
		return false;
	}
	if (stackCount != m.stackCount)
	{
		return false;
	}

	for (int i = 0; i < stackCount; i++)
	{
		if (stacks[i] != m.stacks[i])
		{
			return false;
		}
	}
	return true;
}

template<class T>
inline bool TMultiStack<T>::operator!=(const TMultiStack<T>& m)
{
	return !(*this == m);
}

template<class T>
inline istream& operator>>(istream& istr, TMultiStack<T>& m)
{
	return istr;
}

template<class T>
inline ostream& operator<<(ostream& ostr, const TMultiStack<T>& m)
{
	for (int i = 0; i < m.stackCount; i++)
	{
		ostr << "Stack N" << i << ": " << m.stacks[i] << endl;
	}
	return ostr;
}