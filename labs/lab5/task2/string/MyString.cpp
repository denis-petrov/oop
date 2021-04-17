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

CMyString::CMyString(CMyString const& other)
{
	length_ = other.GetLength();
	buffer_ = new char[length_ + 1];
	memcpy(buffer_, other.GetStringData(), length_ + 1);
}

CMyString::CMyString(string const& stlString)
{
	length_ = stlString.size();
	buffer_ = new char[length_ + 1];

	if (stlString[length_] == '\0')
	{
		memcpy(buffer_, stlString.c_str(), length_ + 1);
	}
	else
	{
		memcpy(buffer_, stlString.c_str(), length_);
		buffer_[length_] = '\0';
	}
}

CMyString::CMyString(CMyString&& other) noexcept
{
	length_ = other.length_;
	buffer_ = other.buffer_;
	other.buffer_ = nullptr;
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

CMyString CMyString::SubString(size_t start, size_t length) const
{
	if (length > length_)
	{
		throw invalid_argument("Access denied, because length is more than object length.");
	}

	string res;
	for (size_t i = start; i < length; i++)
	{
		res.push_back(buffer_[i]);
	}

	return CMyString(res);
}

void CMyString::Clear()
{
	length_ = 0;
	delete[] buffer_;
	buffer_ = new char[length_ + 1];
	buffer_[length_] = '\0';
}


/* OPERATIONS */

CMyString& CMyString::operator=(CMyString const& other)
{
	if (addressof(*this) == addressof(other))
		return *this;

	delete[] buffer_;

	length_ = other.length_;
	buffer_ = new char[length_ + 1];
	memcpy(buffer_, other.buffer_, length_ + 1);

	return *this;
}

CMyString& CMyString::operator=(CMyString&& other) noexcept
{
	if (addressof(*this) == addressof(other))
		return *this;

	delete[] buffer_;

	buffer_ = other.buffer_;
	length_ = other.length_;

	other.buffer_ = nullptr;

	return *this;
}

CMyString& CMyString::operator+=(CMyString const& rhs)
{
	auto newLength = length_ + rhs.GetLength();
	char* temp = new char[newLength + 1];
	strcpy(temp, buffer_);
	strcat(temp, rhs.GetStringData());

	delete[] buffer_;
	length_ = newLength;
	buffer_ = temp;
	buffer_[length_] = '\0';

	temp = nullptr;

	return *this;
}

CMyString const operator+(CMyString lhs, CMyString const& rhs)
{
	return lhs += rhs;
}

bool operator==(CMyString const& lhs, CMyString const& rhs)
{
	if (lhs.GetLength() != rhs.GetLength())
	{
		return false;
	}

	auto lhsBuffer = lhs.GetStringData();
	auto rhsBuffer = rhs.GetStringData();
	for (size_t i = 0; i < lhs.GetLength(); i++)
	{
		if (lhsBuffer[i] != rhsBuffer[i])
		{
			return false;
		}
	}
	return true;
}

bool operator!=(CMyString const& lhs, CMyString const& rhs)
{
	return !(lhs == rhs);
}

bool operator>(CMyString const& lhs, CMyString const& rhs) 
{
	if (lhs.GetLength() > rhs.GetLength())
		return true;
	
	if (lhs.GetLength() < rhs.GetLength())
		return false;

	auto lhsBuffer = lhs.GetStringData();
	auto rhsBuffer = rhs.GetStringData();
	for (size_t i = 0; i < lhs.GetLength(); i++)
	{
		if (lhsBuffer[i] > rhsBuffer[i])
			return true;
		if (lhsBuffer[i] < rhsBuffer[i])
			return false;
	}
	return false;
}

bool operator>=(CMyString const& lhs, CMyString const& rhs)
{
	return ((lhs > rhs) || (lhs == rhs));
}

bool operator<(CMyString const& lhs, CMyString const& rhs)
{
	return (!(lhs >= rhs));
}

bool operator<=(CMyString const& lhs, CMyString const& rhs)
{
	return (!(lhs > rhs));
}