#include "stdafx.h"
#include "Rational.h"

using namespace std;

const regex RATIONAL_REGEX("(\\-?\\d+)\\/(\\-?\\d+)");

CRational::CRational()
	: m_numerator(0)
	, m_denominator(1)
{
}

CRational::CRational(const int value)
	: m_numerator(value)
	, m_denominator(1)
{
	Normilize();
}

int GetGCD(int first, int second)
{
	while (second)
	{
		auto temp = first % second;
		first = second;
		second = temp;
	}
	return abs(first); 
}

CRational::CRational(const int numerrator, const int denominator)
	: m_numerator(numerrator)
	, m_denominator(denominator)
{
	if (m_denominator == 0)
		throw invalid_argument("Denominator cannot be equal to " + to_string(NOT_CORRECT_DENOMINATOR) + "!");

	Normilize();
}

/* PUBLIC */

int CRational::GetNumerator() const
{
	return m_numerator;
}

int CRational::GetDenominator() const
{
	return m_denominator;
}

double CRational::ToDouble() const
{
	return (double)m_numerator / m_denominator;
}

pair<int, CRational> CRational::ToCompoundFraction() const
{
	int intPart = m_numerator / m_denominator;
	int fracPartNum = m_numerator % m_denominator;
	return { intPart, CRational(fracPartNum, m_denominator) };
}

/* PRIVATE */
void CRational::ReduceByGreatestCommonDivisor()
{
	auto gcd = GetGCD(m_numerator, m_denominator);
	m_numerator /= gcd;
	m_denominator /= gcd;
}

bool CRational::IsNegative() const
{
	return ((m_numerator < 0 && m_denominator > 0) || (m_numerator > 0 && m_denominator < 0));
}

void CRational::EnsureCorrectSign()
{
	bool isNegative = IsNegative();
	m_numerator = abs(m_numerator);
	m_denominator = abs(m_denominator);
	if (isNegative)
		m_numerator *= -1;
}

void CRational::Assign(const int numerator, const int denominator)
{
	m_numerator = numerator;
	m_denominator = denominator;

	Normilize();
}

void CRational::Normilize()
{
	EnsureCorrectSign();
	ReduceByGreatestCommonDivisor();
}


/* OPERATIONS */

CRational const CRational::operator+() const
{
	return CRational(m_numerator, m_denominator);
}

CRational const CRational::operator-() const
{
	return CRational((-1) * m_numerator, m_denominator);
}

CRational& CRational::operator+=(CRational const& rhs)
{
	auto rhsNumerator = rhs.GetNumerator() * m_denominator;
	auto lhsNumerator = m_numerator * rhs.GetDenominator();

	Assign(rhsNumerator + lhsNumerator, m_denominator * rhs.GetDenominator());
	return *this;
}

CRational& CRational::operator-=(CRational const& rhs)
{
	auto rhsNumerator = rhs.GetNumerator() * m_denominator;
	auto lhsNumerator = m_numerator * rhs.GetDenominator();

	Assign(lhsNumerator - rhsNumerator, m_denominator * rhs.GetDenominator());
	return *this;
}

CRational& CRational::operator*=(CRational const& rhs)
{
	Assign(m_numerator * rhs.GetNumerator(), m_denominator * rhs.GetDenominator());
	return *this;
}

CRational& CRational::operator/=(CRational const& rhs)
{
	int newDenominator = m_denominator * rhs.GetNumerator();
	if (newDenominator == 0)
		throw invalid_argument("Not correct expression, result denominator cannot be equal to 0!");

	Assign(m_numerator * rhs.GetDenominator(), newDenominator);
	return *this;
}

bool operator==(CRational const& lhs, CRational const& rhs) 
{
	return ((lhs.GetNumerator() == rhs.GetNumerator()) && (lhs.GetDenominator() == rhs.GetDenominator()));
}

bool operator!=(CRational const& lhs, CRational const& rhs)
{
	return !(lhs == rhs);
}

bool operator>(CRational const& lhs, CRational const& rhs)
{
	return ((lhs.GetNumerator() * rhs.GetDenominator()) > (rhs.GetNumerator() * lhs.GetDenominator()));
}

bool operator>=(CRational const& lhs, CRational const& rhs)
{
	return ((lhs > rhs) || (lhs == rhs));
}

bool operator<(CRational const& lhs, CRational const& rhs)
{
	return !(lhs >= rhs);
}

bool operator<=(CRational const& lhs, CRational const& rhs)
{
	return !(lhs > rhs);
}

ostream& operator<<(ostream& out, CRational const& num) 
{
	return out << num.GetNumerator() << "/" << num.GetDenominator();
}

istream& operator>>(istream& in, CRational& num)
{
	string search;
	if (!(getline(in, search, ' ')))
		return in;

	smatch matches;
	if (regex_match(search, matches, RATIONAL_REGEX))
	{
		auto numerator = boost::lexical_cast<int>(matches[1].str());
		auto denominator = boost::lexical_cast<int>(matches[2].str());
		num.Assign(numerator, denominator);
	}
	return in;
}

CRational const operator+(CRational lhs, CRational const& rhs)
{
	return lhs += rhs;
}

CRational const operator-(CRational lhs, CRational const& rhs)
{
	return lhs -= rhs;
}

CRational const operator*(CRational lhs, CRational const& rhs)
{
	return lhs *= rhs;
}

CRational const operator/(CRational lhs, CRational const& rhs)
{
	return lhs /= rhs;
}
