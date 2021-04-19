#include "stdafx.h"

struct MyString_
{
	MyString_() {}
};

BOOST_FIXTURE_TEST_SUITE(My_String_equal, MyString_)

	BOOST_AUTO_TEST_CASE(able_do_equal_lhs_to_rhs)
	{
		CMyString emptyStr1;
		CMyString emptyStr2;
		emptyStr1 = emptyStr2;
		BOOST_CHECK(emptyStr1 == emptyStr2);

		CMyString str1("not test");
		CMyString str2("test my string");
		str1 = str2;
		BOOST_CHECK(str1 == "test my string");
	}

	BOOST_AUTO_TEST_CASE(able_do_equal_lhs_to_temp_rhs)
	{
		CMyString emptyStr1;
		CMyString emptyStr2;
		emptyStr1 = generateItem("");
		BOOST_CHECK(emptyStr1 == emptyStr2);

		CMyString str1("not test");
		str1 = generateItem("test my string");
		std::cout << str1 << "\n";
		BOOST_CHECK(str1 == "test my string");
	}

	BOOST_AUTO_TEST_CASE(correct_way_when_equal_to_itself)
	{
		CMyString emptyStr1;
		emptyStr1 = emptyStr1;
		BOOST_CHECK(emptyStr1 == emptyStr1);

		CMyString str1("not test");
		str1 = str1;
		BOOST_CHECK(str1 == "not test");
	}

BOOST_AUTO_TEST_SUITE_END()