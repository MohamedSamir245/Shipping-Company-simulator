#pragma once

template < typename T>
class Node
{
private:
	T item;
	Node<T>* next;
public:
	Node(){}
	Node(const T& New_Item);
	void setItem(const T& New_Item);
	void setNext(Node<T>* nextNodePtr);
	T getItem() const;
	Node<T>* getNext() const;
	~Node();
};


template < typename T>
Node<T>::Node(const T& New_Item)
{
	item = New_Item;
	next = nullptr;
}


template < typename T>
void Node<T>::setItem(const T& New_Item)
{
	item = New_Item;
}

template < typename T>
void Node<T>::setNext(Node<T>* nextNodePtr)
{
	next = nextNodePtr;
}

template < typename T>
T Node<T>::getItem() const
{
	return item;
}

template < typename T>
Node<T>* Node<T>::getNext() const
{
	return next;
}

template < typename T>

Node<T>::~Node()
{
}
