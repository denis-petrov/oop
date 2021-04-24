#include "ReverseIterator.h"

using namespace std;

CReverseIterator::CReverseIterator(char* ptr)
	: CReverseIteratorImpl(ptr)
{
}

char& CReverseIterator::operator*()
{
	return *m_ptr;
}

char* CReverseIterator::operator->()
{
	return m_ptr;
}