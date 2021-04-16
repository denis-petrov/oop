#pragma once

class CMyString
{
public:
	CMyString();

	CMyString(const char* pString);

	CMyString(const char* pString, size_t length);

	CMyString(CMyString const& other);

	CMyString(CMyString&& other) noexcept;

	CMyString(std::string const& stlString);

	~CMyString();

	size_t GetLength() const;
	const char* GetStringData() const;
	CMyString SubString(size_t start, size_t length = SIZE_MAX) const;

	void Clear();
private:
	char* buffer_;
	size_t length_;
};
