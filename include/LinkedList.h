#pragma once
#include <iostream>
#include "LLNode.h"

template <class T>
class LinkedList
{
protected:
	LLNode<T>* head;
	LLNode<T>* tail;

public:
	//lista vacia
	LinkedList() : head(nullptr), tail(nullptr) {}
	LinkedList(LLNode<T> *_hd) : head(_hd), tail(_hd) {};

	//Imprimir el contenido
	//void PrintElements();

	//agrega elemento al final de la lista ligada
	LLNode<T>* AddNode(T* _data)
	{
		LLNode<T>* newNode = new LLNode<T>(_data);

		if (!head)
		{
			head = tail = newNode;
		}
		else
		{
			tail->next = newNode;
			newNode->prev = tail;
			tail = newNode;
		}

		return newNode;
	}

	//Remover el ultimo nodo
	void RemoveLastNode()
	{
		if (!head)
			return;

		if (head == tail)
		{
			delete head;
			head = tail = nullptr;
		}
		else 
		{

			LLNode<T>* prevNode = tail-> prev;
			delete tail;
			tail = prevNode;
			tail->next = nullptr;
		}
	}

};

