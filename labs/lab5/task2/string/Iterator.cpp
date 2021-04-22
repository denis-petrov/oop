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
	m_ptr++;
	return *this;
}

CIterator& CIterator::operator--()
{
	m_ptr--;
	return *this;
}

CIterator CIterator::operator++(int)
{
	//++(*this);
	return ++(*this);
}

CIterator CIterator::operator--(int)
{
	//--(*this);
	return --(*this); 
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
	auto prevPtr = m_ptr;
	m_ptr += rhs;
	m_ptr = prevPtr;
	return *this;
}

CIterator CIterator::operator-(ptrdiff_t const& rhs)
{
	auto prevPtr = m_ptr;
	m_ptr -= rhs;
	m_ptr = prevPtr;
	return *this;
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