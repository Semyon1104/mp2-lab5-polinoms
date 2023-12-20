#pragma once
#include "TList.h"
using namespace std;


template<class T>
class THeadList : public TList<T>
{
protected:
	TNode<T>* pHead;  // заголовок, pFirst - звено за pHead
public:
	THeadList();
	~THeadList();
	void InsertFirst(T item); // вставка звеньев после заголовка
	void DeleteFirst(); // удалить первое звено
};

template<class T>
THeadList<T>::THeadList()
{
	pHead = new TNode<T>;
	this->pFirst = pHead;
	pHead->pNext = this->pStop;
}

template<class T>
THeadList<T>::~THeadList()
{
	delete pHead;
}

template <class T>
void THeadList<T>::InsertFirst(T item)
{
	TNode<T>* newNode = new TNode<T>;
	newNode->value = item;

	if (pFirst == nullptr) {
		pFirst = newNode;
		pLast = newNode;
		pStop->pNext = pFirst;
		pFirst->pNext = pStop;
	}
	else {
		newNode->pNext = pFirst;
		pFirst = newNode;
	}

	length++;
}

template <class T>
void THeadList<T>::DeleteFirst()
{
	if (this->pFirst != this->pStop) {
		TNode<T>* temp = this->pFirst;
		this->pFirst = this->pFirst->pNext;
		delete temp;
		this->length--;
		if (this->pFirst == this->pStop) {
			this->pLast = this->pStop;
		}
	}
}