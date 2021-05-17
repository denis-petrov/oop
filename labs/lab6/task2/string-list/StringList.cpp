#include "StringList.h"
#include "stdafx.h"

using namespace std;

CStringList::CStringList() 
	: m_size(0)
{
	m_baseNode = new Node("", nullptr, nullptr);
	m_baseNode->prev = m_baseNode->next = m_baseNode;
}

CStringList::CStringList(CStringList const& other)
	: CStringList()
{
	for (auto const& currString : other)
	{
		try
		{
			PushBack(currString);
		}
		catch (...)
		{
			Clear();
			delete m_baseNode;
			throw;
		}
	}
}

CStringList::CStringList(CStringList&& rvalue) noexcept
	: CStringList()
{
	swap(m_baseNode, rvalue.m_baseNode);
	swap(m_size, rvalue.m_size);
}

CStringList::~CStringList() noexcept
{
	Clear();
	delete m_baseNode;
}

void CStringList::PushFront(string const& data) 
{
	Node* newNode = new Node(data, nullptr, m_baseNode->next);
	if (m_baseNode->next)
		m_baseNode->next->prev = newNode;
	else
		m_baseNode->prev = newNode;
	
	m_baseNode->next = newNode;
	++m_size;
}

void CStringList::PushBack(string const& data)
{
	Node* newNode = new Node(data, m_baseNode->prev, m_baseNode);
	if (m_baseNode->prev)
		m_baseNode->prev->next = newNode;
	else
		m_baseNode->next = newNode;

	m_baseNode->prev = newNode;
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

void CStringList::Clear() 
{
	auto curr = m_baseNode->next;
	while (curr != m_baseNode)
	{
		auto next = curr->next;
		delete curr;
		curr = next;
	}
	m_baseNode->next = m_baseNode->prev = m_baseNode;
	m_size = 0;
}

CStringList::iterator CStringList::begin() const
{
	return iterator(GetFirstNode());
}

CStringList::iterator CStringList::end() const
{
	return iterator(GetLastNode()->next);
}

CStringList::const_iterator CStringList::cbegin() const
{
	return const_iterator(GetFirstNode());
}

CStringList::const_iterator CStringList::cend() const
{
	return const_iterator(GetLastNode()->next);
}

CStringList::reverse_iterator CStringList::rbegin() const
{
	return make_reverse_iterator(end());
}

CStringList::reverse_iterator CStringList::rend() const
{
	return make_reverse_iterator(begin());
}

CStringList::const_reverse_iterator CStringList::crbegin() const
{
	return make_reverse_iterator(cend());
}

CStringList::const_reverse_iterator CStringList::crend() const
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
		m_baseNode->next = newNode;

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

	if (it.m_node == m_baseNode)
		throw invalid_argument("Sentry Node can not be deleted.");

	if (it.m_node->prev)
		it.m_node->prev->next = it.m_node->next;

	if (it.m_node->next)
		it.m_node->next->prev = it.m_node->prev;

	if (m_baseNode->next == it.m_node)
		m_baseNode->next = it.m_node->next;

	if (m_baseNode->prev == it.m_node)
		m_baseNode->prev = it.m_node->prev;

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

CStringList::Node* CStringList::GetFirstNode() const
{
	return m_baseNode->next;
}

CStringList::Node* CStringList::GetLastNode() const
{
	return m_baseNode->prev;
}