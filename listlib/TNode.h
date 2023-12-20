#pragma once

template<class T>
struct TNode
{
	T value;
	TNode* pNext;

	TNode() : pNext(nullptr) {}
	TNode(const T& val, TNode* next = nullptr) : value(val), pNext(next) {}
};
