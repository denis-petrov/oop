#include "RationalTests.h"

struct Rational_
{
	const CRational rationalEmpty;
	Rational_() {}
};

BOOST_FIXTURE_TEST_SUITE(Rational_equal_and_not_equal, Rational_)

	/* Equal */
	
	BOOST_AUTO_TEST_CASE(equal_return_true_if_each_other_is_empty)
	{
		CRational rationalEmpty1;
		CRational rationalEmpty2;
		BOOST_CHECK(rationalEmpty1 == rationalEmpty2);
	}
	
	BOOST_AUTO_TEST_CASE(equal_return_false_if_each_other_is_rational_and_denominators_are_not_equal)
	{
		CRational lhs(1, 1);
		CRational rhs(1, 3);
		BOOST_CHECK(!(lhs == rhs));
	}

	BOOST_AUTO_TEST_CASE(equal_return_false_if_each_other_is_rational_and_numerators_are_not_equal)
	{
		CRational lhs(3, 1);
		CRational rhs(1, 1);
		BOOST_CHECK(!(lhs == rhs));
	}

	BOOST_AUTO_TEST_CASE(equal_return_false_if_each_other_is_rational_and_denominators_and_numerators_are_not_equal)
	{
		CRational lhs(3, 1);
		CRational rhs(1, 2);
		BOOST_CHECK(!(lhs == rhs));
	}

	BOOST_AUTO_TEST_CASE(equal_return_true_if_lhs_is_int_and_equal_to_rational_rhs)
	{
		int lhs = 1;
		CRational rhs(2, 2);
		BOOST_CHECK(lhs == rhs);
	}

	BOOST_AUTO_TEST_CASE(equal_return_true_if_rhs_is_int_and_equal_to_rational_lhs)
	{
		CRational lhs(2, 2);
		int rhs = 1;
		BOOST_CHECK(lhs == rhs);
	}

	BOOST_AUTO_TEST_CASE(equal_return_false_if_lhs_is_rational_and_equal_to_int_rhs)
	{
		CRational lhs = (1, 2);
		int rhs = 7;
		BOOST_CHECK(!(lhs == rhs));
	}

	BOOST_AUTO_TEST_CASE(equal_return_false_if_lhs_is_int_and_not_equal_to_rational_rhs)
	{
		int lhs = 10;
		CRational rhs(8, 2);
		BOOST_CHECK(!(lhs == rhs));
	}



	/* Not equal */
	
	BOOST_AUTO_TEST_CASE(not_equal_return_false_if_each_other_is_empty)
	{
		CRational rationalEmpty1;
		CRational rationalEmpty2;
		BOOST_CHECK(!(rationalEmpty1 != rationalEmpty2));
	}

	BOOST_AUTO_TEST_CASE(not_equal_return_true_if_each_other_is_rational_and_denominators_are_not_equal)
	{
		CRational lhs(1, 1);
		CRational rhs(1, 3);
		BOOST_CHECK(lhs != rhs);
	}

	BOOST_AUTO_TEST_CASE(not_equal_return_true_if_each_other_is_rational_and_numerators_are_not_equal)
	{
		CRational lhs(3, 1);
		CRational rhs(1, 1);
		BOOST_CHECK(lhs != rhs);
	}

	BOOST_AUTO_TEST_CASE(not_equal_return_true_if_each_other_is_rational_and_denominators_and_numerators_are_not_equal)
	{
		CRational lhs(3, 1);
		CRational rhs(1, 2);
		BOOST_CHECK(lhs != rhs);
	}

	BOOST_AUTO_TEST_CASE(not_equal_return_false_if_lhs_is_int_and_equal_to_rational_rhs)
	{
		int lhs = 1;
		CRational rhs(2, 2);
		BOOST_CHECK(!(lhs != rhs));
	}

	BOOST_AUTO_TEST_CASE(not_equal_return_false_if_rhs_is_int_and_equal_to_rational_lhs)
	{
		CRational lhs(2, 2);
		int rhs = 1;
		BOOST_CHECK(!(lhs != rhs));
	}

	BOOST_AUTO_TEST_CASE(not_equal_return_true_if_lhs_is_rational_and_equal_to_int_rhs)
	{
		CRational lhs = (1, 2);
		int rhs = 7;
		BOOST_CHECK(lhs != rhs);
	}

	BOOST_AUTO_TEST_CASE(not_equal_return_true_if_lhs_is_int_and_not_equal_to_rational_rhs)
	{
		int lhs = 10;
		CRational rhs(8, 2);
		BOOST_CHECK(lhs != rhs);
	}

BOOST_AUTO_TEST_SUITE_END()