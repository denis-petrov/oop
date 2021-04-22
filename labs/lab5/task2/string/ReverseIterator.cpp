#include "ReverseIterator.h"

CReverseIterator::CReverseIterator(char* ptr)
	: CIterator(ptr)
{
}

CReverseIterator::CReverseIterator(CIterator const& iterator)
{
	this->m_ptr = iterator.getPtr();
}

CReverseIterator& CReverseIterator::operator=(CIterator const& iterator)
{
	this->m_ptr = iterator.getPtr();
	return *this;
}

CReverseIterator& CReverseIterator::operator=(char* ptr)
{
	this->m_ptr = ptr;
	return *this;
}

CReverseIterator& CReverseIterator::operator+=(ptrdiff_t const& rhs)
{
	this->m_ptr -= rhs;
	return *this;
}

CReverseIterator& CReverseIterator::operator-=(ptrdiff_t const& rhs)
{
	this->m_ptr += rhs;
	return *this;
}

CReverseIterator& CReverseIterator::operator++()
{
	this->m_ptr--;
	return *this;
}

CReverseIterator& CReverseIterator::operator--()
{
	this->m_ptr++;
	return *this;
}

CReverseIterator CReverseIterator::operator++(int)
{
	this->m_ptr--;
	return *this;
}

CReverseIterator CReverseIterator::operator--(int)
{
	this->m_ptr++;
	return *this; 
}

CReverseIterator CReverseIterator::operator+(const int rhs)
{
	auto prevPtr = this->m_ptr;
	this->m_ptr -= rhs;
	this->m_ptr = prevPtr;
	return *this; 
}

CReverseIterator CReverseIterator::operator-(const int rhs)
{
	auto prevPtr = this->m_ptr;
	this->m_ptr += rhs;
	this->m_ptr = prevPtr;
	return *this; 
}

ptrdiff_t CReverseIterator::operator-(CReverseIterator const& reverseIterator)
{
	return std::distance(this->getPtr(), reverseIterator.getPtr());
}

CIterator CReverseIterator::base()
{
	CIterator iterator(this->m_ptr);
	++iterator;
	return iterator;
}
