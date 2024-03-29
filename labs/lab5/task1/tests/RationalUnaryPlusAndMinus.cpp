#include "RationalTests.h"

struct Rational_
{
	const CRational rationalEmpty;
	Rational_(){}
};

BOOST_FIXTURE_TEST_SUITE(Rational_unary_plus_and_minus, Rational_)

	BOOST_AUTO_TEST_CASE(unary_plus_able_be_empty)
	{
		CRational rationalEmpty;
		BOOST_CHECK((+rationalEmpty).GetNumerator() == 0);
		BOOST_CHECK((+rationalEmpty).GetDenominator() == 1);
	}

	BOOST_AUTO_TEST_CASE(unary_plus_returns_itself)
	{
		CRational rational1(1, 4);
		BOOST_CHECK((+rational1).GetNumerator() == 1);
		BOOST_CHECK((+rational1).GetDenominator() == 4);

		CRational rational2(-1, 4);
		BOOST_CHECK((+rational2).GetNumerator() == -1);
		BOOST_CHECK((+rational2).GetDenominator() == 4);

		CRational rational3(-1, -4);
		BOOST_CHECK((+rational3).GetNumerator() == 1);
		BOOST_CHECK((+rational3).GetDenominator() == 4);
	}

	BOOST_AUTO_TEST_CASE(unary_minus_able_be_empty)
	{
		CRational rationalEmpty;
		BOOST_CHECK((-rationalEmpty).GetNumerator() == 0);
		BOOST_CHECK((-rationalEmpty).GetDenominator() == 1);
	}

	BOOST_AUTO_TEST_CASE(unary_minus_returns_opposite_object)
	{
		CRational rational(-1, 4);
		BOOST_CHECK((-rational).GetNumerator() == 1);
		BOOST_CHECK((-rational).GetDenominator() == 4);

		CRational rational2(-1, -4);
		BOOST_CHECK((-rational2).GetNumerator() == -1);
		BOOST_CHECK((-rational2).GetDenominator() == 4);

		CRational rational3(1, 4);
		BOOST_CHECK((-rational3).GetNumerator() == -1);
		BOOST_CHECK((-rational3).GetDenominator() == 4);
	}

BOOST_AUTO_TEST_SUITE_END()