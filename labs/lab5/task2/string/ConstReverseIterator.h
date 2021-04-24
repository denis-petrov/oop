#pragma once
#include "ReverseIteratorImpl.h"

class CConstReverseIterator : public CReverseIteratorImpl
{
public:
	CConstReverseIterator(char* ptr = nullptr);
	CConstReverseIterator(CConstReverseIterator const& it) = default;
	~CConstReverseIterator() {}

	char const& operator*() const;
	char const* operator->() const;
};
