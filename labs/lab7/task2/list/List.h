#pragma once
#include "stdafx.h"

template <class T>
class CList
{
public:
	struct Node
	{
		Node(T const& newData, Node* newPrev, Node* newNext)
			: data(std::make_optional<T>(newData))
			, prev(newPrev)
			, next(newNext)
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
			return *m_node->data.value();
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
			return (lhs.m_node == rhs.m_node);
		}

		friend bool operator!=(Iterator const& lhs, Iterator const& rhs)
		{
			return !(lhs == rhs);
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
	CList()
		: m_size(0)
	{
		m_baseNode = new Node(nullptr, nullptr, nullptr);
		m_baseNode->prev = m_baseNode->next = m_baseNode;
	}

	using iterator = CIterator<false>;
	using const_iterator = CIterator<true>;

	using reverse_iterator = std::reverse_iterator<CIterator<false>>;
	using const_reverse_iterator = std::reverse_iterator<CIterator<true>>;

	iterator begin()
	{
		return iterator(GetFirstNode());
	}

	iterator end()
	{
		return iterator(GetLastNode()->next);
	}

	const_iterator cbegin() const
	{
		return const_iterator(GetFirstNode());
	}

	const_iterator cend() const
	{
		return const_iterator(GetLastNode()->next);
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

	CList(CList<T> const& other)
	{
		for (T& currNode : other)
		{
			try
			{
				PushBack(currNode->data.value());
			}
			catch (...)
			{
				Clear();
				delete m_baseNode;
				throw;
			}
		}
	}

	CList(CList<T>&& rvalue) noexcept
	{
		std::swap(m_baseNode, rvalue.m_baseNode);
		std::swap(m_size, rvalue.m_size);
	}

	~CList() noexcept
	{
		Clear();
		delete m_baseNode;
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
		Node* newNode = new Node(data, nullptr, m_baseNode->next);
		if (m_baseNode->next)
			m_baseNode->next->prev = newNode;
		else
			m_baseNode->prev = newNode;

		m_baseNode->next = newNode;
		++m_size;
	}

	void PushBack(T const& data)
	{
		Node* newNode = new Node(data, m_baseNode->prev, m_baseNode);
		if (m_baseNode->prev)
			m_baseNode->prev->next = newNode;
		else
			m_baseNode->next = newNode;

		m_baseNode->prev = newNode;
		++m_size;
	}

	void Clear()
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

	void Insert(iterator const& it, T const& data)
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

	void Insert(reverse_iterator const& it, T const& data)
	{
		Insert(it.base(), data);
	}

	void Delete(iterator& it)
	{
		if (!it.m_node)
			throw std::invalid_argument("Node does not exist.");

		if (it.m_node == m_baseNode)
			throw std::invalid_argument("Sentry Node can not be deleted.");

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

	void Delete(reverse_iterator& it)
	{
		if (!it.base().m_node || !it.base().m_node->prev)
			throw std::invalid_argument("Node does not exist.");
		auto itDel = --it.base();
		Delete(itDel);
		it.base() = itDel.m_node;
	}

private:
	size_t m_size;
	Node* m_baseNode;

	Node* GetFirstNode() const
	{
		return m_baseNode->next;
	}

	Node* GetLastNode() const
	{
		return m_baseNode->prev;
	}
};


