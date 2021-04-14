#include "stdafx.h"
#include "Rational.h"

using namespace std;

CRational::CRational()
	: m_numerator(DEFAULT_NUMERATOR)
	, m_denominator(DEFAULT_DENOMINATOR)
{
}

CRational::CRational(const int value)
	: m_numerator(value)
	, m_denominator(DEFAULT_DENOMINATOR)
	, m_isNegative(IsLessThanZero())
{
	EnsureCorrectSign();
}

int GetGCD(int first, int second)
{
	return !second ? abs(first) : GetGCD(second, first % second);
}

CRational::CRational(const int numerrator, const int denominator)
	: m_numerator(numerrator)
	, m_denominator(denominator)
	, m_isNegative(IsLessThanZero())
{
	if (m_denominator == NOT_CORRECT_DENOMINATOR)
		throw invalid_argument("Denominator cannot be equal " + to_string(NOT_CORRECT_DENOMINATOR) + "!");

	EnsureCorrectSign();
	ReduceByGreatestCommonDivisor();
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
	return m_numerator / m_denominator;
}

bool CRational::IsNegative() const
{
	return m_isNegative;
}

/* OPERATIONS */

CRational const CRational::operator+() const
{
	return m_isNegative ? CRational(m_numerator, -m_denominator) : CRational(m_numerator, m_denominator);
}

CRational const CRational::operator-() const
{
	return m_isNegative ? CRational(m_numerator, m_denominator) : CRational(m_numerator, -m_denominator);
}

CRational const operator+(CRational lhs, CRational const& rhs) 
{
	return lhs += rhs;
}

CRational const operator+(CRational lhs, int const rhs)
{
	return lhs += rhs;
}

CRational const operator+(int const lhs, CRational rhs)
{
	return rhs += lhs;
}

CRational& CRational::operator+=(CRational const& rhs)
{
	auto rhsNumerator = (rhs.IsNegative()) ? (-rhs.GetNumerator()) * m_denominator : rhs.GetNumerator() * m_denominator;
	auto lhsNumerator = (m_isNegative) ? (-m_numerator) * rhs.GetDenominator() : m_numerator * rhs.GetDenominator();

	Assign(rhsNumerator + lhsNumerator, m_denominator * rhs.GetDenominator());
	return *this;
}

CRational& CRational::operator+=(int const rhs)
{
	int numerator = m_isNegative ? -m_numerator : m_numerator;
	Assign(numerator + rhs * m_denominator, m_denominator);
	return *this;
}

/* PRIVATE */
void CRational::ReduceByGreatestCommonDivisor()
{
	auto gcd = GetGCD(m_numerator, m_denominator);
	m_numerator /= gcd;
	m_denominator /= gcd;
}

bool CRational::IsLessThanZero() const
{
	return ((m_numerator < 0 && m_denominator > 0) || (m_numerator > 0 && m_denominator < 0));
}

void CRational::EnsureCorrectSign()
{
	m_numerator = abs(m_numerator);
	m_denominator = abs(m_denominator);
}

void CRational::Assign(const int numerator, const int denominator)
{
	m_numerator = numerator;
	m_denominator = denominator;
	m_isNegative = IsLessThanZero();

	EnsureCorrectSign();
	ReduceByGreatestCommonDivisor();
}
