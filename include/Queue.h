#pragma once

template<typename T>
class Queue
{
private:
	T* data;
	size_t front;
	size_t rear;
	size_t maxsize;

public:
	//constructor
	Queue(size_t _size)
	{
		maxsize = _size;
		front = 0;
		rear = 0;

		data = new T[maxsize];
	}
	//destructor
	~Queue()
	{
		delete[] data;
	}

	bool isEmpty()
	{
		return front == rear;
	}

	size_t size()
	{
		return rear - front;
	}

	//agregar elemento a la cola
	void enqueue(T item)
	{
		if (size() == maxsize)
		{
			std::cout << "la cola esta llena, queue overflow!!" << std::endl;
			return;
		}
		data[++rear] = item;
	}

	//sacar elemento de la cola
	T dequeue()
	{
		if (isEmpty())
		{
			std::cout << "la cola esta vacia" << std::endl;
			return T();
		}


		T temp = data[front];
		for (size_t i = front; i<rear; i++)
		{
			data[i] = data[i + 1];
		}

		return temp;
	}

	//ver el primer elemento de la cola
	T* peek()
	{
		if (isEmpty())
		{
			std::cout << "la cola esta vacia" << std::endl;
			return nullptr;
		}
		return &data[front];
	}

	void debugPrintContents()
	{
		std::cout << "Cola: ";
		for (size_t i = 0; i <= maxsize; i++)
		{
			std::cout << data[i] << " ";
		}
		std::cout << "]" << std::endl;
	}

};

