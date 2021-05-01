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
		using iterator_category = std::random_access_iterator_tag;

		CIterator() = default;
		CIterator(const CIterator<false>& other)
			: m_node(other.m_node)
		{
		}

		Node* GetNode() 
		{
			return m_node;
		}

		pointer operator->() 
		{
			return &m_node->data; 
		}

		reference operator*() const 
		{
			return m_node->data;
		}

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
		
		Iterator operator+(difference_type offset) const
		{
			Iterator temp(m_node);
			temp += offset;
			return temp;
		}

		friend Iterator operator+(difference_type offset, Iterator const& it)
		{
			return it + offset;
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

		Iterator& operator+=(difference_type offset)
		{
			for (difference_type i = 0; i < std::abs(offset); i++)
			{
				if (m_node == nullptr)
					throw std::invalid_argument("Not correct right side operand in += operation.");
				m_node = (offset > 0) ? m_node->next : m_node->prev;
			}
			return *this;
		}

		Iterator& operator-=(difference_type offset)
		{
			return (*this += -offset);
		}

		Iterator operator-(difference_type offset) const
		{
			Iterator temp(m_node);
			temp -= offset;
			return temp;
		}

		friend Iterator operator-(difference_type offset, Iterator const& it)
		{
			return it + (-offset);
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
	CStringList(CStringList const& other);
	CStringList(CStringList&& rvalue) noexcept;
	~CStringList();

	size_t GetSize() const;
	bool IsEmpty() const;
	void PushFront(std::string const& data);
	void PushBack(std::string const& data);

	Node* GetFirstNode() const;
	Node* GetLastNode() const;

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
	const_iterator end();

	const_iterator cbegin() const;
	const_iterator cend() const;

	reverse_iterator rbegin();
	reverse_iterator rend();

	const_reverse_iterator crbegin(); 
	const_reverse_iterator crend();

	void Insert(iterator const& it, std::string const& data);
	void Insert(const_iterator const& it, std::string const& data);
	void Insert(reverse_iterator const& it, std::string const& data);
	void Insert(const_reverse_iterator const& it, std::string const& data);

	void Delete(iterator& it);
	void Delete(const_iterator& it);
	void Delete(reverse_iterator& it);
	void Delete(const_reverse_iterator& it);

private:
	size_t m_size = 0;
	Node* m_firstNode = nullptr;
	Node* m_lastNode = nullptr;
};