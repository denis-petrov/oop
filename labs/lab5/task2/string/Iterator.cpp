#include "Iterator.h"

using namespace std;

CIterator::CIterator(char* ptr)
	: m_ptr(ptr)
{
}

CIterator::operator bool() const
{
	if (m_ptr)
		return true;
	else
		return false;
}

char& CIterator::operator*()
{
	return *m_ptr;
}

char const& CIterator::operator*() const
{
	return *m_ptr;
}

char* CIterator::operator->()
{
	return m_ptr;
}

CIterator& CIterator::operator++()
{
	++m_ptr;
	return *this;
}

CIterator& CIterator::operator--()
{
	--m_ptr;
	return *this;
}

CIterator CIterator::operator++(int)
{
	CIterator tmp = *this;
	++(*this);
	return tmp;
}

CIterator CIterator::operator--(int)
{
	CIterator tmp = *this;
	--(*this);
	return tmp;
}

CIterator& CIterator::operator+=(ptrdiff_t const& rhs)
{
	m_ptr += rhs;
	return *this;
}

CIterator& CIterator::operator-=(ptrdiff_t const& rhs)
{
	m_ptr -= rhs;
	return *this;
}

CIterator CIterator::operator+(ptrdiff_t const& rhs)
{
	auto oldPtr = m_ptr;
	m_ptr += rhs;
	auto temp(*this);
	m_ptr = oldPtr;
	return temp;
}

CIterator CIterator::operator-(ptrdiff_t const& rhs)
{
	auto oldPtr = m_ptr;
	m_ptr -= rhs;
	auto temp(*this);
	m_ptr = oldPtr;
	return temp;
}

ptrdiff_t CIterator::operator-(CIterator const& it)
{
	return distance(it.getPtr(), this->getPtr());
}

char* CIterator::getPtr() const 
{
	return m_ptr;
}

char const* CIterator::getConstPtr() const 
{
	return m_ptr;
}