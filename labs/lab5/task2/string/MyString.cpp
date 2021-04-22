#include "stdafx.h"
#include "MyString.h"

using namespace std;

CMyString::CMyString()
{
	m_length = 0;
	m_buffer = DefineNewArray(m_length);
}

CMyString::CMyString(const char* pString)
{
	m_length = strlen(pString);
	m_buffer = DefineNewArray(m_length);
	strcpy(m_buffer, pString);
}

CMyString::CMyString(const char* pString, size_t length)
{
	m_length = length;
	m_buffer = DefineNewArray(m_length);
	strcpy(m_buffer, pString);
}

CMyString::CMyString(CMyString const& other)
{
	m_length = other.GetLength();
	m_buffer = DefineNewArray(m_length);
	strcpy(m_buffer, other.GetStringData());
}

CMyString::CMyString(string const& stlString)
{
	m_length = stlString.size();
	m_buffer = DefineNewArray(m_length);
	strcpy(m_buffer, stlString.c_str());
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
	m_buffer = DefineNewArray(m_length);
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
	char* temp = DefineNewArray(newLength);
	strcpy(temp, m_buffer);
	strcat(temp, rhs.GetStringData());

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

char& CMyString::operator[](const size_t index)
{
	if (index >= m_length)
		throw out_of_range("Not correct index.");

	return m_buffer[index];
}

const char& CMyString::operator[](const size_t index) const
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

char* CMyString::DefineNewArray(const size_t size) const
{
	try
	{
		char* temp = new char[size + 1];
		temp[size] = '\0';
		return temp;
	}
	catch (const bad_alloc&)
	{
		return nullptr;
	}
}

CIterator CMyString::begin()
{
	return CIterator(&m_buffer[0]);
}

CIterator CMyString::end()
{
	return CIterator(&m_buffer[m_length]);
}

const CIterator CMyString::cbegin()
{
	const CIterator res(&m_buffer[0]);
	return res;
}

const CIterator CMyString::cend()
{
	const CIterator res(&m_buffer[m_length]);
	return res;
}


CReverseIterator CMyString::rbegin()
{
	return CReverseIterator(&m_buffer[m_length - 1]);
}

CReverseIterator CMyString::rend()
{
	return CReverseIterator(&m_buffer[-1]);
}

const CReverseIterator CMyString::crbegin()
{
	const CReverseIterator res(&m_buffer[m_length - 1]);
	return res;
}

const CReverseIterator CMyString::crend()
{
	const CReverseIterator res(&m_buffer[-1]);
	return res;
}