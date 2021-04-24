#pragma once
#include "IteratorImpl.h"

class CIterator : public CIteratorImpl
{
public:
	CIterator(char* ptr = nullptr);
	CIterator(CIterator const& it) = default;
	~CIterator() {}

	char& operator*();
	char* operator->();
};
