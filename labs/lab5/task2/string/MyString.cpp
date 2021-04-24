#include "stdafx.h"
#include "MyString.h"

using namespace std;

CMyString::CMyString()
{
	m_length = 0;
	m_buffer = Allocate(m_length);
	m_buffer[m_length] = '\0';
}

CMyString::CMyString(const char* pString)
{
	m_buffer = CopyString(pString, strlen(pString));
}

CMyString::CMyString(const char* pString, size_t length)
{
	m_buffer = CopyString(pString, length);
}

CMyString::CMyString(CMyString const& other)
{
	m_buffer = CopyString(other.GetStringData(), other.GetLength());
}

CMyString::CMyString(string const& stlString)
{
	m_buffer = CopyString(stlString.c_str(), stlString.size());
}

CMyString::CMyString(CMyString&& other) noexcept
{
	m_length = other.m_length;
	m_buffer = other.m_buffer;
	other.m_buffer = nullptr;
	other.m_length = 0;
}

CMyString::~CMyString()
{
	delete[] m_buffer;
}

size_t CMyString::GetLength() const
{
	return m_length;
}

const char* CMyString::GetStringData() const
{
	static const char zeroLengthString[] = "";
	return m_buffer ? m_buffer : zeroLengthString;
}

CMyString CMyString::SubString(size_t start, size_t length) const
{
	if (length > m_length || start > length)
		throw invalid_argument("Access denied, because length is more than object length.");

	string res;
	for (size_t i = start; i < length; i++)
	{
		res.push_back(m_buffer[i]);
	}

	return CMyString(res);
}

void CMyString::Clear()
{
	m_length = 0;
	delete[] m_buffer;
	m_buffer = Allocate(m_length);
}

/* OPERATIONS */

CMyString& CMyString::operator=(CMyString const& other)
{
	if (this != addressof(other))
	{
		CMyString tmpCopy(other);
		swap(m_buffer, tmpCopy.m_buffer);
		swap(m_length, tmpCopy.m_length);
	}

	return *this;
}

CMyString& CMyString::operator=(CMyString&& other) noexcept
{
	if (this != &other)
	{
		delete[] m_buffer;
		m_buffer = other.m_buffer;
		m_length = other.m_length;
		other.m_buffer = nullptr;
		other.m_length = 0;
	}

	return *this;
}

CMyString& CMyString::operator+=(CMyString const& rhs)
{
	auto newLength = m_length + rhs.GetLength();
	char* temp = Allocate(newLength);
	memcpy(temp, m_buffer, m_length);
	memcpy(temp + m_length, rhs.GetStringData(), rhs.GetLength());

	delete[] m_buffer;
	m_buffer = temp;
	m_length = newLength;
	temp = nullptr;

	return *this;
}

CMyString& CMyString::operator+=(char ch)
{
	return *this += string(1, ch);
}


CMyString operator+(CMyString lhs, CMyString const& rhs)
{
	return lhs += rhs;
}

bool operator==(CMyString const& lhs, CMyString const& rhs)
{
	if (lhs.GetLength() != rhs.GetLength())
		return false;

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
	size_t minSize = (lhs.GetLength() > rhs.GetLength()) ? rhs.GetLength() : lhs.GetLength();

	auto lhsBuffer = lhs.GetStringData();
	auto rhsBuffer = rhs.GetStringData();
	for (size_t i = 0; i < minSize; i++)
	{
		if (lhsBuffer[i] > rhsBuffer[i])
		{
			return true;
		}
		if (lhsBuffer[i] < rhsBuffer[i])
		{
			return false;
		}
	}
	return (lhs.GetLength() > rhs.GetLength());
}

bool operator>=(CMyString const& lhs, CMyString const& rhs)
{
	return ((lhs > rhs) || (lhs == rhs));
}

bool operator<(CMyString const& lhs, CMyString const& rhs)
{
	return !(lhs >= rhs);
}

bool operator<=(CMyString const& lhs, CMyString const& rhs)
{
	return !(lhs > rhs);
}

char& CMyString::operator[](size_t index)
{
	if (index >= m_length)
		throw out_of_range("Not correct index.");

	return m_buffer[index];
}

const char& CMyString::operator[](size_t index) const
{
	if (index >= m_length)
		throw out_of_range("Not correct index.");

	return m_buffer[index];
}

ostream& operator<<(ostream& out, CMyString const& str)
{
	return out << str.GetStringData();
}

istream& operator>>(istream& in, CMyString& str)
{
	char ch;
	while (in.get(ch) && ch != '\n' && ch != ' ')
	{
		str += ch;
	}

	return in;
}

char* CMyString::Allocate(size_t size) const
{
	try
	{
		return new char[size + 1];
	}
	catch (const bad_alloc&)
	{
		return nullptr;
	}
}

char* CMyString::CopyString(const char* str, size_t size) 
{
	auto temp = Allocate(size);
	memcpy(temp, str, size);
	temp[size] = '\0';
	m_length = size;
	return temp;
}

CIterator CMyString::begin()
{
	return CIterator(&m_buffer[0]);
}

CIterator CMyString::end()
{
	return CIterator(&m_buffer[m_length]);
}

const CConstIterator CMyString::cbegin()
{
	const CConstIterator res(&m_buffer[0]);
	return res;
}

const CConstIterator CMyString::cend()
{
	const CConstIterator res(&m_buffer[m_length]);
	return res;
}


CReverseIterator CMyString::rbegin()
{
	return CReverseIterator(&m_buffer[m_length - 1]);
	//return CReverseIterator(&m_buffer[0]);
}

CReverseIterator CMyString::rend()
{
	return CReverseIterator(&m_buffer[-1]);
	//return CReverseIterator(&m_buffer[m_length]);
}

const CConstReverseIterator CMyString::crbegin()
{
	const CConstReverseIterator res(&m_buffer[m_length - 1]);
	return res;
}

const CConstReverseIterator CMyString::crend()
{
	const CConstReverseIterator res(&m_buffer[-1]);
	return res;
}