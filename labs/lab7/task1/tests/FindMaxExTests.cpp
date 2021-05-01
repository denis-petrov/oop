#include "stdafx.h"
#include "../FindMaxEx/FindMaxEx.h"

struct FindMaxEx_
{
	std::vector<int> emptyArr;
	std::vector<int> arrInt = { 1, 24, 52, 1, 0, -1, -23};
	std::vector<std::string> arrStr = { "1", "lol", "", "tests"};
	int maxValInt = 0;
	std::string maxValStr;
};

bool CompareTwoInt(int a, int b) 
{
	return a < b;
}

bool CompareTwoString(std::string a, std::string b)
{
	return a < b;
}


BOOST_FIXTURE_TEST_SUITE(FindMaxEx_tests, FindMaxEx_)

	BOOST_AUTO_TEST_CASE(empty_array_return_false)
	{
		BOOST_CHECK(!FindMax(emptyArr, maxValInt, [](int a, int b) { return a < b; }));
	}

	BOOST_AUTO_TEST_CASE(abe_use_on_vector_of_int)
	{
		BOOST_CHECK(FindMax(arrInt, maxValInt, [](int a, int b) { return a < b; }));
		BOOST_CHECK(maxValInt == 52);
	}

	BOOST_AUTO_TEST_CASE(abe_use_custom_compare_function_on_vector_of_int)
	{
		BOOST_CHECK(FindMax(arrInt, maxValInt, CompareTwoInt));
		BOOST_CHECK(maxValInt == 52);
	}

	BOOST_AUTO_TEST_CASE(abe_use_custom_compare_function_on_vector_of_string)
	{
		BOOST_CHECK(FindMax(arrStr, maxValStr, CompareTwoString));
		BOOST_CHECK(maxValStr == "tests");
	}

BOOST_AUTO_TEST_SUITE_END()