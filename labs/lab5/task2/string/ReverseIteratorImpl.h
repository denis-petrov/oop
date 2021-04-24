#pragma once
#include "stdafx.h"

class CReverseIteratorImpl
{
public:
	CReverseIteratorImpl(char* ptr = nullptr);

	CReverseIteratorImpl& operator++();
	CReverseIteratorImpl& operator--();
	CReverseIteratorImpl operator++(int);
	CReverseIteratorImpl operator--(int);
	CReverseIteratorImpl& operator+=(ptrdiff_t const& rhs);
	CReverseIteratorImpl& operator-=(ptrdiff_t const& rhs);
	CReverseIteratorImpl operator+(ptrdiff_t const& rhs);
	CReverseIteratorImpl operator-(ptrdiff_t const& rhs);

	ptrdiff_t operator-(CReverseIteratorImpl const& it);

	operator bool() const;

	friend bool operator==(CReverseIteratorImpl const& lhs, CReverseIteratorImpl const& rhs) { return lhs.m_ptr == rhs.m_ptr; };
	friend bool operator!=(CReverseIteratorImpl const& lhs, CReverseIteratorImpl const& rhs) { return lhs.m_ptr != rhs.m_ptr; };

protected:
	char* m_ptr;
};
