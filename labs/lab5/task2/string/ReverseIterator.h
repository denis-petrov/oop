#pragma once
#include "stdafx.h"
#include "Iterator.h"

class CReverseIterator : public CIterator
{
public:
	CReverseIterator(char* ptr = nullptr);

	CReverseIterator(const CIterator& iterator);
	CReverseIterator(CReverseIterator const& reverseIterator) = default;
	~CReverseIterator() {}

	CReverseIterator& operator=(CReverseIterator const& reverseIterator) = default;
	CReverseIterator& operator=(CIterator const& iterator);
	CReverseIterator& operator=(char* ptr);

	CReverseIterator& operator+=(ptrdiff_t const& rhs);
	CReverseIterator& operator-=(ptrdiff_t const& movement);
	CReverseIterator& operator++();
	CReverseIterator& operator--();
	CReverseIterator operator++(int);
	CReverseIterator operator--(int);
	CReverseIterator operator+(const int rhs);
	CReverseIterator operator-(const int rhs);

	ptrdiff_t operator-(CReverseIterator const& reverseIterator);
};
