#include "stdafx.h"

struct MyString_
{
	MyString_() {}
};

BOOST_FIXTURE_TEST_SUITE(My_String_initialization_and_clear_and_substring, MyString_)

	BOOST_AUTO_TEST_CASE(able_be_empty)
	{
		CMyString emptyStr;
		BOOST_CHECK(emptyStr.GetLength() == 0);
		BOOST_CHECK(emptyStr == "");
	}

	BOOST_AUTO_TEST_CASE(able_to_take_string)
	{
		CMyString zeroStr("");
		BOOST_CHECK(zeroStr.GetLength() == 0);
		BOOST_CHECK(zeroStr == "");

		CMyString str("test my string");
		BOOST_CHECK(str.GetLength() == 14);
		BOOST_CHECK(str == "test my string");
	}

	BOOST_AUTO_TEST_CASE(able_to_take_string_and_length)
	{
		CMyString zeroStr("", 0);
		BOOST_CHECK(zeroStr.GetLength() == 0);
		BOOST_CHECK(zeroStr == "");

		CMyString str("test my string", 14);
		BOOST_CHECK(str.GetLength() == 14);
		BOOST_CHECK(str == "test my string");
	}

	BOOST_AUTO_TEST_CASE(able_to_copy_from_another_mystring_instance)
	{
		CMyString zeroStr("", 0);
		BOOST_CHECK(zeroStr.GetLength() == 0);
		BOOST_CHECK(zeroStr == "");

		CMyString str3(zeroStr);
		BOOST_CHECK(str3.GetLength() == 0);
		BOOST_CHECK(str3 == "");


		CMyString str("test my string", 14);
		BOOST_CHECK(str.GetLength() == 14);
		BOOST_CHECK(str == "test my string");

		CMyString str2(str);
		BOOST_CHECK(str2.GetLength() == 14);
		BOOST_CHECK(str2 == "test my string");
	}

	BOOST_AUTO_TEST_CASE(able_init_from_stl_string)
	{
		std::string stlZero;
		CMyString zeroStr(stlZero);
		BOOST_CHECK(zeroStr.GetLength() == 0);
		BOOST_CHECK(zeroStr == "");


		std::string stlString = "test my string";
		CMyString str(stlString);
		BOOST_CHECK(str.GetLength() == 14);
		BOOST_CHECK(str == "test my string");
	}

	BOOST_AUTO_TEST_CASE(able_init_from_temp_mystring_by_move_constructor)
	{
		CMyString zeroStr = generateEmptyItem();
		BOOST_CHECK(zeroStr.GetLength() == 0);
		BOOST_CHECK(zeroStr == "");

		CMyString str = generateItem("test");
		BOOST_CHECK(str.GetLength() == 4);
		BOOST_CHECK(str == "test");
	}

	BOOST_AUTO_TEST_CASE(able_clear_mystring_instance)
	{
		CMyString zeroStr = generateEmptyItem();
		BOOST_CHECK(zeroStr.GetLength() == 0);
		BOOST_CHECK(zeroStr == "");
		
		zeroStr.Clear();
		BOOST_CHECK(zeroStr.GetLength() == 0);
		BOOST_CHECK(zeroStr == "");

		
		CMyString str = generateItem("test");
		BOOST_CHECK(str.GetLength() == 4);
		BOOST_CHECK(str == "test");
		
		str.Clear();
		BOOST_CHECK(str.GetLength() == 0);
		BOOST_CHECK(str == "");
	}

BOOST_AUTO_TEST_SUITE_END()