#include "Stack.h"
#include "MultiStack.h"

int main()
{
	TStack<int> A;
	TStack<int> B(3);
	B.Push(11);
	TStack<int> C = B;
	int** data = new int* [11];
	data[0] = new int(5);
	data[1] = new int(17);
	for (int i = 2; i < 11; i++)
	{
		data[i] = nullptr;
	}
	TStack<int> D(data, 5);
	TStack<int> E(&(data[5]), 6);

	int k = D.Pop();

	/*TMultiStack<char> mStack(16, 3);

	mStack.Push('a', 1);
	mStack.Push('b', 2);
	mStack.Push('c', 2);
	char res = mStack.Pop(2);
	mStack.Push('d', 2);
	mStack.Push('e', 1);
	mStack.Push('f', 1);
	mStack.Push('j', 1);
	mStack.Push('h', 1);
	mStack.Push('g', 2);
	mStack.Push('q', 1);*/

	TMultiStack<char> mStack(40, 10);

	mStack.Push('t', 0);
	mStack.Push('q', 1);
	mStack.Push('w', 1);
	mStack.Push('e', 1);
	mStack.Push('r', 1);
	mStack.Push('y', 2);
	mStack.Push('u', 2);
	mStack.Push('i', 2);
	mStack.Push('o', 3);
	mStack.Push('p', 3);
	mStack.Push('a', 4);
	mStack.Push('s', 5);
	mStack.Push('d', 6);
	mStack.Push('f', 7);
	mStack.Push('g', 7);
	mStack.Push('h', 7);
	mStack.Push('j', 8);
	mStack.Push('k', 8);
	mStack.Push('l', 9);
	mStack.Push('z', 9);
	mStack.Push('x', 1);

	return 0;
}