#pragma once

class CRational
{
public:
	CRational();

	CRational(const int value);

	CRational(const int numerator, const int denominator);

	int GetNumerator() const;
	int GetDenominator() const;
	double ToDouble() const;
	bool IsNegative() const;

public:
	CRational const operator+() const;
	CRational const operator-() const;

	CRational & operator+=(CRational const& rhs);
	CRational & operator+=(int const rhs);

private:
	void ReduceByGreatestCommonDivisor();
	bool IsLessThanZero() const;
	void EnsureCorrectSign();

	void Assign(const int numerator, const int denominator);

private:
	int m_numerator, m_denominator;
	bool m_isNegative = false;
};

CRational const operator+(CRational lhs, CRational const& rhs);
CRational const operator+(CRational lhs, int const rhs);
CRational const operator+(int const lhs, CRational rhs);
