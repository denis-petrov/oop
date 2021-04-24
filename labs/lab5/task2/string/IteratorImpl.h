#pragma once
#include "stdafx.h"

class CIteratorImpl
{
public:
	CIteratorImpl(char* ptr = nullptr);

	CIteratorImpl& operator++();
	CIteratorImpl& operator--();
	CIteratorImpl operator++(int);
	CIteratorImpl operator--(int);
	CIteratorImpl& operator+=(ptrdiff_t const& rhs);
	CIteratorImpl& operator-=(ptrdiff_t const& rhs);
	CIteratorImpl operator+(ptrdiff_t const& rhs);
	CIteratorImpl operator-(ptrdiff_t const& rhs);

	ptrdiff_t operator-(CIteratorImpl const& it);
	
	operator bool() const;

	friend bool operator==(CIteratorImpl const& lhs, CIteratorImpl const& rhs) { return lhs.m_ptr == rhs.m_ptr; };
	friend bool operator!=(CIteratorImpl const& lhs, CIteratorImpl const& rhs) { return lhs.m_ptr != rhs.m_ptr; };

protected:
	char* m_ptr;
};
