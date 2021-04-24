#include "ConstIterator.h"

using namespace std;

CConstIterator::CConstIterator(char* ptr)
	: CIteratorImpl(ptr)
{
}

char const& CConstIterator::operator*() const
{
	return *m_ptr;
}

char const* CConstIterator::operator->() const
{
	return m_ptr;
}