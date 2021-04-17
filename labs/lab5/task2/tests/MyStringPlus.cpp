#include "stdafx.h"

struct MyString_
{
	MyString_() {}
};

BOOST_FIXTURE_TEST_SUITE(My_String_plus, MyString_)

	BOOST_AUTO_TEST_CASE(plus_equal_able_add_rhs_string_to_lhs)
	{
		CMyString emptyStr1;
		CMyString emptyStr2;
		emptyStr1 += emptyStr2;
		BOOST_CHECK(emptyStr1 == emptyStr2);

		CMyString str1("test my string");
		CMyString str2("test my string");
		str1 += str2;
		BOOST_CHECK(str1 == "test my stringtest my string");

		CMyString str3("1");
		CMyString str4(" 2 3 4");
		str3 += str4;
		BOOST_CHECK(str3 == "1 2 3 4");
	}

	BOOST_AUTO_TEST_CASE(plus_return_concat_mystring_and_mystring)
	{
		CMyString emptyStr1;
		CMyString emptyStr2;
		CMyString res1 = emptyStr1 + emptyStr2;
		BOOST_CHECK(res1 == emptyStr2);

		CMyString str1("test my string");
		CMyString str2("test my string");
		CMyString res2 = str1 + str2;
		BOOST_CHECK(res2 == "test my stringtest my string");

		CMyString str3("1");
		CMyString str4(" 2 3 4");
		CMyString res3 = str3 + str4;
		BOOST_CHECK(res3 == "1 2 3 4");
	}

	BOOST_AUTO_TEST_CASE(plus_return_concat_stl_string_and_mystring)
	{
		CMyString emptyStr;
		CMyString res1 = "" + emptyStr;
		BOOST_CHECK(res1 == emptyStr);

		CMyString str2("test my string");
		CMyString res2 = "test my string" + str2;
		BOOST_CHECK(res2 == "test my stringtest my string");

		CMyString str3(" 2 3 4");
		CMyString res3 = "1" + str3;
		BOOST_CHECK(res3 == "1 2 3 4");
	}

	BOOST_AUTO_TEST_CASE(plus_return_concat_const_char_array_and_mystring)
	{
		CMyString emptyStr;
		const char* empty1 = "";
		CMyString res1 = empty1 + emptyStr;
		BOOST_CHECK(res1 == emptyStr);

		CMyString str2("test my string");
		const char* arr2 = "test my string";
		CMyString res2 = arr2 + str2;
		BOOST_CHECK(res2 == "test my stringtest my string");

		CMyString str3(" 2 3 4");
		const char* arr3 = "1";
		CMyString res3 = arr3 + str3;
		BOOST_CHECK(res3 == "1 2 3 4");
	}

BOOST_AUTO_TEST_SUITE_END()