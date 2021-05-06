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
		friend class CList;

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
			return &m_node->data.value();
		}

		reference operator*() const
		{
			assert(m_node);
			return m_node->data.value();
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
	CList() = default;
	CList(CList const& other)
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

	CList(CList&& rvalue) noexcept
	{
		swap(m_firstNode, rvalue.m_firstNode);
		swap(m_sentryNode, rvalue.m_sentryNode);
		swap(m_size, rvalue.m_size);
	}

	~CList()
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
		Node* newNode = new Node(std::make_optional(data), nullptr, m_firstNode);
		if (m_firstNode)
			m_firstNode->prev = newNode;
		else
			m_sentryNode->prev = newNode;

		m_firstNode = newNode;
		++m_size;
	}

	void PushBack(T const& data)
	{
		Node* newNode = new Node(std::make_optional(data), m_sentryNode->prev, m_sentryNode);
		if (m_sentryNode->prev)
			m_sentryNode->prev->next = newNode;
		else
			m_firstNode = newNode;

		m_sentryNode->prev = newNode;
		++m_size;
	}

	T& GetBackElement()
	{
		assert(m_sentryNode->prev);
		return m_sentryNode->prev->data.has_value() ? m_sentryNode->prev->data.value() : nullptr;
	}

	T const& GetBackElement() const
	{
		assert(m_sentryNode->prev);
		return m_sentryNode->prev->data.has_value() ? m_sentryNode->prev->data.value() : nullptr;
	}

	T& GetFirstElement()
	{
		assert(m_firstNode);
		return m_firstNode->data.has_value() ? m_firstNode->data.value() : nullptr;
	}
	T const& GetFirstElement() const
	{
		assert(m_firstNode);
		return m_firstNode->data.has_value() ? m_firstNode->data.value() : nullptr;
	}

	void Clear()
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

	friend std::ostream& operator<<(std::ostream& os, CList const& rhs)
	{
		auto currNode = rhs.m_firstNode;
		for (size_t i = 0; i < rhs.GetSize(); i++)
		{
			os << std::to_string(currNode->data.value());
			currNode = currNode->next;
		}
		return os;
	}

	using iterator = CIterator<false>;
	using const_iterator = CIterator<true>;

	using reverse_iterator = std::reverse_iterator<CIterator<false>>;
	using const_reverse_iterator = std::reverse_iterator<CIterator<true>>;

	iterator begin()
	{
		return iterator(m_firstNode);
	}
	iterator end()
	{
		return iterator(m_sentryNode);
	}

	const_iterator cbegin() const
	{
		return const_iterator(m_firstNode);
	}
	const_iterator cend() const
	{
		return const_iterator(m_sentryNode);
	}

	reverse_iterator rbegin()
	{
		return std::make_reverse_iterator(end());
	}
	reverse_iterator rend()
	{
		return std::make_reverse_iterator(begin());
	}

	const_reverse_iterator crbegin()
	{
		return std::make_reverse_iterator(cend());
	}
	const_reverse_iterator crend()
	{
		return std::make_reverse_iterator(cbegin());
	}

	void Insert(iterator const& it, T const& data)
	{
		if (!it.m_node)
		{
			PushBack(data);
			return;
		}

		Node* newNode = new Node(std::make_optional(data), it.m_node->prev, it.m_node);
		if (it.m_node->prev)
			it.m_node->prev->next = newNode;
		else
			m_firstNode = newNode;

		it.m_node->prev = newNode;
		m_size++;
	}
	void Insert(reverse_iterator const& it, T const& data)
	{
		Insert(it.base(), data);
	}

	void Delete(iterator& it)
	{
		if (!it.m_node)
			throw std::invalid_argument("Node does not exist.");

		if (it.m_node == m_sentryNode)
			throw std::invalid_argument("Sentry Node can not be deleted.");

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
	void Delete(reverse_iterator& it)
	{
		if (!it.base().m_node || !it.base().m_node->prev)
			throw std::invalid_argument("Node does not exist.");
		auto itDel = --it.base();
		Delete(itDel);
		it.base() = itDel.m_node;
	}

private:
	size_t m_size = 0;
	Node* m_firstNode = nullptr;
	Node* m_sentryNode = new Node(nullptr, nullptr, nullptr);
};
