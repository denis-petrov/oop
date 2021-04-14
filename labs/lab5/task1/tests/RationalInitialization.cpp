#include "RationalTests.h"

struct Rational_
{
	const CRational rationalEmpty;
	Rational_()
	{
	}
};

BOOST_FIXTURE_TEST_SUITE(Rational_initialization, Rational_)

	BOOST_AUTO_TEST_CASE(able_be_empty) 
	{
		BOOST_CHECK(rationalEmpty.GetNumerator() == 0);
		BOOST_CHECK(rationalEmpty.GetDenominator() == 1);
		BOOST_CHECK(rationalEmpty.IsNegative() == false);
	}

	BOOST_AUTO_TEST_CASE(able_only_numerator)
	{
		CRational rationalOne(1);
		BOOST_CHECK(rationalOne.GetNumerator() == 1);
		BOOST_CHECK(rationalOne.GetDenominator() == 1);

		CRational rationalZero(0);
		BOOST_CHECK(rationalZero.GetNumerator() == 0);
		BOOST_CHECK(rationalZero.GetDenominator() == 1);

		CRational rationalMinus(-1);
		BOOST_CHECK(rationalMinus.GetNumerator() == 1);
		BOOST_CHECK(rationalMinus.GetDenominator() == 1);
		BOOST_CHECK(rationalMinus.IsNegative() == true);
	}

	BOOST_AUTO_TEST_CASE(able_numerator_and_denominator)
	{
		CRational rational(1, 1);
		BOOST_CHECK(rational.GetNumerator() == 1);
		BOOST_CHECK(rational.GetDenominator() == 1);

		CRational rational2(10, 5);
		BOOST_CHECK(rational2.GetNumerator() == 2);
		BOOST_CHECK(rational2.GetDenominator() == 1);

		CRational rational3(7, 3);
		BOOST_CHECK(rational3.GetNumerator() == 7);
		BOOST_CHECK(rational3.GetDenominator() == 3);
		
		CRational rational4(-7, 3);
		BOOST_CHECK(rational4.GetNumerator() == 7);
		BOOST_CHECK(rational4.GetDenominator() == 3);
		BOOST_CHECK(rational4.IsNegative() == true);
	}

	BOOST_AUTO_TEST_CASE(numerator_and_denominator_reduce_by_gcd)
	{
		CRational rational(6, 3);
		BOOST_CHECK(rational.GetNumerator() == 2);
		BOOST_CHECK(rational.GetDenominator() == 1);

		CRational rational2(18, 6);
		BOOST_CHECK(rational2.GetNumerator() == 3);
		BOOST_CHECK(rational2.GetDenominator() == 1);
		BOOST_CHECK(rational2.IsNegative() == false);
	}

	BOOST_AUTO_TEST_CASE(numerator_and_denominator_stay_with_correct_sign)
	{
		CRational rational(-6, 3);
		BOOST_CHECK(rational.GetNumerator() == 2);
		BOOST_CHECK(rational.GetDenominator() == 1);
		BOOST_CHECK(rational.IsNegative() == true);

		CRational rational2(-18, -6);
		BOOST_CHECK(rational2.GetNumerator() == 3);
		BOOST_CHECK(rational2.GetDenominator() == 1);
		BOOST_CHECK(rational2.IsNegative() == false);

		CRational rational3(-0, 1);
		BOOST_CHECK(rational3.GetNumerator() == 0);
		BOOST_CHECK(rational3.GetDenominator() == 1);
		BOOST_CHECK(rational3.IsNegative() == false);

		CRational rational4(0, -1);
		BOOST_CHECK(rational4.GetNumerator() == 0);
		BOOST_CHECK(rational4.GetDenominator() == 1);
		BOOST_CHECK(rational4.IsNegative() == false);
	}
	
	BOOST_AUTO_TEST_CASE(throw_invalid_argument_if_denominator_is_equal_zero)
	{
		BOOST_CHECK_THROW(CRational(1, 0), std::invalid_argument);
	}

BOOST_AUTO_TEST_SUITE_END()