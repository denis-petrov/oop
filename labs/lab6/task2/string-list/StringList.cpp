#include "StringList.h"
#include "stdafx.h"

using namespace std;

CStringList::CStringList(CStringList const& other)
{
	if (!other.m_sentryNode->prev)
		return;

	try
	{
		auto currNode = other.m_firstNode;
		while (currNode && currNode != other.m_sentryNode)
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

CStringList::CStringList(CStringList&& rvalue) noexcept
{
	swap(m_firstNode, rvalue.m_firstNode);
	swap(m_sentryNode, rvalue.m_sentryNode);
	swap(m_size, rvalue.m_size);
}

CStringList::~CStringList() noexcept
{
	Clear();
	delete m_sentryNode;
}

void CStringList::PushFront(string const& data) 
{
	Node* newNode = new Node(data, nullptr, m_firstNode);
	if (m_firstNode)
		m_firstNode->prev = newNode;
	else
		m_sentryNode->prev = newNode;
	
	m_firstNode = newNode;
	++m_size;
}

void CStringList::PushBack(string const& data)
{
	Node* newNode = new Node(data, m_sentryNode->prev, m_sentryNode);
	if (m_sentryNode->prev)
		m_sentryNode->prev->next = newNode;
	else
		m_firstNode = newNode;

	m_sentryNode->prev = newNode;
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
	assert(m_sentryNode->prev);
	return m_sentryNode->prev->data;
}

string const& CStringList::GetBackElement() const
{
	assert(m_sentryNode->prev);
	return m_sentryNode->prev->data;
}

string& CStringList::GetFirstElement()
{
	assert(m_firstNode);
	return m_firstNode->data;
}

string const& CStringList::GetFirstElement() const
{
	assert(m_firstNode);
	return m_firstNode->data;
}

void CStringList::Clear() 
{
	auto curr = m_firstNode;
	while (curr && curr != m_sentryNode)
	{
		auto next = curr->next;
		delete curr;
		curr = next;
	}
	m_firstNode = nullptr;
	m_size = 0;
}

ostream& operator<<(ostream& os, CStringList const& rhs)
{
	auto currNode = rhs.m_firstNode;
	for (size_t i = 0; i < rhs.GetSize(); i++)
	{
		os << currNode->data;
		currNode = currNode->next;
	}
	return os;
}

CStringList::iterator CStringList::begin()
{
	return iterator(m_firstNode);
}

CStringList::iterator CStringList::end()
{
	return iterator(m_sentryNode);
}

CStringList::const_iterator CStringList::cbegin() const
{
	return const_iterator(m_firstNode);
}

CStringList::const_iterator CStringList::cend() const
{
	return const_iterator(m_sentryNode);
}

CStringList::reverse_iterator CStringList::rbegin()
{
	return make_reverse_iterator(end());
}

CStringList::reverse_iterator CStringList::rend()
{
	return make_reverse_iterator(begin());
}

CStringList::const_reverse_iterator CStringList::crbegin()
{
	return make_reverse_iterator(cend());
}

CStringList::const_reverse_iterator CStringList::crend()
{
	return make_reverse_iterator(cbegin());
}

void CStringList::Insert(iterator const& it, string const& data)
{
	if (!it.m_node)
	{
		PushBack(data);
		return;
	}

	Node* newNode = new Node(data, it.m_node->prev, it.m_node);
	if (it.m_node->prev)
		it.m_node->prev->next = newNode;
	else
		m_firstNode = newNode;

	it.m_node->prev = newNode;
	m_size++;
}

void CStringList::Insert(reverse_iterator const& it, string const& data)
{
	Insert(it.base(), data);
}

void CStringList::Delete(iterator& it) 
{
	if (!it.m_node)
		throw invalid_argument("Node does not exist.");

	if (it.m_node == m_sentryNode)
		throw invalid_argument("Sentry Node can not be deleted.");

	if (it.m_node->prev)
		it.m_node->prev->next = it.m_node->next;

	if (it.m_node->next)
		it.m_node->next->prev = it.m_node->prev;

	if (m_firstNode == it.m_node)
		m_firstNode = it.m_node->next;

	if (m_sentryNode->prev == it.m_node)
		m_sentryNode->prev = it.m_node->prev;

	m_size--;
	auto temp = it.m_node->next;
	delete it.m_node;
	it = temp;
}

void CStringList::Delete(reverse_iterator& it)
{
	if (!it.base().m_node || !it.base().m_node->prev)
		throw invalid_argument("Node does not exist.");
	auto itDel = --it.base();
	Delete(itDel);
	it.base() = itDel.m_node;
}