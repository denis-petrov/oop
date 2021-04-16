#include "RationalTests.h"

struct Rational_
{
	const CRational rationalEmpty;
	Rational_() {}
};

CRational const GetRationalFromString(std::string const& str)
{
	CRational num;
	std::istringstream(str) >> num;
	return num;
}

BOOST_FIXTURE_TEST_SUITE(Rational_read, Rational_)

	BOOST_AUTO_TEST_CASE(able_read_empty)
	{
		CRational rationalEmpty;
		BOOST_CHECK(GetRationalFromString("0/1") == rationalEmpty);
	}

	BOOST_AUTO_TEST_CASE(able_read_rational_more_than_zero)
	{
		CRational num(1, 1);
		BOOST_CHECK(GetRationalFromString("1/1") == num);
	}

	BOOST_AUTO_TEST_CASE(able_read_rational_less_than_zero)
	{
		CRational num1(-1, 1);
		BOOST_CHECK(GetRationalFromString("-1/1") == num1);

		CRational num2(-1, 1);
		BOOST_CHECK(GetRationalFromString("1/-1") == num2);

		CRational num3(1, 1);
		BOOST_CHECK(GetRationalFromString("-1/-1") == num3);
	}

	BOOST_AUTO_TEST_CASE(able_read_not_optimized_rational)
	{
		CRational num1(-12, 2);
		BOOST_CHECK(GetRationalFromString("-6/1") == num1);

		CRational num2(-62, 4);
		BOOST_CHECK(GetRationalFromString("31/-2") == num2);
	}

	BOOST_AUTO_TEST_CASE(return_empty_if_incorrect_string)
	{
		CRational rationalEmpty;
		BOOST_CHECK(GetRationalFromString("test") == rationalEmpty);
	}

BOOST_AUTO_TEST_SUITE_END()