#pragma once
#include "Node.h"
#include<iostream>
#include"NormalCargo.h"
#include"SpecialCargo.h"
#include"VipCargo.h"

using namespace std;



template<typename T>
class List
{
	Node<T>* HeadPtr;
	int Count;
public:

	List()
	{
		HeadPtr = nullptr;
		Count = 0;
	}

	int GetCount()
	{
		return Count;
	}

	bool IsEmpty()
	{
		if (Count == 0)
			return true;
		return false;
	}

	bool Add( T newvalue)
	{
		Node<T>* temp = new Node<T>;
		temp->setItem(newvalue);

		if (HeadPtr == nullptr)
		{
			HeadPtr = temp;
			Count++;
			return true;
		}
		if (newvalue < HeadPtr->getItem())
		{
			temp->setNext(HeadPtr);
			HeadPtr = temp;
			Count++;
			return true;
		}
		else
		{
			Node<T>* curr = HeadPtr;
			while (curr->getNext() != nullptr)
			{
				if (newvalue < curr->getNext()->getItem())
				{
					temp->setNext(curr->getNext());
					curr->setNext(temp);
					Count++;
					return true;
				}
				curr = curr->getNext();
			}
			curr->setNext(temp);
			temp->setNext(nullptr);
			Count++;
			return true;

		}
	}
	bool Remove(const T& deletedvalue)
	{
		if (HeadPtr->getItem() == deletedvalue)
		{
			Node<T>* temp = HeadPtr;
			HeadPtr = HeadPtr->getNext();
			delete temp;
			Count--;
			return true;
		}

		Node<T>* curr = HeadPtr;
		while (curr->getNext() != nullptr)
		{
			if (curr->getNext()->getItem() == deletedvalue)
			{
				Node<T>* temp = curr->getNext();
				if (curr->getNext()->getNext() == nullptr)
				{
					curr->setNext(nullptr);
					delete temp;
					Count--;
					return true;
				}
				else
				{
					curr->setNext(curr->getNext()->getNext());
					delete temp;
					Count--;
					return true;
				}


			}
			curr = curr->getNext();
		}
		return false;
	}

	bool RemoveFirst(T &deleted)
	{
		if (HeadPtr == nullptr)
			return false;
		else
		{
			deleted = HeadPtr->getItem();
			Node<T>* temp=HeadPtr;
			HeadPtr = HeadPtr->getNext();
			temp->setNext(nullptr);
			delete temp;
			Count--;
			return true;
		}
	}
	Node<T>* GetFirst()
	{
		return HeadPtr;
	}

	void Print();
	

	

};


template<typename T>
void List<T>:: Print()
{
	if (HeadPtr == nullptr)
		return;
	Node<T>* curr = HeadPtr;
	while (curr)
	{
		cout << (curr->getItem());
		if (curr->getNext() != nullptr)
			cout << ",";
		curr = curr->getNext();
	}
	return;
}

template<>
inline void List<NormalCargo*>::Print()
{
	if (HeadPtr == nullptr)
		return;
	Node<NormalCargo*>* curr = HeadPtr;
	while (curr)
	{
		cout << curr->getItem()->GetID();
		if (curr->getNext() != nullptr)
			cout << ",";
		curr = curr->getNext();
	}
	return;
}

template<>
inline void List<SpecialCargo*>::Print()
{
	if (HeadPtr == nullptr)
		return;
	Node<SpecialCargo*>* curr = HeadPtr;
	while (curr)
	{
		cout << curr->getItem()->GetID();
		if (curr->getNext() != nullptr)
			cout << ",";
		curr = curr->getNext();
	}
	return;
}

template<>
inline void List<VipCargo*>::Print()
{
	if (HeadPtr == nullptr)
		return;
	Node<VipCargo*>* curr = HeadPtr;
	while (curr)
	{
		cout << curr->getItem()->GetID();
		if (curr->getNext() != nullptr)
			cout << ",";
		curr = curr->getNext();
	}
	return;
}