#include "stdafx.h"

struct MyString_
{
	MyString_() {}
};


BOOST_FIXTURE_TEST_SUITE(My_String_substring, MyString_)

	BOOST_AUTO_TEST_CASE(able_be_empty)
	{
		CMyString emptyStr;
		BOOST_CHECK(emptyStr.GetLength() == 0);
		BOOST_CHECK(emptyStr == "");
		BOOST_CHECK(emptyStr.SubString(0, 0) == "");
	}

	BOOST_AUTO_TEST_CASE(return_substring_if_taken_arguments_is_valid)
	{
		CMyString str("test my string");
		BOOST_CHECK(str.GetLength() == 14);
		BOOST_CHECK(str == "test my string");
		BOOST_CHECK(str.SubString(0, 2) == "te");
		BOOST_CHECK(str.SubString(0, 0) == "");
		BOOST_CHECK(str.SubString(0, 1) == "t");
		BOOST_CHECK(str.SubString(6, 10) == "y st");
		BOOST_CHECK(str.SubString(2, 14) == "st my string");
	}

	BOOST_AUTO_TEST_CASE(throw_invalid_argument_if_m_length_is_invalid)
	{
		CMyString emptyStr;
		BOOST_CHECK(emptyStr.GetLength() == 0);
		BOOST_CHECK(emptyStr == "");
		BOOST_CHECK_THROW(emptyStr.SubString(0, 10), std::invalid_argument);
		BOOST_CHECK_THROW(emptyStr.SubString(6, 4), std::invalid_argument);
		BOOST_CHECK_THROW(emptyStr.SubString(1, 0), std::invalid_argument);

		CMyString str("test my string");
		BOOST_CHECK(str.GetLength() == 14);
		BOOST_CHECK(str == "test my string");
		BOOST_CHECK_THROW(str.SubString(2, 0), std::invalid_argument);
		BOOST_CHECK_THROW(str.SubString(28, 30), std::invalid_argument);
		BOOST_CHECK_THROW(str.SubString(-1, -1), std::invalid_argument);
	}

BOOST_AUTO_TEST_SUITE_END()