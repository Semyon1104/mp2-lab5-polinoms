#pragma once
#include "TNode.h"
#include <iostream>
using namespace std;

template<class T>
class TList
{
protected:
	TNode<T>* pFirst; // ������ �����
	TNode<T>* pCurrent; // ������� �����
	TNode<T>* pPrevious; // ����� ����� �������
	TNode<T>* pLast; // ��������� �����
	TNode<T>* pStop; // �������� ���������, ����������� ����� ������
	int length; // ���������� ������� � ������

public:

	TList();
	~TList();
	int GetLength() { return length; }
	bool IsEmpty(); // ������ ���� ?
	// ������� �������
	void InsertFirst(T item); // ����� ������
	void InsertCurrent(T item); // ����� ������� 
	void InsertLast(T item);  // �������� ��������� 

	// �������� �������
	void DeleteFirst(); // ������� ������ ����� 
	void DeleteCurrent(); // ������� ������� �����

	void GoNext(); // ����� ������ �������� �����
	// (=1 ����� ���������� GoNext ��� ���������� ����� ������)

	void Reset(); // ���������� �� ������ ������
	bool IsEnd();  // ������ �������� ?

	T GetCurrentItem();
	void SetCurrentItem(T item) { pCurrent->value = item; }


};
template <class T>
TList<T>::TList()
{
	pFirst = nullptr;
	pCurrent = nullptr;
	pPrevious = nullptr;
	pLast = nullptr;
	pStop = nullptr;
	length = 0;
}

template <class T>
TList<T>::~TList()
{
	Reset();
	delete pStop;
}

template <class T>
bool TList<T>::IsEmpty()
{
	return length == 0;
}

template <class T>
void TList<T>::InsertFirst(T item)
{
	pFirst = new TNode<T>(item, pFirst);
	length++;
	if (length == 1)
		pLast = pCurrent = pFirst;
}

template <class T>
void TList<T>::InsertLast(T item)
{
	if (pCurrent == pStop)
		return InsertFirst(item);
	pLast->pNext = new TNode<T>(item, pStop);
	pLast = pLast->pNext;
	length++;
}

template <class T>
void TList<T>::InsertCurrent(T item)
{
	if (pCurrent == pFirst)
		return InsertFirst(item);
	pPrevious->pNext = new TNode<T>(item, pCurrent);
	pCurrent = pPrevious->pNext;
	length++;

}

template <class T>
void TList<T>::DeleteFirst()
{
	if (IsEmpty())
		return;
	TNode<T>* temp = pFirst;
	pFirst = pFirst->pNext;
	delete temp;
	length--;
	if (length == 0)
		pLast = pCurrent = pPrevious = pFirst = pStop;
	else if (pCurrent == temp)
		pCurrent = pFirst;
}

template <class T>
void TList<T>::DeleteCurrent()
{
	if (pCurrent == pStop)
		return;
	if (pCurrent == pFirst)
		return DeleteFirst();
	pPrevious->pNext = pCurrent->pNext;
	delete pCurrent;
	pCurrent = pPrevious->pNext;
	length--;
	if (length == 0)
		pLast = pCurrent = pPrevious = pFirst = pStop;
}

template <class T>
T TList<T>::GetCurrentItem()
{
	if (pCurrent == pStop)
		throw "Error";
	return pCurrent->value;
}

template <class T>
void TList<T>::Reset()
{
	while (!IsEmpty())
		DeleteFirst();
}

template <class T>
void TList<T>::GoNext() {
	if (pCurrent != pStop)
		pPrevious = pCurrent;

	if (pCurrent != pLast) {
		pCurrent = pCurrent->pNext;
	}
	else {
		pCurrent = pStop;
	}
}



template <class T>
bool TList<T>::IsEnd()
{
	return pCurrent == pStop;
}





