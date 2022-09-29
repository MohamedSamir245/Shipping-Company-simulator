#pragma once
#include "Node.h"
#include<iostream>
#include"Cargo.h"
#include"NormalCargo.h"
#include"SpecialCargo.h"
#include"VipCargo.h"
using namespace std;


template <typename T>
class Queue
{
private:

	Node<T>* backPtr;
	Node<T>* frontPtr;
	int count;

public:
	Queue ( );
	bool isEmpty ( ) const;
	bool enqueue ( const T& newEntry );
	bool dequeue ( T& frntEntry );
	bool peek ( T& frntEntry )  const;
	void Print();
	~Queue ( );

	//copy constructor
	Queue ( const Queue<T>& LQ );
	int getCount()const;

	void print() const;

};


template <typename T>
Queue<T>::Queue ( )
{
	backPtr = nullptr;
	frontPtr = nullptr;
	count = 0;

}

template <typename T>
bool Queue<T>::isEmpty ( ) const
{
	return (frontPtr == nullptr);
}


template <typename T>
bool Queue<T>::enqueue ( const T& newEntry )
{
	Node<T>* newNodePtr = new Node<T> ( newEntry );
	if ( isEmpty ( ) )
		frontPtr = newNodePtr;
	else
		backPtr->setNext ( newNodePtr );

	backPtr = newNodePtr;
	count++;

	return true;
}

template <typename T>
bool Queue<T>::dequeue ( T& frntEntry )
{
	if ( isEmpty ( ) )
		return false;

	Node<T>* nodeToDeletePtr = frontPtr;
	frntEntry = frontPtr->getItem ( );
	frontPtr = frontPtr->getNext ( );
	if ( nodeToDeletePtr == backPtr )
		backPtr = nullptr;

	delete nodeToDeletePtr;
	count--;

	return true;

}

template <typename T>
bool Queue<T>::peek ( T& frntEntry ) const
{
	if ( isEmpty ( ) )
		return false;

	frntEntry = frontPtr->getItem ( );
	return true;

}

template <typename T>
void Queue<T>::Print()
{
	if (frontPtr == nullptr)
		return;
	Node<T>* curr = frontPtr;
	while (curr)
	{
		cout << curr->getItem();
		if (curr->getNext() != nullptr)
			cout << ",";
		curr = curr->getNext();
	}
	return;
}

template <typename T>
Queue<T>::~Queue ( )
{
	T temp;

	while ( dequeue ( temp ) );
}


template <typename T>
Queue<T>::Queue ( const Queue<T>& LQ )
{
	Node<T>* NodePtr = LQ.frontPtr;
	if ( !NodePtr ) 
	{
		frontPtr = backPtr = nullptr;
		return;
	}

	
	Node<T>* ptr = new Node<T> ( NodePtr->getItem ( ) );
	frontPtr = backPtr = ptr;
	NodePtr = NodePtr->getNext ( );

	while ( NodePtr )
	{
		Node<T>* ptr = new Node<T> ( NodePtr->getItem ( ) );
		backPtr->setNext ( ptr );
		backPtr = ptr;
		NodePtr = NodePtr->getNext ( );
	}
}

template <typename T>
int Queue<T>::getCount() const
{
	return count;
}

template <typename T>
void Queue<T>::print() const
{
	if (this->isEmpty())
		return;
	Node<T>* curr = frontPtr;
	while (curr)
	{
		cout << curr->getItem();
		if (curr->getNext())
			cout << ",";
		curr = curr->getNext();
	}
	return;
}
template<>
inline void Queue<Cargo*>::print() const
{
	if (this->isEmpty())
		return;
	Node<Cargo*>* curr = frontPtr;
	while (curr)
	{
		cout << curr->getItem()->GetID();
		if (curr->getNext())
			cout << ",";
		curr = curr->getNext();
	}
	return;
}
template<>
inline void Queue<NormalCargo*>::print() const
{
	if (this->isEmpty())
		return;
	Node<NormalCargo*>* curr = frontPtr;
	while (curr)
	{
		cout << curr->getItem()->GetID();
		if (curr->getNext())
			cout << ",";
		curr = curr->getNext();
	}
	return;
}
template<>
inline void Queue<SpecialCargo*>::print() const
{
	if (this->isEmpty())
		return;
	Node<SpecialCargo*>* curr = frontPtr;
	while (curr)
	{
		cout << curr->getItem()->GetID();
		if (curr->getNext())
			cout << ",";
		curr = curr->getNext();
	}
	return;
}
template<>
inline void Queue<VipCargo*>::print() const
{
	if (this->isEmpty())
		return;
	Node<VipCargo*>* curr = frontPtr;
	while (curr)
	{
		cout << curr->getItem()->GetID();
		if (curr->getNext())
			cout << ",";
		curr = curr->getNext();
	}
	return;
}