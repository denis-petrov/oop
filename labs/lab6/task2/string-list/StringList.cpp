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

void CStringList::Insert(iterator const& it, string const& data)
{
	if (it.m_node->prev)
	{
		Node* newNode = new Node(data, it.m_node->prev, it.m_node);
		it.m_node->prev->next = newNode;
		it.m_node->prev = newNode;
	}
	else
	{
		Node* newNode = new Node(data, nullptr, it.m_node);
		it.m_node->prev = newNode;
		m_firstNode = newNode;
	}
	m_size++;
}

void CStringList::Insert(const_iterator const& it, string const& data)
{
	if (it.m_node->prev)
	{
		Node* newNode = new Node(data, it.m_node->prev, it.m_node);
		it.m_node->prev->next = newNode;
		it.m_node->prev = newNode;
	}
	else
	{
		Node* newNode = new Node(data, nullptr, it.m_node);
		it.m_node->prev = newNode;
		m_firstNode = newNode;
	}
	m_size++;
}

void CStringList::Insert(reverse_iterator const& it, string const& data)
{
	if (it.base().m_node->prev)
	{
		Node* newNode = new Node(data, it.base().m_node->prev, it.base().m_node);
		it.base().m_node->prev->next = newNode;
		it.base().m_node->prev = newNode;
	}
	else
	{
		Node* newNode = new Node(data, nullptr, it.base().m_node);
		it.base().m_node->prev = newNode;
		m_firstNode = newNode;
	}
	m_size++;
}

void CStringList::Insert(const_reverse_iterator const& it, string const& data)
{
	if (it.base().m_node->prev)
	{
		Node* newNode = new Node(data, it.base().m_node->prev, it.base().m_node);
		it.base().m_node->prev->next = newNode;
		it.base().m_node->prev = newNode;
	}
	else
	{
		Node* newNode = new Node(data, nullptr, it.base().m_node);
		it.base().m_node->prev = newNode;
		m_firstNode = newNode;
	}
	m_size++;
}

void CStringList::Delete(iterator& it) 
{
	if (it.m_node->prev)
		it.m_node->prev->next = it.m_node->next;

	if (it.m_node->next)
		it.m_node->next->prev = it.m_node->prev;

	if (m_firstNode == it.m_node)
		m_firstNode = it.m_node->next;

	if (m_lastNode == it.m_node)
		m_lastNode = it.m_node->prev;

	m_size--;
	auto temp = it.m_node->next;
	delete it.m_node;
	it = temp;
}

void CStringList::Delete(const_iterator& it)
{
	if (it.m_node->prev)
		it.m_node->prev->next = it.m_node->next;

	if (it.m_node->next)
		it.m_node->next->prev = it.m_node->prev;

	if (m_firstNode == it.m_node)
		m_firstNode = it.m_node->next;

	if (m_lastNode == it.m_node)
		m_lastNode = it.m_node->prev;

	m_size--;
	auto temp = it.m_node->next;
	delete it.m_node;
	it = temp;
}

void CStringList::Delete(reverse_iterator& it)
{
	if (it.base().m_node->prev)
		it.base().m_node->prev->next = it.base().m_node->next;

	if (it.base().m_node->next)
		it.base().m_node->next->prev = it.base().m_node->prev;

	if (m_firstNode == it.base().m_node)
		m_firstNode = it.base().m_node->next;

	if (m_lastNode == it.base().m_node)
		m_lastNode = it.base().m_node->prev;

	m_size--;
	auto temp = it.base().m_node->next;
	delete it.base().m_node;
	it.base()= temp;
}

void CStringList::Delete(const_reverse_iterator& it)
{
	if (it.base().m_node->prev)
		it.base().m_node->prev->next = it.base().m_node->next;

	if (it.base().m_node->next)
		it.base().m_node->next->prev = it.base().m_node->prev;

	if (m_firstNode == it.base().m_node)
		m_firstNode = it.base().m_node->next;

	if (m_lastNode == it.base().m_node)
		m_lastNode = it.base().m_node->prev;

	m_size--;
	auto temp = it.base().m_node->next;
	delete it.base().m_node;
	it.base() = temp;
}