#include "RationalTests.h"

struct Rational_
{
	const CRational rationalEmpty;
	Rational_() {}
};

BOOST_FIXTURE_TEST_SUITE(Rational_public_part, Rational_)

	BOOST_AUTO_TEST_CASE(able_get_numerator)
	{
		CRational rationalEmpty;
		BOOST_CHECK(rationalEmpty.GetNumerator() == 0);

		CRational num(-1);
		BOOST_CHECK(num.GetNumerator() == -1);

		CRational num2(-4, 8);
		BOOST_CHECK(num2.GetNumerator() == -1);

		CRational num3(4, -8);
		BOOST_CHECK(num3.GetNumerator() == -1);

		CRational num4(-4, -8);
		BOOST_CHECK(num4.GetNumerator() == 1);
	}

	BOOST_AUTO_TEST_CASE(able_get_demoninator)
	{
		CRational rationalEmpty;
		BOOST_CHECK(rationalEmpty.GetDenominator() == 1);

		CRational num(-1);
		BOOST_CHECK(num.GetDenominator() == 1);

		CRational num2(-4, 8);
		BOOST_CHECK(num2.GetDenominator() == 2);

		CRational num3(4, -8);
		BOOST_CHECK(num3.GetDenominator() == 2);

		CRational num4(-4, -8);
		BOOST_CHECK(num4.GetDenominator() == 2);
	}

	BOOST_AUTO_TEST_CASE(able_get_to_double)
	{
		CRational rationalEmpty;
		BOOST_CHECK(rationalEmpty.ToDouble() == (double)0);

		CRational num(-1);
		BOOST_CHECK(num.ToDouble() == (double)-1);

		CRational num2(-4, 8);
		BOOST_CHECK(num2.ToDouble() == (double)-0.5);

		CRational num3(4, -8);
		BOOST_CHECK(num3.ToDouble() == (double)-0.5);

		CRational num4(-4, -8);
		BOOST_CHECK(num4.ToDouble() == (double)0.5);
	}

	BOOST_AUTO_TEST_CASE(able_get_compound_fraction)
	{
		CRational rationalEmpty;
		auto res1 = rationalEmpty.ToCompoundFraction();
		BOOST_CHECK(res1.first == 0);
		BOOST_CHECK(res1.second == rationalEmpty);

		CRational num2(-1);
		auto res2 = num2.ToCompoundFraction();
		BOOST_CHECK(res2.first == -1);
		BOOST_CHECK(res2.second == rationalEmpty);

		CRational num3(-4, 8);
		auto res3 = num3.ToCompoundFraction();
		BOOST_CHECK(res3.first == 0);
		BOOST_CHECK(res3.second == CRational(-1, 2));

		CRational num4(-8, 3);
		auto res4 = num4.ToCompoundFraction();
		BOOST_CHECK(res4.first == -2);
		BOOST_CHECK(res4.second == CRational(-2, 3));

		CRational num5(-8, -5);
		auto res5 = num5.ToCompoundFraction();
		BOOST_CHECK(res5.first == 1);
		BOOST_CHECK(res5.second == CRational(3, 5));

		CRational num6(-9, 4);
		auto res6 = num6.ToCompoundFraction();
		BOOST_CHECK(res6.first == -2);
		BOOST_CHECK(res6.second == CRational(-1, 4));
	}

BOOST_AUTO_TEST_SUITE_END()