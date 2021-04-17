#include "stdafx.h"

struct MyString_
{
	MyString_() {}
};

CMyString const GetMyStringFromString(std::string const& str)
{
	CMyString res;
	std::istringstream(str) >> res;
	return res;
}

std::string const GetMyStringAsString(CMyString const& str)
{
	std::ostringstream strm;
	strm << str;
	return strm.str();
}

BOOST_FIXTURE_TEST_SUITE(My_String_read_and_print, MyString_)

	BOOST_AUTO_TEST_CASE(able_read_empty)
	{
		CMyString emptyStr;
		BOOST_CHECK(GetMyStringFromString("") == emptyStr);
	}

	BOOST_AUTO_TEST_CASE(able_read_string)
	{
		CMyString str1("test");
		BOOST_CHECK(GetMyStringFromString("test") == str1);

		CMyString str2("te  st 12");
		BOOST_CHECK(GetMyStringFromString("te  st 12") == str2);

		CMyString str3("@@##");
		BOOST_CHECK(GetMyStringFromString("@@##") == str3);
	}

	BOOST_AUTO_TEST_CASE(able_read_string_with_system_symbols)
	{
		CMyString str("test");
		BOOST_CHECK(GetMyStringFromString("test\n") == str);

		CMyString str2("test\t");
		BOOST_CHECK(GetMyStringFromString("test\t") == str2);
	}

	BOOST_AUTO_TEST_CASE(able_print_empty)
	{
		CMyString emptyStr;
		BOOST_CHECK(GetMyStringAsString(emptyStr) == "");
	}
	
	BOOST_AUTO_TEST_CASE(able_print_my_string)
	{
		CMyString str1("test");
		BOOST_CHECK(GetMyStringAsString(str1) == "test");

		CMyString str2("te  st 12");
		BOOST_CHECK(GetMyStringAsString(str2) == "te  st 12");

		CMyString str3("@@##");
		BOOST_CHECK(GetMyStringAsString(str3) == "@@##");
	}

	BOOST_AUTO_TEST_CASE(able_print_string_with_system_symbols)
	{
		CMyString str1("test");
		BOOST_CHECK(GetMyStringAsString(str1) == "test");

		CMyString str2("test\t");
		BOOST_CHECK(GetMyStringAsString(str2) == "test\t");
	}

BOOST_AUTO_TEST_SUITE_END()