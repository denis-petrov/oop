#include "stdafx.h"

struct MyString_
{
	MyString_() {}
};

BOOST_FIXTURE_TEST_SUITE(My_String_compare_equal_and_not, MyString_)

	BOOST_AUTO_TEST_CASE(equal_return_true_if_strings_are_equal_or_empty)
	{
		CMyString emptyStr1;
		CMyString emptyStr2;
		BOOST_CHECK(emptyStr1 == emptyStr2);

		CMyString str1("test my string");
		CMyString str2("test my string");
		BOOST_CHECK(str1 == str2);
	}

	BOOST_AUTO_TEST_CASE(not_equal_return_false_if_strings_are_equal_or_empty)
	{
		CMyString emptyStr1;
		CMyString emptyStr2;
		BOOST_CHECK(!(emptyStr1 != emptyStr2));

		CMyString str1("test my string");
		CMyString str2("test my string");
		BOOST_CHECK(!(str1 != str2));
	}

	BOOST_AUTO_TEST_CASE(equal_return_false_if_strings_are_not_equal)
	{
		CMyString str1("1");
		CMyString str2("2");
		BOOST_CHECK(!(str1 == str2));

		CMyString str3("test my");
		CMyString str4("string");
		BOOST_CHECK(!(str3 == str4));
	}

	BOOST_AUTO_TEST_CASE(not_equal_return_true_if_strings_are_not_equal)
	{
		CMyString str1("1");
		CMyString str2("2");
		BOOST_CHECK(str1 != str2);

		CMyString str3("test my");
		CMyString str4("string");
		BOOST_CHECK(str3 != str4);
	}

BOOST_AUTO_TEST_SUITE_END()