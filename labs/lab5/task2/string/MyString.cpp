#include "stdafx.h"
#include "MyString.h"

using namespace std;

CMyString::CMyString()
{
	m_length = 0;
	m_buffer = new char[m_length + 1];
	m_buffer[m_length] = '\0';
}

CMyString::CMyString(const char* pString)
{
	m_length = strlen(pString);
	m_buffer = new char[m_length + 1];
	memcpy(m_buffer, pString, m_length);
	m_buffer[m_length] = '\0';
}

CMyString::CMyString(const char* pString, size_t length)
{
	m_length = length;
	m_buffer = new char[m_length + 1];
	memcpy(m_buffer, pString, m_length);
	m_buffer[m_length] = '\0';
}

CMyString::CMyString(CMyString const& other)
{
	m_length = other.GetLength();
	m_buffer = new char[m_length + 1];
	memcpy(m_buffer, other.GetStringData(), m_length + 1);
}

CMyString::CMyString(string const& stlString)
{
	m_length = stlString.size();
	m_buffer = new char[m_length + 1];

	if (stlString[m_length] == '\0')
	{
		memcpy(m_buffer, stlString.c_str(), m_length + 1);
	}
	else
	{
		memcpy(m_buffer, stlString.c_str(), m_length);
		m_buffer[m_length] = '\0';
	}
}

CMyString::CMyString(CMyString&& other) noexcept
{
	m_length = other.m_length;
	m_buffer = other.m_buffer;
	other.Clear();
}

CMyString ::~CMyString()
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
		throw invalid_argument("Bad access, not correct parametrs.");

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
	m_buffer = new char[m_length + 1];
	m_buffer[m_length] = '\0';
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
{//TODO
	auto defaultLength = m_length;
	auto defaultBuffer = m_buffer;
	try
	{
		auto newLength = m_length + rhs.GetLength();
		char* temp = new char[newLength + 2];

		memcpy(temp, m_buffer, m_length + 1);
		memcpy(temp + m_length + 1, rhs.m_buffer, rhs.GetLength() + 1);

		m_length = newLength;
		delete[] m_buffer;
		m_buffer = temp;
		m_buffer[m_length] = '\0';
		temp = nullptr;
	}
	catch (const exception&)
	{
		m_buffer = defaultBuffer;
		m_length = defaultLength;
	}
	return *this;
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
		str += CMyString(string(1, ch));
	}

	return in;
}
