#pragma once
#include "stdafx.h"
//#include "Iterator.h"

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

		pointer& operator->() 
		{
			return &m_node->data; 
		}

		reference& operator*() const 
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

		Iterator& operator+=(size_t offset)
		{
			for (size_t i = 0; i < offset; i++)
			{
				if (m_node == nullptr)
					throw std::invalid_argument("Not correct right side operand in += operation.");
				m_node = m_node->next;
			}
			return *this;
		}

		Iterator& operator-=(size_t offset)
		{
			for (size_t i = 0; i < offset; i++)
			{
				if (m_node == nullptr)
					throw std::invalid_argument("Not correct right side operand in -= operation.");
				m_node = m_node->prev;
			}
			return *this;
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

	/*CIterator<false> begin();
	CIterator<false> end();

	CIterator<true> cbegin() const;
	CIterator<true> cend() const;

	std::reverse_iterator<CIterator<false>> rbegin();
	std::reverse_iterator<CIterator<false>> rend();*/

	using iterator = CIterator<false>;
	using const_iterator = CIterator<true>;

	using reverse_iterator = std::reverse_iterator<CIterator<false>>;
	using const_reverse_iterator = std::reverse_iterator<CIterator<true>>;

	iterator begin()
	{
		return { m_firstNode };
	}

	const_iterator end()
	{
		return { m_lastNode->next };
	}

	const_iterator cbegin() const
	{
		return { m_firstNode };
	}

	const_iterator cend() const
	{
		return { m_lastNode->next };
	}

	reverse_iterator rbegin() 
	{
		return std::make_reverse_iterator(begin());
	}

	reverse_iterator rend()
	{
		return std::make_reverse_iterator(CIterator<false>(m_lastNode->next));
	}

	/*const_reverse_iterator crbegin() 
	{
		return std::make_reverse_iterator(cbegin());
	}

	const_reverse_iterator crend()
	{
		return std::make_reverse_iterator(cend());
	}*/

private:
	size_t m_size = 0;
	Node* m_firstNode = nullptr;
	Node* m_lastNode = nullptr;
};