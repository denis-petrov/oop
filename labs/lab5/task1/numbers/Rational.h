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

public:
	CRational const operator+() const;
	CRational const operator-() const;

	CRational & operator+=(CRational const& rhs);
	CRational & operator-=(CRational const& rhs);
	CRational & operator*=(CRational const& rhs);
	CRational & operator/=(CRational const& rhs);

private:
	void ReduceByGreatestCommonDivisor();
	bool IsLessThanZero() const;
	void EnsureCorrectSign();
	void Assign(const int numerator, const int denominator);

private:
	int m_numerator, m_denominator;
};

CRational const operator+(CRational lhs, CRational const& rhs);
CRational const operator-(CRational lhs, CRational const& rhs);
CRational const operator*(CRational lhs, CRational const& rhs);
CRational const operator/(CRational lhs, CRational const& rhs);

bool operator==(CRational const& lhs, CRational const& rhs);
bool operator!=(CRational const& lhs, CRational const& rhs);

bool operator>(CRational const& lhs, CRational const& rhs);
bool operator>=(CRational const& lhs, CRational const& rhs);
bool operator<(CRational const& lhs, CRational const& rhs);
bool operator<=(CRational const& lhs, CRational const& rhs);

std::ostream& operator<<(std::ostream& out, CRational const& num);
std::istream& operator>>(std::istream& in, CRational& num);
