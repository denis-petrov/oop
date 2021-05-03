#include "StringList.h"
#include "stdafx.h"

using namespace std;

const string INEXIST_NODE = "Node does not exis";

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

CStringList::CStringList(CStringList&& rvalue) noexcept
{
	swap(m_firstNode, rvalue.m_firstNode);
	swap(m_lastNode, rvalue.m_lastNode);
	swap(m_size, rvalue.m_size);
}

CStringList::~CStringList()
{
	Clear();
}

void CStringList::PushFront(string const& data) 
{
	Node* newNode = new Node(data, nullptr, m_firstNode);
	if (m_firstNode)
		m_firstNode->prev = newNode;
	else
		m_lastNode = newNode;
	
	m_firstNode = newNode;
	
	if (!m_lastNode)
		m_firstNode = m_firstNode;
	++m_size;
}

void CStringList::PushBack(string const& data)
{
	Node* newNode = new Node(data, m_lastNode, nullptr);
	if (m_lastNode)
		m_lastNode->next = newNode;
	else
		m_firstNode = newNode;

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

CStringList::Node* CStringList::GetFirstNode() const
{
	assert(m_firstNode);
	return m_firstNode;
}

CStringList::Node* CStringList::GetLastNode() const
{
	assert(m_lastNode);
	return m_lastNode;
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
	for (size_t i = 0; i < rhs.GetSize(); i++)
	{
		os << currNode->data;
		currNode = currNode->next;
	}
	return os;
}

CStringList::iterator CStringList::begin()
{
	if (!m_firstNode)
		throw invalid_argument(INEXIST_NODE);
	return iterator(m_firstNode);
}

CStringList::const_iterator CStringList::end()
{
	if (!m_lastNode)
		throw invalid_argument(INEXIST_NODE);
	return iterator(m_lastNode->next);
}

CStringList::const_iterator CStringList::cbegin() const
{
	if (!m_firstNode)
		throw invalid_argument(INEXIST_NODE);
	return const_iterator(m_firstNode);
}

CStringList::const_iterator CStringList::cend() const
{
	if (!m_lastNode)
		throw invalid_argument(INEXIST_NODE);
	return const_iterator(m_lastNode->next);
}

CStringList::reverse_iterator CStringList::rbegin()
{
	if (!m_lastNode)
		throw invalid_argument(INEXIST_NODE);
	return make_reverse_iterator(CIterator<false>(m_lastNode));
}

CStringList::reverse_iterator CStringList::rend()
{
	if (!m_firstNode)
		throw invalid_argument(INEXIST_NODE);
	return make_reverse_iterator(CIterator<false>(m_firstNode->prev));
}//std::aligned_storege lab7 task2

CStringList::const_reverse_iterator CStringList::crbegin()
{
	if (!m_lastNode)
		throw invalid_argument(INEXIST_NODE);
	return make_reverse_iterator(CIterator<true>(m_lastNode));
}

CStringList::const_reverse_iterator CStringList::crend()
{
	if (!m_firstNode)
		throw invalid_argument(INEXIST_NODE);
	return make_reverse_iterator(CIterator<true>(m_firstNode->prev));
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
	if (it.m_node->prev)
		it.m_node->prev->next = it.m_node->next;

	if (it.m_node->next)
		it.m_node->next->prev = it.m_node->prev;

	if (m_firstNode == it.m_node)
		m_firstNode = it.m_node->next;

	if (m_lastNode == it.m_node)
		m_lastNode = it.m_node->prev;

	if (it.m_node)
	{
		m_size--;
		auto temp = it.m_node->next;
		delete it.m_node;
		it = temp;
	}
}

void CStringList::Delete(reverse_iterator& it)
{
	auto itDel = iterator(it.base().m_node);
	Delete(itDel);
	it.base() = itDel.m_node;
}