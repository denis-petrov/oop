#pragma once
#include "stdafx.h"

template <class T>
class CList
{
public:
	struct Node
	{
		Node(const T& data, Node* prev, Node* next)
			: data(data)
			, prev(prev)
			, next(next)
		{
		}
		std::optional<T> data;
		Node* prev;
		Node* next;
	};

	template <bool IsConst>
	class CIterator
	{
		friend class CIterator<true>;
		friend class CStringList;

	public:
		using Iterator = CIterator<IsConst>;
		using value_type = std::conditional_t<IsConst, const T, T>;
		using reference = value_type&;
		using pointer = value_type*;
		using difference_type = ptrdiff_t;
		using iterator_category = std::bidirectional_iterator_tag;

		CIterator() = default;
		CIterator(const CIterator<false>& other)
			: m_node(other.m_node)
		{
		}

		pointer operator->()
		{
			assert(m_node);
			return &m_node->data;
		}

		reference operator*() const
		{
			assert(m_node);
			return m_node->data;
		}

		Iterator& operator++()
		{
			assert(m_node->next);
			m_node = m_node->next;
			return *this;
		}

		Iterator operator++(int)
		{
			assert(m_node->next);
			return Iterator(m_node->next);
		}

		Iterator& operator--()
		{
			assert(m_node->prev);
			m_node = m_node->prev;
			return *this;
		}

		Iterator operator--(int)
		{
			assert(m_node->prev);
			return Iterator(m_node->prev);
		}

		friend bool operator==(Iterator const& lhs, Iterator const& rhs)
		{
			return lhs.m_node == rhs.m_node;
		}

		friend bool operator!=(Iterator const& lhs, Iterator const& rhs)
		{
			return lhs.m_node != rhs.m_node;
		}

	public:
		CIterator(Node* node)
			: m_node(node)
		{
		}

	protected:
		Node* m_node = nullptr;
	};

public:
	CStringList() = default;
	CStringList(CStringList const& other)
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
	CStringList(CStringList&& rvalue) noexcept
	{
		swap(m_firstNode, rvalue.m_firstNode);
		swap(m_sentryNode, rvalue.m_sentryNode);
		swap(m_size, rvalue.m_size);
	}
	~CStringList()
	{
		Clear();
		delete m_sentryNode;
	}

	size_t GetSize() const
	{
		return m_size;
	}
	bool IsEmpty() const
	{
		return (m_size == 0);
	}
	void PushFront(T const& data)
	{
		Node* newNode = new Node(data, nullptr, m_firstNode);
		if (m_firstNode)
			m_firstNode->prev = newNode;
		else
			m_sentryNode->prev = newNode;

		m_firstNode = newNode;
		++m_size;
	}
	void PushBack(T const& data)
	{
		Node* newNode = new Node(data, m_sentryNode->prev, m_sentryNode);
		if (m_sentryNode->prev)
			m_sentryNode->prev->next = newNode;
		else
			m_firstNode = newNode;

		m_sentryNode->prev = newNode;
		++m_size;
	}

	Node* GetFirstNode() const
	{
		assert(m_firstNode);
		return m_firstNode;
	}
	Node* GetLastNode() const
	{
		assert(m_lastNode);
		return m_lastNode;
	}

	T& GetBackElement();
	T const& GetBackElement() const;

	T& GetFirstElement();
	T const& GetFirstElement() const;

	void Clear();

	friend std::ostream& operator<<(std::ostream& os, CStringList const& rhs);

	using iterator = CIterator<false>;
	using const_iterator = CIterator<true>;

	using reverse_iterator = std::reverse_iterator<CIterator<false>>;
	using const_reverse_iterator = std::reverse_iterator<CIterator<true>>;

	iterator begin();
	iterator end();

	const_iterator cbegin() const;
	const_iterator cend() const;

	reverse_iterator rbegin();
	reverse_iterator rend();

	const_reverse_iterator crbegin();
	const_reverse_iterator crend();

	void Insert(iterator const& it, T const& data);
	void Insert(reverse_iterator const& it, T const& data);

	void Delete(iterator& it);
	void Delete(reverse_iterator& it);

private:
	size_t m_size = 0;
	Node* m_firstNode = nullptr;
	Node* m_lastNode = nullptr;
	Node* m_sentryNode = new Node(nullptr, m_lastNode, nullptr);
};
