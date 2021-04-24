#pragma once 
#include "IteratorImpl.h"

class CConstIterator : public CIteratorImpl
{
public:
	CConstIterator(char* ptr = nullptr);
	CConstIterator(CConstIterator const& it) = default;
	~CConstIterator() {}

	char const& operator*() const;
	char const* operator->() const;
};
