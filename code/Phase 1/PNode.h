#pragma once

template < typename T1, typename T2>
class PNode
{
private:
	T1 Item;
	T2 priority;
	PNode<T1, T2>* next;

public:

	PNode(const T1& New_Item, const T2& Item_priority);
	void setItem(const T1& New_Item);
	void setPriority(const T2& Item_priority);
	void setNext(PNode<T1, T2>* nextPNodePtr);
	T1 getItem() const;
	T2 getPriority() const;
	PNode<T1, T2>* getNext() const;
	~PNode();
};


template < typename T1, typename T2>
PNode<T1, T2>::PNode(const T1& New_Item, const T2& Item_priority)
{
	Item = New_Item;
	priority = Item_priority;
	next = nullptr;
}


template < typename T1, typename T2>
void PNode<T1, T2>::setItem(const T1& New_Item)
{
	Item = New_Item;
}

template < typename T1, typename T2>
void PNode<T1, T2>::setPriority(const T2& Item_priority)
{
	priority = Item_priority;
}

template < typename T1, typename T2>
void  PNode<T1, T2>::setNext(PNode<T1, T2>* nextPNodePtr)
{
	next = nextPNodePtr;
}

template < typename T1, typename T2>
T1 PNode<T1, T2>::getItem() const
{
	return Item;
}

template < typename T1, typename T2>
T2 PNode<T1, T2>::getPriority() const
{
	return priority;
}

template < typename T1, typename T2>
PNode<T1, T2>* PNode<T1, T2>::getNext() const
{
	return next;
}

template < typename T1, typename T2>
PNode<T1, T2>::~PNode()
{
}