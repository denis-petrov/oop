#pragma once
#include "stdafx.h"
#include "Iterator.h"
#include "ReverseIterator.h"

class CMyString
{
public:
	CMyString();

	CMyString(const char* pString);
	CMyString(const char* pString, size_t length);
	CMyString(CMyString const& other);
	CMyString(std::string const& stlString);

	CMyString(CMyString&& other) noexcept;

	~CMyString();

	size_t GetLength() const;
	const char* GetStringData() const;
	CMyString SubString(size_t start, size_t length = SIZE_MAX) const;
	void Clear();

	CIterator begin();
	CIterator end();

	const CIterator cbegin();
	const CIterator cend();

	CReverseIterator rbegin();
	CReverseIterator rend();

	const CReverseIterator crbegin();
	const CReverseIterator crend();

public:
	CMyString& operator=(CMyString const& other);
	CMyString& operator=(CMyString&& other) noexcept;
	CMyString& operator+=(CMyString const& rhs);
	CMyString& operator+=(char ch);

	char& operator[](size_t index);
	const char& operator[](size_t index) const;

	friend std::istream& operator>>(std::istream& in, CMyString& str);

private:
	char* m_buffer;
	size_t m_length;

	char* Allocate(size_t size) const;
	char* CopyString(const char* str, size_t size);
};

CMyString operator+(CMyString lhs, CMyString const& rhs);

bool operator==(CMyString const& lhs, CMyString const& rhs);
bool operator!=(CMyString const& lhs, CMyString const& rhs);

bool operator>(CMyString const& lhs, CMyString const& rhs);
bool operator>=(CMyString const& lhs, CMyString const& rhs);
bool operator<(CMyString const& lhs, CMyString const& rhs);
bool operator<=(CMyString const& lhs, CMyString const& rhs);

std::ostream& operator<<(std::ostream& out, CMyString const& str);
