#include "ConstReverseIterator.h"
using namespace std;

CConstReverseIterator::CConstReverseIterator(char* ptr)
	: CReverseIteratorImpl(ptr)
{
}

char const& CConstReverseIterator::operator*() const
{
	return *m_ptr;
}

char const* CConstReverseIterator::operator->() const
{
	return m_ptr;
}