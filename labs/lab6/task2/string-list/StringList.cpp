#include "StringList.h"
#include "stdafx.h"

using namespace std;

CStringList::CStringList(CStringList const& other)
{
	if (!other.m_lastNode)
		return;

	try
	{
		auto currNode = other.m_firstNode;
		while (currNode)
		{
			PushBack(currNode->data);
			currNode = currNode->next;
		}
	}
	catch (...)
	{
		Clear();
		throw;
	}
}

CStringList::CStringList(CStringList&& other) noexcept
{
	m_firstNode = other.m_firstNode;
	m_lastNode = other.m_lastNode;
	m_size = other.m_size;

	other.m_firstNode = nullptr;
	other.m_lastNode = nullptr;
	other.m_size = 0;
}

CStringList::~CStringList()
{
	Clear();
}

void CStringList::PushFront(string const& data) 
{
	Node* newNode = new Node(data, nullptr, m_firstNode);
	if (m_firstNode)
	{
		m_firstNode->prev = newNode;
	}
	else
	{
		m_lastNode = newNode;
	}
	m_firstNode = newNode;
	if (!m_lastNode)
	{
		m_firstNode = m_firstNode;
	}
	++m_size;
}

void CStringList::PushBack(string const& data)
{
	Node* newNode = new Node(data, m_lastNode, nullptr);
	if (m_lastNode)
	{
		m_lastNode->next = newNode;
	}
	else
	{
		m_firstNode = newNode;
	}
	m_lastNode = newNode;
	++m_size;
}

size_t CStringList::GetSize() const
{
	return m_size;
}

bool CStringList::IsEmpty() const
{
	return (m_size == 0);
}

string& CStringList::GetBackElement()
{
	assert(m_lastNode);
	return m_lastNode->data;
}

string const& CStringList::GetBackElement() const
{
	assert(m_lastNode);
	return m_lastNode->data;
}

void CStringList::Clear() 
{
	auto curr = m_firstNode;
	while (curr)
	{
		auto next = curr->next;
		delete curr;
		curr = next;
	}
	m_firstNode = nullptr;
	m_lastNode = nullptr;
	m_size = 0;
}

ostream& operator<<(ostream& os, CStringList const& rhs)
{
	auto currNode = rhs.m_firstNode;
	while (currNode)
	{
		os << currNode->data;
		currNode = currNode->next;
	}
	return os;
}

CStringList::CIterator::CIterator(CStringList::Node* node)
	: m_node(node)
{
}

CStringList::CIterator::reference CStringList::CIterator::operator*() const
{
	return *m_node;
}

CStringList::CIterator::pointer CStringList::CIterator::operator->()
{
	return m_node;
}

CStringList::CIterator& CStringList::CIterator::operator++()
{
	assert(m_node != nullptr);
	m_node = m_node->next;
	return *this;
}

CStringList::CIterator& CStringList::CIterator::operator++(int)
{
	assert(m_node != nullptr);
	m_node = m_node->next;
	return *this;
}

CStringList::CIterator& CStringList::CIterator::operator--()
{
	assert(m_node != nullptr);
	m_node = m_node->prev;
	return *this;
}

CStringList::CIterator& CStringList::CIterator::operator--(int)
{
	assert(m_node != nullptr);
	m_node = m_node->prev;
	return *this;
}

bool CStringList::CIterator::operator!=(CStringList::CIterator const& other) const
{
	return m_node != other.m_node;
}


	//CStringList::Iterator CStringList::begin()
//{
//	return Iterator(m_firstNode);
//}

//CStringList::Iterator CStringList::end()
//{
//	return Iterator(m_lastNode->next);
//}
//
//CStringList::Iterator CStringList::cbegin() const
//{
//	return Iterator(m_firstNode);
//}
//
//CStringList::Iterator CStringList::cend() const
//{
//	return Iterator(m_lastNode->next);
//}
//
//reverse_iterator<CStringList::Iterator> CStringList::rbegin()
//{
//	return make_reverse_iterator(begin());
//}
//
//reverse_iterator<CStringList::Iterator> CStringList::rend()
//{
//	return make_reverse_iterator(end());
//}

CStringList::CIterator CStringList::begin()
{
	return CIterator(m_firstNode);
}

CStringList::CIterator CStringList::end()
{
	return CIterator(m_lastNode->next);
}

CStringList::CIterator CStringList::cbegin() const
{
	return CIterator(m_firstNode);
}

CStringList::CIterator CStringList::cend() const
{
	return CIterator(m_lastNode->next);
}

reverse_iterator<CStringList::CIterator> CStringList::rbegin()
{
	return make_reverse_iterator(begin());
}

reverse_iterator<CStringList::CIterator> CStringList::rend()
{
	return make_reverse_iterator(end());
}
