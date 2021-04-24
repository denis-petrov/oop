#include "ReverseIteratorImpl.h"

CReverseIteratorImpl::CReverseIteratorImpl(char* ptr)
	: m_ptr(ptr)
{
}

CReverseIteratorImpl::operator bool() const
{
	if (m_ptr)
		return true;
	else
		return false;
}

CReverseIteratorImpl& CReverseIteratorImpl::operator++()
{
	--this->m_ptr;
	return (*this);
}

CReverseIteratorImpl& CReverseIteratorImpl::operator--()
{
	++this->m_ptr;
	return (*this);
}

CReverseIteratorImpl CReverseIteratorImpl::operator++(int)
{
	auto temp(*this);
	--m_ptr;
	return temp;
}

CReverseIteratorImpl CReverseIteratorImpl::operator--(int)
{
	auto temp(*this);
	++m_ptr;
	return temp;
}

CReverseIteratorImpl& CReverseIteratorImpl::operator+=(ptrdiff_t const& rhs)
{
	m_ptr -= rhs;
	return (*this);
}

CReverseIteratorImpl& CReverseIteratorImpl::operator-=(ptrdiff_t const& rhs)
{
	m_ptr += rhs;
	return (*this);
}

CReverseIteratorImpl CReverseIteratorImpl::operator+(ptrdiff_t const& rhs)
{
	auto oldPtr = m_ptr;
	m_ptr -= rhs;
	auto temp(*this);
	m_ptr = oldPtr;
	return temp;
}

CReverseIteratorImpl CReverseIteratorImpl::operator-(ptrdiff_t const& rhs)
{
	auto oldPtr = m_ptr;
	m_ptr += rhs;
	auto temp(*this);
	m_ptr = oldPtr;
	return temp;
}

ptrdiff_t CReverseIteratorImpl::operator-(CReverseIteratorImpl const& it)
{
	return std::distance(it.m_ptr, m_ptr);
}
