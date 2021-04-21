#include "stdafx.h"

struct MyString_
{
	MyString_() {}
};

BOOST_FIXTURE_TEST_SUITE(My_String_iterator, MyString_)

	BOOST_AUTO_TEST_CASE(able_get_begin_and_end_from_empty_mystring)
	{
		CMyString emptyStr;
		BOOST_CHECK(emptyStr.begin());
		BOOST_CHECK(emptyStr.end());
	}

	BOOST_AUTO_TEST_CASE(able_use_for_loop)
	{
		CMyString str("test my string");
		CMyString res;
		BOOST_CHECK(str.GetLength() == 14);
		BOOST_CHECK(str == "test my string");
		for (auto&& ch : str)
		{
			res += ch;
		}
		BOOST_CHECK(str == res);
	}

	BOOST_AUTO_TEST_CASE(able_use_const_for_loop)
	{
		CMyString str("test my string");
		CMyString res;
		BOOST_CHECK(str.GetLength() == 14);
		BOOST_CHECK(str == "test my string");
		for (auto it = str.cbegin(); it != str.cend(); it++)
		{
			res += *it;
		}
		BOOST_CHECK(str == res);
	}

	BOOST_AUTO_TEST_CASE(able_add_and_reduce_value_from_iterator)
	{
		CMyString str("test my string");
		CMyString res;
		BOOST_CHECK(str.GetLength() == 14);
		BOOST_CHECK(str == "test my string");
		auto itB = str.begin();
		BOOST_CHECK(*itB == str[0]);
		itB++;
		BOOST_CHECK(*itB == str[1]);
		itB += 2;
		BOOST_CHECK(*itB == str[3]);

		auto itE = str.end();
		itE--;
		BOOST_CHECK(*itE == str[13]);
		itE -= 2;
		BOOST_CHECK(*itE == str[11]);

		BOOST_CHECK(itB != itE);
	}

BOOST_AUTO_TEST_SUITE_END()