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

	BOOST_AUTO_TEST_CASE(able_print_empty)
	{
		CRational rationalEmpty;
		BOOST_CHECK(GetRationalFromString("0/1") == rationalEmpty);
	}
/*

	BOOST_AUTO_TEST_CASE(able_print_rational_more_than_zero)
	{
		CRational num(1, 1);
		BOOST_CHECK(GetRationalAsString(num) == "1/1");
	}

	BOOST_AUTO_TEST_CASE(able_print_rational_less_than_zero)
	{
		CRational num(-1, 1);
		BOOST_CHECK(GetRationalAsString(num) == "-1/1");

		CRational num2(1, -1);
		BOOST_CHECK(GetRationalAsString(num2) == "-1/1");
	}

	BOOST_AUTO_TEST_CASE(able_print_rational_equal_to_zero)
	{
		CRational num(0);
		BOOST_CHECK(GetRationalAsString(num) == "0/1");
	}

	BOOST_AUTO_TEST_CASE(able_print_rational_initialized_by_int_and_more_zero)
	{
		CRational num1(4);
		BOOST_CHECK(GetRationalAsString(num1) == "4/1");

		CRational num2(8);
		BOOST_CHECK(GetRationalAsString(num2) == "8/1");
	}

	BOOST_AUTO_TEST_CASE(able_print_rational_initialized_by_int_and_less_zero)
	{
		CRational num(-8);
		BOOST_CHECK(GetRationalAsString(num) == "-8/1");
	}*/

BOOST_AUTO_TEST_SUITE_END()