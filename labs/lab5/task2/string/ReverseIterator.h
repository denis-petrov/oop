#pragma once
#include "ReverseIteratorImpl.h"

class CReverseIterator : public CReverseIteratorImpl
{
public:
	CReverseIterator(char* ptr = nullptr);
	CReverseIterator(const CReverseIterator& it) = default;
	~CReverseIterator() {}

	char& operator*();
	char* operator->();
};
