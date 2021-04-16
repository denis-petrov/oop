#include "RationalTests.h"

struct Rational_
{
	const CRational rationalEmpty;
	Rational_() {}
};

BOOST_FIXTURE_TEST_SUITE(Rational_multuplication_equal, Rational_)

	BOOST_AUTO_TEST_CASE(right_hand_side_able_be_empty_and_be_rational)
	{
		CRational rationalEmpty1;
		CRational rationalEmpty2;
		rationalEmpty1 *= rationalEmpty2;
		BOOST_CHECK(rationalEmpty1.GetNumerator() == 0);
		BOOST_CHECK(rationalEmpty1.GetDenominator() == 1);
	}

	BOOST_AUTO_TEST_CASE(right_hand_side_able_be_less_zero_and_be_rational)
	{
		CRational rationalMoreZero(1, 1);
		CRational rationalLessZero(-1, 1);
		rationalMoreZero *= rationalLessZero;
		BOOST_CHECK(rationalMoreZero.GetNumerator() == -1);
		BOOST_CHECK(rationalMoreZero.GetDenominator() == 1);
	}

	BOOST_AUTO_TEST_CASE(left_hand_side_able_be_less_zero_and_be_rational)
	{
		CRational rationalMoreZero(1, 1);
		CRational rationalLessZero(-1, 1);
		rationalLessZero *= rationalMoreZero;
		BOOST_CHECK(rationalLessZero.GetNumerator() == -1);
		BOOST_CHECK(rationalLessZero.GetDenominator() == 1);
	}

	BOOST_AUTO_TEST_CASE(right_hand_side_denominator_able_be_not_equal_to_left_and_be_rational)
	{
		CRational lhs(1, 1);
		CRational rhs(1, 3);
		lhs *= rhs;
		BOOST_CHECK(lhs.GetNumerator() == 1);
		BOOST_CHECK(lhs.GetDenominator() == 3);
	}

	BOOST_AUTO_TEST_CASE(left_hand_side_denominator_able_be_not_equal_to_right_and_be_rational)
	{
		CRational rhs(1, 1);
		CRational lhs(1, 3);
		lhs *= rhs;
		BOOST_CHECK(lhs.GetNumerator() == 1);
		BOOST_CHECK(lhs.GetDenominator() == 3);
	}

	BOOST_AUTO_TEST_CASE(right_hand_side_and_left_hand_able_be_negative_and_rational)
	{
		CRational lhs(-1, 1);
		CRational rhs(-1, 3);
		lhs *= rhs;
		BOOST_CHECK(lhs.GetNumerator() == 1);
		BOOST_CHECK(lhs.GetDenominator() == 3);
	}

	BOOST_AUTO_TEST_CASE(left_hand_side_and_right_hand_able_be_negative_and_rational)
	{
		CRational rhs(-1, 1);
		CRational lhs(-1, 3);
		lhs *= rhs;
		BOOST_CHECK(lhs.GetNumerator() == 1);
		BOOST_CHECK(lhs.GetDenominator() == 3);
	}

	BOOST_AUTO_TEST_CASE(right_hand_side_able_be_int)
	{
		CRational lhs(-1, 1);
		int rhs(2);
		lhs *= rhs;
		BOOST_CHECK(lhs.GetNumerator() == -2);
		BOOST_CHECK(lhs.GetDenominator() == 1);
	}

	BOOST_AUTO_TEST_CASE(right_hand_side_able_be_equal_to_zero)
	{
		CRational lhs(-1, 1);
		int rhs(0);
		lhs *= rhs;
		BOOST_CHECK(lhs.GetNumerator() == 0);
		BOOST_CHECK(lhs.GetDenominator() == 1);
	}

	BOOST_AUTO_TEST_CASE(right_hand_side_able_be_less_than_zero)
	{
		CRational lhs(-1, 1);
		int rhs(-3);
		lhs *= rhs;
		BOOST_CHECK(lhs.GetNumerator() == 3);
		BOOST_CHECK(lhs.GetDenominator() == 1);
	}

BOOST_AUTO_TEST_SUITE_END()