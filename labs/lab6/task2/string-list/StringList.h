#pragma once
#include "stdafx.h"

class CStringList
{
	struct Node
	{
		Node(const std::string& data, Node* prev, std::unique_ptr<Node>&& next)
			: data(data)
			, prev(prev)
			, next(std::move(next))
		{
		}
		std::string data;
		Node* prev;
		std::unique_ptr<Node> next;
	};

public:
	CStringList() = default;
	CStringList(CStringList const& other);
	CStringList(CStringList&& other) noexcept;
	~CStringList();

	size_t GetSize() const;
	bool IsEmpty() const;
	void Append(std::string const& data);

	std::string& GetBackElement();
	std::string const& GetBackElement() const;

	void Clear();

	friend std::ostream& operator<<(std::ostream& os, CStringList const& rhs);

private:
	size_t m_size = 0;
	std::unique_ptr<Node> m_firstNode;
	Node* m_lastNode = nullptr;
};