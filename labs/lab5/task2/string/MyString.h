#pragma once
#include "stdafx.h"

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

public:
	CMyString& operator=(CMyString const& other);
	CMyString& operator=(CMyString&& other) noexcept;
	CMyString& operator+=(CMyString const& rhs);
	
	char& operator[](const size_t index);
	const char& operator[](const size_t index) const;

	friend std::istream& operator>>(std::istream& in, CMyString& str);

private:
	char* buffer_;
	size_t length_;
};

CMyString const operator+(CMyString lhs, CMyString const& rhs);

bool operator==(CMyString const& lhs, CMyString const& rhs);
bool operator!=(CMyString const& lhs, CMyString const& rhs);

bool operator>(CMyString const& lhs, CMyString const& rhs);
bool operator>=(CMyString const& lhs, CMyString const& rhs);
bool operator<(CMyString const& lhs, CMyString const& rhs);
bool operator<=(CMyString const& lhs, CMyString const& rhs);

std::ostream& operator<<(std::ostream& out, CMyString const& str);