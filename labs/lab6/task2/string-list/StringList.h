#pragma once
#include "stdafx.h"

class CStringList
{
public:
	struct Node
	{
		Node(const std::string& data, Node* prev, Node* next)
			: data(data)
			, prev(prev)
			, next(next)
		{
		}
		std::string data;
		Node* prev;
		Node* next;
	};

	class CIterator : public std::iterator<std::forward_iterator_tag, Node*>
	{
		using iterator_category = std::forward_iterator_tag;
	    using difference_type = std::ptrdiff_t;
		using value_type = Node;
		using pointer = Node*;
		using reference = Node&;

		friend CStringList;
		CIterator(Node* node);

	public:
		CIterator() = default;
		reference operator*() const;
		pointer operator->();
		CIterator& operator++();
		CIterator& operator++(int);
		CIterator& operator--();
		CIterator& operator--(int);
		bool operator!=(CIterator const& other) const;

	private:
		Node* m_node = nullptr;
	};

	/*struct Iterator
	{
		using iterator_category = std::forward_iterator_tag;
		using value_type = Node;
		using pointer = Node*;
		using reference = Node&;

		Iterator(pointer node)
			: m_node(node)
		{
		}

		std::string* operator*() const { return &m_node->data; }
		std::string& operator->() { return m_node->data; }
		Iterator& operator++()
		{
			m_node = m_node->next;
			return *this;
		}
		Iterator operator++(int)
		{
			m_node = m_node->next;
			return *this;
		}
		Iterator& operator--()
		{
			m_node = m_node->prev;
			return *this;
		}
		Iterator operator--(int)
		{
			m_node = m_node->prev;
			return *this;
		}
		friend bool operator==(Iterator const& a, Iterator const& b) { return a.m_node == b.m_node; };
		friend bool operator!=(Iterator const& a, Iterator const& b) { return a.m_node != b.m_node; };

	private:
		pointer m_node = nullptr;
	};*/

public:
	CStringList() = default;
	CStringList(CStringList const& other);
	CStringList(CStringList&& other) noexcept;
	~CStringList();

	size_t GetSize() const;
	bool IsEmpty() const;
	void PushFront(std::string const& data);
	void PushBack(std::string const& data);

	std::string& GetBackElement();
	std::string const& GetBackElement() const;

	void Clear();

	friend std::ostream& operator<<(std::ostream& os, CStringList const& rhs);

	CIterator begin();
	CIterator end();

	CIterator cbegin() const;
	CIterator cend() const;

	std::reverse_iterator<CIterator> rbegin();
	std::reverse_iterator<CIterator> rend();

private:
	size_t m_size = 0;
	Node* m_firstNode = nullptr;
	Node* m_lastNode = nullptr;
};