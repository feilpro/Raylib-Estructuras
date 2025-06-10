#pragma once
#include <iostream>

template <typename T>
class Stack
{
private:
	T* data;
	size_t top;

public:
	size_t maxsize;

	//constructor
	Stack(size_t _maxsize)
	{
		maxsize = _maxsize;
		data = new T[maxsize];
		top = 0;
	}

	//destructor
	~Stack()
	{
		delete[] data;
	}


	void push(T item); //push
	T pop(); //Nos regresa el elemento
	T* peek();
	bool isEmpty();
	bool size();

};

template<typename T>
inline void Stack<T>::push(T item)
{
	top++;
	if (top > maxsize)
	{
		std::cout << "Stack overflow!!!" << std::endl;
	}
	else
	{
		data[top - 1] = item;
	}
}

template<typename T>
inline T Stack<T>::pop()
{
	if (top > 0)
	{
		top--;
		return data[top];
	}
	//warning
	else
	{
		std::cout << "stack esta vacio" << std::endl;
		//return nullptr;
		return T();
	}
}

template<typename T>
inline T* Stack<T>::peek()
{
	if (top > 0)
	{
		return &data[top - 1];
	}
	else
	{
		return nullptr;
	}
}

template<typename T>
inline bool Stack<T>::isEmpty()
{
	//si top es cero, quiere decir que no hay elementos en la pila
	return top == 0;
}

template<typename T>
inline bool Stack<T>::size()
{
	return top;
}
