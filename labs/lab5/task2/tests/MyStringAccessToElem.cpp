#include "stdafx.h"

struct MyString_
{
	MyString_() {}
};

BOOST_FIXTURE_TEST_SUITE(My_String_access_to_elem, MyString_)

	BOOST_AUTO_TEST_CASE(able_get_const_elem_in_buffer)
	{
		CMyString notEmptyStr("1");
		BOOST_CHECK(notEmptyStr[0] == '1');

		CMyString str1("test my string");
		BOOST_CHECK(str1[10] == 'r');

		CMyString str2("test my");
		BOOST_CHECK(str2[6] == 'y');
	}

	BOOST_AUTO_TEST_CASE(able_modify_elem_by_index)
	{
		CMyString notEmptyStr("1");
		BOOST_CHECK(notEmptyStr[0] == '1');
		notEmptyStr[0] = '2';
		BOOST_CHECK(notEmptyStr[0] == '2');

		CMyString str1("test my string");
		BOOST_CHECK(str1[10] == 'r');
		str1[10] = 'o';
		BOOST_CHECK(str1[10] == 'o');

		CMyString str2("test my");
		BOOST_CHECK(str2[6] == 'y');
		str2[6] = 'z';
		BOOST_CHECK(str2[6] == 'z');
	}

	BOOST_AUTO_TEST_CASE(throw_out_of_range_if_not_valid_index)
	{
		CMyString notEmptyStr("1");
		BOOST_CHECK_THROW(notEmptyStr[2], std::out_of_range);

		CMyString str1("test my string");
		BOOST_CHECK_THROW(str1[20], std::out_of_range);

		CMyString str2("test my");
		BOOST_CHECK_THROW(str2[-1], std::out_of_range);
	}

BOOST_AUTO_TEST_SUITE_END()