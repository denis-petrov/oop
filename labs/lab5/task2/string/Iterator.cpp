#include "Iterator.h"

using namespace std;

CIterator::CIterator(char* ptr)
	: CIteratorImpl(ptr)
{
}

char& CIterator::operator*()
{
	return *m_ptr;
}

char* CIterator::operator->()
{
	return m_ptr;
}