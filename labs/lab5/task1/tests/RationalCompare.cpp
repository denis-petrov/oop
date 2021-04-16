#include "RationalTests.h"

struct Rational_
{
	const CRational rationalEmpty;
	Rational_() {}
};

BOOST_FIXTURE_TEST_SUITE(Rational_compare, Rational_)

	/* More */

	BOOST_AUTO_TEST_CASE(more_return_false_if_each_other_is_empty)
	{
		CRational rationalEmpty1;
		CRational rationalEmpty2;
		BOOST_CHECK(!(rationalEmpty1 > rationalEmpty2));
	}

	BOOST_AUTO_TEST_CASE(more_return_true_if_each_other_is_rational_lhs_more_than_rhs)
	{
		CRational lhs(1, 1);
		CRational rhs(1, 3);
		BOOST_CHECK(lhs > rhs);

		CRational lhs2(3, 1);
		CRational rhs2(1, 1);
		BOOST_CHECK(lhs2 > rhs);

		CRational lhs3(3, 1);
		CRational rhs3(1, 2);
		BOOST_CHECK(lhs3 > rhs3);
	}

	BOOST_AUTO_TEST_CASE(more_return_false_if_lhs_is_int_and_equal_to_rational_rhs)
	{
		int lhs = 1;
		CRational rhs(2, 2);
		BOOST_CHECK(!(lhs > rhs));
	}

	BOOST_AUTO_TEST_CASE(more_return_false_if_rhs_is_int_and_more_than_rational_lhs)
	{
		CRational lhs(2, 2);
		int rhs = 2;
		BOOST_CHECK(!(lhs > rhs));
	}

	BOOST_AUTO_TEST_CASE(more_return_true_if_rhs_is_int_and_less_than_lhs)
	{
		CRational lhs = (1, 2);
		int rhs = 0;
		BOOST_CHECK(lhs > rhs);
	}

	BOOST_AUTO_TEST_CASE(more_return_true_if_lhs_is_int_and_more_than_rhs)
	{
		int lhs = 10;
		CRational rhs(8, 2);
		BOOST_CHECK(lhs > rhs);
	}




	/* More equal */

	BOOST_AUTO_TEST_CASE(more_equal_return_true_if_each_other_is_empty)
	{
		CRational rationalEmpty1;
		CRational rationalEmpty2;
		BOOST_CHECK(rationalEmpty1 >= rationalEmpty2);
	}

	BOOST_AUTO_TEST_CASE(more_equal_return_true_if_each_other_is_rational_lhs_more_than_rhs)
	{
		CRational lhs(1, 1);
		CRational rhs(1, 3);
		BOOST_CHECK(lhs >= rhs);

		CRational lhs2(3, 1);
		CRational rhs2(1, 1);
		BOOST_CHECK(lhs2 >= rhs);

		CRational lhs3(3, 1);
		CRational rhs3(1, 2);
		BOOST_CHECK(lhs3 >= rhs3);
	}

	BOOST_AUTO_TEST_CASE(more_equal_return_true_if_lhs_is_int_and_equal_to_rational_rhs)
	{
		int lhs = 1;
		CRational rhs(2, 2);
		BOOST_CHECK(lhs >= rhs);
	}

	BOOST_AUTO_TEST_CASE(more_equal_return_false_if_rhs_is_int_and_more_than_rational_lhs)
	{
		CRational lhs(2, 2);
		int rhs = 2;
		BOOST_CHECK(!(lhs >= rhs));
	}

	BOOST_AUTO_TEST_CASE(more_equal_return_true_if_rhs_is_int_and_less_than_lhs)
	{
		CRational lhs = (1, 2);
		int rhs = 0;
		BOOST_CHECK(lhs >= rhs);
	}

	BOOST_AUTO_TEST_CASE(more_equal_return_true_if_lhs_is_int_and_more_than_rhs)
	{
		int lhs = 10;
		CRational rhs(8, 2);
		BOOST_CHECK(lhs >= rhs);
	}



	/* Less */

	BOOST_AUTO_TEST_CASE(less_return_false_if_each_other_is_empty)
	{
		CRational rationalEmpty1;
		CRational rationalEmpty2;
		BOOST_CHECK(!(rationalEmpty1 < rationalEmpty2));
	}

	BOOST_AUTO_TEST_CASE(less_return_false_if_each_other_is_rational_lhs_more_than_rhs)
	{
		CRational lhs(1, 1);
		CRational rhs(1, 3);
		BOOST_CHECK(!(lhs < rhs));

		CRational lhs2(3, 1);
		CRational rhs2(1, 1);
		BOOST_CHECK(!(lhs2 < rhs));

		CRational lhs3(3, 1);
		CRational rhs3(1, 2);
		BOOST_CHECK(!(lhs3 < rhs3));
	}

	BOOST_AUTO_TEST_CASE(less_return_false_if_lhs_is_int_and_equal_to_rational_rhs)
	{
		int lhs = 1;
		CRational rhs(2, 2);
		BOOST_CHECK(!(lhs < rhs));
	}

	BOOST_AUTO_TEST_CASE(less_return_true_if_rhs_is_int_and_more_than_rational_lhs)
	{
		CRational lhs(2, 2);
		int rhs = 2;
		BOOST_CHECK(lhs < rhs);
	}

	BOOST_AUTO_TEST_CASE(less_return_false_if_rhs_is_int_and_less_than_lhs)
	{
		CRational lhs = (1, 2);
		int rhs = 0;
		BOOST_CHECK(!(lhs < rhs));
	}

	BOOST_AUTO_TEST_CASE(less_return_false_if_lhs_is_int_and_more_than_rhs)
	{
		int lhs = 10;
		CRational rhs(8, 2);
		BOOST_CHECK(!(lhs < rhs));
	}



	/* Less equal */

	BOOST_AUTO_TEST_CASE(less_equal_return_trus_if_each_other_is_empty)
	{
		CRational rationalEmpty1;
		CRational rationalEmpty2;
		BOOST_CHECK(rationalEmpty1 <= rationalEmpty2);
	}

	BOOST_AUTO_TEST_CASE(less_equal_return_false_if_each_other_is_rational_lhs_more_than_rhs)
	{
		CRational lhs(1, 1);
		CRational rhs(1, 3);
		BOOST_CHECK(!(lhs <= rhs));

		CRational lhs2(3, 1);
		CRational rhs2(1, 1);
		BOOST_CHECK(!(lhs2 <= rhs));

		CRational lhs3(3, 1);
		CRational rhs3(1, 2);
		BOOST_CHECK(!(lhs3 <= rhs3));
	}

	BOOST_AUTO_TEST_CASE(less_equal_return_true_if_lhs_is_int_and_equal_to_rational_rhs)
	{
		int lhs = 1;
		CRational rhs(2, 2);
		BOOST_CHECK(lhs <= rhs);
	}

	BOOST_AUTO_TEST_CASE(less_equal_return_true_if_rhs_is_int_and_more_than_rational_lhs)
	{
		CRational lhs(2, 2);
		int rhs = 2;
		BOOST_CHECK(lhs <= rhs);
	}

	BOOST_AUTO_TEST_CASE(less_equal_return_false_if_rhs_is_int_and_less_than_lhs)
	{
		CRational lhs = (1, 2);
		int rhs = 0;
		BOOST_CHECK(!(lhs <= rhs));
	}

	BOOST_AUTO_TEST_CASE(less_equal_return_false_if_lhs_is_int_and_more_than_rhs)
	{
		int lhs = 10;
		CRational rhs(8, 2);
		BOOST_CHECK(!(lhs <= rhs));
	}

BOOST_AUTO_TEST_SUITE_END()