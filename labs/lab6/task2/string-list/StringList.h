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

	template <bool IsConst>
	class CIterator
	{
		friend class CIterator<true>;
		friend class CStringList;

	public:
		using Iterator = CIterator<IsConst>;
		using value_type = std::conditional_t<IsConst, const std::string, std::string>;
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
	CStringList() = default;
	CStringList(CStringList const& other);
	CStringList(CStringList&& rvalue) noexcept;
	~CStringList() noexcept;

	size_t GetSize() const;
	bool IsEmpty() const;
	void PushFront(std::string const& data);
	void PushBack(std::string const& data);

	std::string& GetBackElement();
	std::string const& GetBackElement() const;

	std::string& GetFirstElement();
	std::string const& GetFirstElement() const;

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

	void Insert(iterator const& it, std::string const& data);
	void Insert(reverse_iterator const& it, std::string const& data);

	void Delete(iterator& it);
	void Delete(reverse_iterator& it);

private:
	size_t m_size = 0;
	Node* m_firstNode = nullptr;
	Node* m_sentryNode = new Node("", nullptr, nullptr);
};