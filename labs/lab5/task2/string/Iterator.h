#pragma once
#include "stdafx.h"

class CIterator
{
public:
	CIterator(char* ptr = nullptr);
	CIterator(CIterator const& it) = default;
	~CIterator() {}

	operator bool() const;

	char& operator*();
	char const& operator*() const;
	char* operator->();
	CIterator& operator++();
	CIterator& operator--();
	CIterator operator++(int);
	CIterator operator--(int);
	CIterator& operator+=(ptrdiff_t const& rhs);
	CIterator& operator-=(ptrdiff_t const& rhs);
	CIterator operator+(ptrdiff_t const& rhs);
	CIterator operator-(ptrdiff_t const& rhs);

	ptrdiff_t operator-(CIterator const& it);

	friend bool operator==(CIterator const& lhs, CIterator const& rhs) { return lhs.m_ptr == rhs.m_ptr; };
	friend bool operator!=(CIterator const& lhs, CIterator const& rhs) { return lhs.m_ptr != rhs.m_ptr; };

	char* getPtr() const;
	const char* getConstPtr() const;

protected:
	char* m_ptr;
};
