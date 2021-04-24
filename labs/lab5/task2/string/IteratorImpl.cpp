#include "IteratorImpl.h"

CIteratorImpl::CIteratorImpl(char* ptr)
	: m_ptr(ptr)
{
}

CIteratorImpl::operator bool() const
{
	if (m_ptr)
		return true;
	else
		return false;
}

CIteratorImpl& CIteratorImpl::operator++()
{
	++m_ptr;
	return (*this);
}

CIteratorImpl& CIteratorImpl::operator--()
{
	--m_ptr;
	return (*this);
}

CIteratorImpl CIteratorImpl::operator++(int)
{
	auto temp(*this);
	++m_ptr;
	return temp;
}

CIteratorImpl CIteratorImpl::operator--(int)
{
	auto temp(*this);
	--m_ptr;
	return temp;
}

CIteratorImpl& CIteratorImpl::operator+=(ptrdiff_t const& rhs)
{
	m_ptr += rhs;
	return (*this);
}

CIteratorImpl& CIteratorImpl::operator-=(ptrdiff_t const& rhs)
{
	m_ptr -= rhs;
	return (*this);
}

CIteratorImpl CIteratorImpl::operator+(ptrdiff_t const& rhs)
{
	auto oldPtr = m_ptr;
	m_ptr += rhs;
	auto temp(*this);
	m_ptr = oldPtr;
	return temp;
}

CIteratorImpl CIteratorImpl::operator-(ptrdiff_t const& rhs)
{
	auto oldPtr = m_ptr;
	m_ptr -= rhs;
	auto temp(*this);
	m_ptr = oldPtr;
	return temp;
}

ptrdiff_t CIteratorImpl::operator-(CIteratorImpl const& it)
{
	return std::distance(it.m_ptr, m_ptr);
}
