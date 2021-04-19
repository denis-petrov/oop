#pragma once

class CRational
{
public:
	CRational();

	CRational(int value);

	CRational(const int numerator, const int denominator);

	int GetNumerator() const;
	int GetDenominator() const;
	double ToDouble() const;

	std::pair<int, CRational> ToCompoundFraction() const;

public:
	CRational const operator+() const;
	CRational const operator-() const;

	CRational & operator+=(CRational const& rhs);
	CRational & operator-=(CRational const& rhs);
	CRational & operator*=(CRational const& rhs);
	CRational & operator/=(CRational const& rhs);

	friend std::istream& operator>>(std::istream& in, CRational& num);

private:
	void ReduceByGreatestCommonDivisor();
	bool IsNegative() const;
	void EnsureCorrectSign();
	void Normilize();
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