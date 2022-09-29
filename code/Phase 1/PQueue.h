#pragma once
#include "PNode.h"
#include"Time.h"
#include <iostream>
#include"Cargo.h"
#include"NormalCargo.h"
#include"SpecialCargo.h"
#include"VipCargo.h"
using namespace std;


template <typename T1, typename T2>
class PQueue
{
private:
	bool desceing_order;
	PNode<T1, T2>* backPtr;
	PNode<T1, T2>* frontPtr;
	int counter;

public:

	PQueue();
	bool isEmpty() const;
	bool push(const T1& newEntry,  T2 Entry_priority);
	bool pop(T1& frntEntry);
	void setPriorityOrder(bool Des_order);
	bool peek(T1& frntEntry)  const;
	int getcounter() const;
	~PQueue();
	void print() const;
};


template <typename T1, typename T2>
PQueue<T1, T2>::PQueue()
{
	backPtr = nullptr;
	frontPtr = nullptr;
	desceing_order = true;
	counter = 0;
}

template <typename T1, typename T2>
bool PQueue<T1, T2>::isEmpty() const
{
	return (frontPtr == nullptr);
}


template <typename T1, typename T2>
bool PQueue<T1, T2>::push(const T1& newEntry,  T2 Entry_priority)
{
	PNode<T1, T2>* temp = new PNode<T1, T2>(newEntry, Entry_priority);
	if (isEmpty())
	{
		frontPtr = temp;
		backPtr = temp;
		counter++;
		return true;
	}
	if (desceing_order)
	{
		if (Entry_priority > frontPtr->getPriority())
		{
			temp->setNext(frontPtr);
			frontPtr = temp;
			counter++;
			return true;
		}
		else
		{
			PNode<T1, T2>* curr = frontPtr;
			while (curr->getNext() != nullptr)
			{
				if (Entry_priority > curr->getNext()->getPriority())
				{
					temp->setNext(curr->getNext());
					curr->setNext(temp);
					counter++;
					return true;
				}
				curr = curr->getNext();
			}
			curr->setNext(temp);
			temp->setNext(nullptr);
			backPtr = temp;
			counter++;
			return true;
		}
	}
	else
	{
		if (Entry_priority < frontPtr->getPriority())
		{
			temp->setNext(frontPtr);
			frontPtr = temp;
			counter++;
			return true;
		}
		else
		{
			PNode<T1, T2>* curr = frontPtr;
			while (curr->getNext() != nullptr)
			{
				if (Entry_priority < curr->getNext()->getPriority())
				{
					temp->setNext(curr->getNext());
					curr->setNext(temp);
					counter++;
					return true;
				}
				curr = curr->getNext();
			}
			curr->setNext(temp);
			temp->setNext(nullptr);
			backPtr = temp;
			counter++;
			return true;
		}
	}
}

template <typename T1, typename T2>
bool PQueue<T1, T2>::pop(T1& frntEntry)
{
	if (isEmpty())
		return false;

	PNode<T1, T2>* PNodeToDeletePtr = frontPtr;
	frntEntry = frontPtr->getItem();
	frontPtr = frontPtr->getNext();
	if (PNodeToDeletePtr == backPtr)
		backPtr = nullptr;

	delete PNodeToDeletePtr;
	counter--;
	return true;

}

template <typename T1, typename T2>
void PQueue<T1, T2>::setPriorityOrder(bool Des_order)
{
	desceing_order = Des_order;
}

template <typename T1, typename T2>
bool PQueue<T1, T2>::peek(T1& frntEntry) const
{
	if (isEmpty())
		return false;

	frntEntry = frontPtr->getItem();
	return true;

}

template <typename T1, typename T2>
int PQueue<T1, T2>::getcounter() const
{
	return counter;
}

template <typename T1, typename T2>
PQueue<T1, T2>::~PQueue()
{
	T1 temp;

	while (pop(temp));
}

template <typename T1, typename T2>
void PQueue<T1, T2>::print() const
{
	if (this->isEmpty())
		return;
	PNode<T1, T2>* curr = frontPtr;
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
inline void PQueue<Cargo*, Time>::print() const
{
	if (this->isEmpty())
		return;
	PNode<Cargo*, Time>* curr = frontPtr;
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
inline void PQueue<NormalCargo*, Time>::print() const
{
	if (this->isEmpty())
		return;
	PNode<NormalCargo*, Time>* curr = frontPtr;
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
inline void PQueue<SpecialCargo*, Time>::print() const
{
	if (this->isEmpty())
		return;
	PNode<SpecialCargo*, Time>* curr = frontPtr;
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
inline void PQueue<VipCargo*, Time>::print() const
{
	if (this->isEmpty())
		return;
	PNode<VipCargo*, Time>* curr = frontPtr;
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
inline void PQueue<VipCargo*, int>::print() const
{
	if (this->isEmpty())
		return;
	PNode<VipCargo*, int>* curr = frontPtr;
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
inline void PQueue<Cargo*, float>::print() const
{
	if (this->isEmpty())
		return;
	PNode<Cargo*, float>* curr = frontPtr;
	while (curr)
	{
		cout << curr->getItem()->GetID();
		if (curr->getNext())
			cout << ",";
		curr = curr->getNext();
	}
	return;
}