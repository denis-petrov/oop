#include "MyStringTestsHandler.h"

struct MyString_
{
	MyString_() {}
};

BOOST_FIXTURE_TEST_SUITE(My_String_initialization, MyString_)

	BOOST_AUTO_TEST_CASE(able_be_empty)
	{
		CMyString emptyStr;
		BOOST_CHECK(emptyStr.GetLength() == 0);
		BOOST_CHECK(strcmp(emptyStr.GetStringData(), "") == 0);
	}

	BOOST_AUTO_TEST_CASE(able_to_take_string)
	{
		CMyString zeroStr("");
		BOOST_CHECK(zeroStr.GetLength() == 0);
		BOOST_CHECK(strcmp(zeroStr.GetStringData(), "") == 0);

		CMyString str("test my string");
		BOOST_CHECK(str.GetLength() == 14);
		BOOST_CHECK(strcmp(str.GetStringData(), "test my string") == 0);
	}

	BOOST_AUTO_TEST_CASE(able_to_take_string_and_length)
	{
		CMyString zeroStr("", 0);
		BOOST_CHECK(zeroStr.GetLength() == 0);
		BOOST_CHECK(strcmp(zeroStr.GetStringData(), "") == 0);

		CMyString str("test my string", 14);
		BOOST_CHECK(str.GetLength() == 14);
		BOOST_CHECK(strcmp(str.GetStringData(), "test my string") == 0);
	}

BOOST_AUTO_TEST_SUITE_END()