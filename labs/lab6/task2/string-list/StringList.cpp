#include "StringList.h"
#include "stdafx.h"

using namespace std;

CStringList::CStringList(CStringList const& other)
{
	if (!other.m_lastNode)
		return;

	try
	{
		auto currNode = other.m_firstNode.get();
		while (currNode)
		{
			PushBack(currNode->data);
			currNode = currNode->next.get();
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
	m_firstNode = move(other.m_firstNode);
	m_lastNode = other.m_lastNode;
	m_size = other.m_size;
}

CStringList::~CStringList()
{
	Clear();
}

void CStringList::PushFront(string const& data) // TODO
{
	auto newNode = make_unique<Node>(data, nullptr, move(m_firstNode));
	m_firstNode->prev = newNode.get();
	m_firstNode = move(newNode);
	
	++m_size;
}

void CStringList::PushBack(string const& data)
{
	auto newNode = make_unique<Node>(data, m_lastNode, nullptr);
	Node* newLastNode = newNode.get();
	if (m_lastNode)
	{
		m_lastNode->next = move(newNode);
	}
	else
	{
		m_firstNode = move(newNode);
	}
	m_lastNode = newLastNode;
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
	while (m_firstNode)
		m_firstNode = move(m_firstNode->next);
	m_lastNode = nullptr;
	m_size = 0;
}

ostream& operator<<(ostream& os, CStringList const& rhs)
{
	auto currNode = rhs.m_firstNode.get();
	while (currNode)
	{
		os << currNode->data;
		currNode = currNode->next.get();
	}
	return os;
}

