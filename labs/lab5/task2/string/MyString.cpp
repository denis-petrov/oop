#include "stdafx.h"
#include "MyString.h"

using namespace std;

CMyString::CMyString()
{
	length_ = 0;
	buffer_ = new char[length_ + 1];
	buffer_[length_] = '\0';
}

CMyString::CMyString(const char* pString)
{
	length_ = strlen(pString);
	buffer_ = new char[length_ + 1];
	memcpy(buffer_, pString, length_);
	buffer_[length_] = '\0';
}

CMyString::CMyString(const char* pString, size_t length)
{
	length_ = length;
	buffer_ = new char[length_ + 1];
	memcpy(buffer_, pString, length_);
	buffer_[length_] = '\0';
}

CMyString::CMyString(CMyString const& other) // tests
{
	length_ = other.GetLength();
	memcpy(buffer_, other.GetStringData(), length_ + 1);
}

CMyString::CMyString(CMyString&& other) noexcept // tests
{
	length_ = other.length_;
	buffer_ = other.buffer_;
	other.buffer_ = nullptr;
}

CMyString::CMyString(string const& stlString) // tests
{
	length_ = stlString.size();
	if (stlString[length_] == '\0')
	{
		buffer_ = new char[length_];
		memcpy(buffer_, stlString.c_str(), length_);
	}
	else
	{
		buffer_ = new char[length_ + 1];
		memcpy(buffer_, stlString.c_str(), length_);
		buffer_[length_] = '\0';
	}
}

CMyString ::~CMyString()
{
	delete[] buffer_;
}

size_t CMyString::GetLength() const
{
	return length_;
}

const char* CMyString::GetStringData() const
{
	return buffer_;
}

CMyString CMyString::SubString(size_t start, size_t length = SIZE_MAX) const // Tests
{
	if (length > length_)
		throw invalid_argument("Access denied, because length is more than object length.");

	string res;
	for (size_t i = 0; i < length; i++)
		res[i] = buffer_[i];

	return CMyString(res);
}

void CMyString::Clear() // Tests
{
	length_ = 0;
	delete[] buffer_;
	buffer_ = new char[length_ + 1];
	buffer_[length_] = '\0';
}