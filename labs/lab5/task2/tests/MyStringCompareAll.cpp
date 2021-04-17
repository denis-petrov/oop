#include "stdafx.h"

struct MyString_
{
	MyString_() {}
};

BOOST_FIXTURE_TEST_SUITE(My_String_compare_all, MyString_)

	BOOST_AUTO_TEST_CASE(more_return_true_if_lhs_more_than_rhs)
	{
		CMyString emptyStr;
		CMyString notEmptyStr("1");
		BOOST_CHECK(notEmptyStr > emptyStr);

		CMyString str1("test my string");
		CMyString str2("test my");
		BOOST_CHECK(str1 > str2);

		CMyString str3("test zz");
		CMyString str4("test my");
		BOOST_CHECK(str3 > str4);
	}
	
	BOOST_AUTO_TEST_CASE(more_return_false_if_lhs_less_than_rhs_or_equal)
	{
		CMyString emptyStr;
		CMyString notEmptyStr("1");
		BOOST_CHECK(!(notEmptyStr < emptyStr));

		CMyString str1("test my string");
		CMyString str1_eq("test my string");
		CMyString str2("test my");
		BOOST_CHECK(!(str2 > str1));
		BOOST_CHECK(!(str1 > str1_eq));

		CMyString str3("test zz");
		CMyString str3_eq("test zz");
		CMyString str4("test my");
		BOOST_CHECK(!(str3 < str4));
		BOOST_CHECK(!(str3 > str3_eq));
	}

	BOOST_AUTO_TEST_CASE(more_equal_return_true_if_lhs_more_than_rhs_or_equal)
	{
		CMyString emptyStr;
		CMyString emptyStr2;
		CMyString notEmptyStr("1");
		BOOST_CHECK(notEmptyStr >= emptyStr);
		BOOST_CHECK(emptyStr >= emptyStr2);

		CMyString str1("test my string");
		CMyString str1_eq("test my string");
		CMyString str2("test my");
		BOOST_CHECK(str1 >= str2);
		BOOST_CHECK(str1 >= str1_eq);

		CMyString str3("test zz");
		CMyString str3_eq("test zz");
		CMyString str4("test my");
		BOOST_CHECK(str3 >= str4);
		BOOST_CHECK(str3 >= str3_eq);
	}

	BOOST_AUTO_TEST_CASE(more_equal_return_false_if_lhs_less_than_rhs)
	{
		CMyString emptyStr;
		CMyString emptyStr2;
		CMyString notEmptyStr("1");
		BOOST_CHECK(!(emptyStr >= notEmptyStr));

		CMyString str1("test my string");
		CMyString str2("test my");
		BOOST_CHECK(!(str2 >= str1));

		CMyString str3("test zz");
		CMyString str4("test my");
		BOOST_CHECK(!(str4 >= str3));
	}

	BOOST_AUTO_TEST_CASE(less_return_true_if_lhs_less_than_rhs)
	{
		CMyString emptyStr;
		CMyString notEmptyStr("1");
		BOOST_CHECK(emptyStr < notEmptyStr);

		CMyString str1("test my string");
		CMyString str2("test my");
		BOOST_CHECK(str2 < str1);

		CMyString str3("test zz");
		CMyString str4("test my");
		BOOST_CHECK(str4 < str3);
	}

	BOOST_AUTO_TEST_CASE(less_return_false_if_lhs_more_than_rhs_or_equal)
	{
		CMyString emptyStr;
		CMyString notEmptyStr("1");
		BOOST_CHECK(!(notEmptyStr < emptyStr));

		CMyString str1("test my string");
		CMyString str2("test my");
		BOOST_CHECK(!(str1 < str2));

		CMyString str3("test zz");
		CMyString str4("test my");
		BOOST_CHECK(!(str3 < str4));
	}

	BOOST_AUTO_TEST_CASE(less_equal_return_true_if_lhs_less_than_rhs_or_equal)
	{
		CMyString emptyStr;
		CMyString emptyStr_eq;
		CMyString notEmptyStr("1");
		BOOST_CHECK(emptyStr <= notEmptyStr);
		BOOST_CHECK(emptyStr <= emptyStr_eq);

		CMyString str1("test my string");
		CMyString str1_eq = str1;
		CMyString str2("test my");
		BOOST_CHECK(str2 <= str1);
		BOOST_CHECK(str1 <= str1_eq);

		CMyString str3("test zz");
		CMyString str3_eq = str3;
		CMyString str4("test my");
		BOOST_CHECK(str4 <= str3);
		BOOST_CHECK(str3 <= str3_eq);
	}

BOOST_AUTO_TEST_SUITE_END()