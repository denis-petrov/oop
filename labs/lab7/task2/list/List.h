#pragma once
#include "stdafx.h"

template <class T>
class CList
{
public:
	struct Node
	{
		Node* prev;
		std::unique_ptr<T> data;
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

		pointer operator->() const
		{
			assert(m_node);
			return m_node->data.get();
		}

		reference operator*() const
		{
			assert(m_node);
			return *m_node->data;
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
			return (lhs.m_node != rhs.m_node);
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
		m_baseNode = new Node;
		m_baseNode->prev = m_baseNode->next = m_baseNode;
		m_baseNode->data = nullptr;
	}

	CList(CList<T> const& other)
		: CList()
	{
		try
		{
			for (const auto& curr : other)
			{
				PushBack(curr);
			}
		}
		catch (...)
		{
			Clear();
			delete m_baseNode;
			throw;
		}
	}

	CList(CList<T>&& rvalue) noexcept
		: CList()
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
		Insert(begin(), data);
	}

	void PushBack(T const& data)
	{
		Insert(end(), data);
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
	
	using iterator = CIterator<false>;
	using const_iterator = CIterator<true>;

	using reverse_iterator = std::reverse_iterator<CIterator<false>>;
	using const_reverse_iterator = std::reverse_iterator<CIterator<true>>;

	iterator begin() const
	{
		return iterator(GetFirstNode());
	}

	iterator end() const
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

	reverse_iterator rbegin() const
	{
		return std::make_reverse_iterator(end());
	}

	reverse_iterator rend() const
	{
		return std::make_reverse_iterator(begin());
	}

	const_reverse_iterator crbegin() const
	{
		return std::make_reverse_iterator(cend());
	}

	const_reverse_iterator crend() const
	{
		return std::make_reverse_iterator(cbegin());
	}

	void Insert(const_iterator const& it, T const& data)
	{
		Node* nodeBeforeNewNode = it.m_node->prev;
		Node* nodeAfterNewNode = it.m_node;

		Node* newNode = new Node{ nodeBeforeNewNode, std::make_unique<T>(data),	nodeAfterNewNode };
		nodeBeforeNewNode->next = nodeAfterNewNode->prev = newNode;
		++m_size;
	}

	void Delete(const const_iterator& it)
	{
		if (!it.m_node)
			throw std::invalid_argument("Node does not exist.");

		if (it.m_node == m_baseNode)
			throw std::invalid_argument("Sentry Node can not be deleted.");

		Node* prevNode = it.m_node->prev;
		Node* nodeForDeleting = it.m_node;
		Node* nextNode = it.m_node->next;
		prevNode->next = nextNode;
		nextNode->prev = prevNode;

		delete nodeForDeleting;

		--m_size;
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


