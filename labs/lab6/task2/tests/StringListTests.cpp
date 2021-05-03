#include "stdafx.h"
#include "../string-list/StringList.h"

struct StringList_
{
};

CStringList CreatNewOne()
{
	CStringList list;
	list.PushBack("Hello");
	list.PushBack(" world");
	return list;
}

std::string const GetListAsString(CStringList const& list)
{
	std::ostringstream strm;
	strm << list;
	return strm.str();
}

BOOST_FIXTURE_TEST_SUITE(StringList_tests, StringList_)

	BOOST_AUTO_TEST_CASE(able_PushBack_node)
	{
		CStringList list;
		list.PushBack("Hello");
		BOOST_CHECK(list.GetSize() == 1);
		BOOST_CHECK(list.GetBackElement() == "Hello");

		list.PushBack(" world");
		BOOST_CHECK(list.GetSize() == 2);
		BOOST_CHECK(list.GetBackElement() == " world");
		BOOST_CHECK(GetListAsString(list) == "Hello world");
	}

	BOOST_AUTO_TEST_CASE(able_PushFront_node)
	{
		CStringList list;
		list.PushFront("Hello");
		BOOST_CHECK(list.GetSize() == 1);
		BOOST_CHECK(list.GetBackElement() == "Hello");

		list.PushFront(" world");
		BOOST_CHECK(list.GetSize() == 2);
		BOOST_CHECK(list.GetBackElement() == "Hello");

		BOOST_CHECK(GetListAsString(list) == " worldHello");
	}

	BOOST_AUTO_TEST_CASE(able_clear_list)
	{
		CStringList list;
		list.PushBack("Hello");
		list.PushBack(" world");
		BOOST_CHECK(list.GetSize() == 2);
		BOOST_CHECK(list.GetBackElement() == " world");
		BOOST_CHECK(GetListAsString(list) == "Hello world");
		list.Clear();
		BOOST_CHECK(list.GetSize() == 0);
	}

	BOOST_AUTO_TEST_CASE(able_use_move_constructor)
	{
		CStringList list;
		list.PushBack("Hello");
		list.PushBack(" world");
		BOOST_CHECK(list.GetSize() == 2);
		BOOST_CHECK(list.GetBackElement() == " world");
		BOOST_CHECK(GetListAsString(list) == "Hello world");

		CStringList list2(list);
		BOOST_CHECK(list2.GetSize() == 2);
		BOOST_CHECK(list2.GetBackElement() == " world");
		BOOST_CHECK(GetListAsString(list2) == "Hello world");

		CStringList list3(list2);
		BOOST_CHECK(list3.GetSize() == 2);
		BOOST_CHECK(list3.GetBackElement() == " world");
		list3.PushBack(" lol");
		BOOST_CHECK(GetListAsString(list3) == "Hello world lol");
	}

	BOOST_AUTO_TEST_CASE(able_use_replace_constructor)
	{
		CStringList list = CreatNewOne();
		BOOST_CHECK(list.GetSize() == 2);
		BOOST_CHECK(list.GetBackElement() == " world");
		BOOST_CHECK(GetListAsString(list) == "Hello world");
	}

	BOOST_AUTO_TEST_CASE(iterator_throw_error_if_node_null)
	{
		CStringList list;
		BOOST_CHECK_THROW(list.begin(), std::invalid_argument);
		BOOST_CHECK_THROW(list.end(), std::invalid_argument);
		BOOST_CHECK_THROW(list.rbegin(), std::invalid_argument);
		BOOST_CHECK_THROW(list.rend(), std::invalid_argument);
		BOOST_CHECK_THROW(list.cbegin(), std::invalid_argument);
		BOOST_CHECK_THROW(list.cend(), std::invalid_argument);
		BOOST_CHECK_THROW(list.crbegin(), std::invalid_argument);
		BOOST_CHECK_THROW(list.crend(), std::invalid_argument);
	}

	BOOST_AUTO_TEST_CASE(able_use_iterator)
	{
		CStringList list = CreatNewOne();
		BOOST_CHECK(list.GetSize() == 2);
		BOOST_CHECK(list.GetBackElement() == " world");
		BOOST_CHECK(GetListAsString(list) == "Hello world");

		std::string res;
		for (auto&& elem : list)
		{
			res += elem;
		}
		BOOST_CHECK(res == "Hello world");
		res.clear();

		for (auto it = list.cbegin(); it != list.cend(); ++it)
		{
			res += *it;
		}
		BOOST_CHECK(res == "Hello world");
	}

	BOOST_AUTO_TEST_CASE(able_use_reverse_iterator)
	{
		CStringList list = CreatNewOne();
		BOOST_CHECK(list.GetSize() == 2);
		BOOST_CHECK(list.GetBackElement() == " world");
		BOOST_CHECK(GetListAsString(list) == "Hello world");

		std::string res;
		for (auto it = list.rbegin(); it != list.rend(); ++it)
		{
			res += *it.base();
		}
		BOOST_CHECK(res == " worldHello");
		res.clear();

		for (auto it = list.crbegin(); it != list.crend(); ++it)
		{
			res += *it.base();
		}
		BOOST_CHECK(res == " worldHello");
	}

	BOOST_AUTO_TEST_CASE(able_use_operations_with_begin_and_end)
	{
		CStringList list = CreatNewOne();
		BOOST_CHECK(list.GetSize() == 2);
		BOOST_CHECK(list.GetBackElement() == " world");
		BOOST_CHECK(GetListAsString(list) == "Hello world");
		list.PushBack(" iterator test.");

		auto it = list.begin();
		BOOST_CHECK(*(it++) == " world");
	}

	BOOST_AUTO_TEST_CASE(able_insert_element_by_iterator)
	{
		CStringList list = CreatNewOne();
		BOOST_CHECK(list.GetSize() == 2);
		BOOST_CHECK(list.GetBackElement() == " world");
		list.PushBack(" test");
		BOOST_CHECK(GetListAsString(list) == "Hello world test");

		auto it = list.begin();
		list.Insert(it, std::string("Ok "));
		BOOST_CHECK(GetListAsString(list) == "Ok Hello world test");
		BOOST_CHECK(list.GetSize() == 4);

		std::string res;
		for (auto&& elem : list)
		{
			res += elem;
		}
		BOOST_CHECK(res == "Ok Hello world test");
	}

	BOOST_AUTO_TEST_CASE(able_insert_element_by_reverse_iterator)
	{
		CStringList list = CreatNewOne();
		BOOST_CHECK(list.GetSize() == 2);
		BOOST_CHECK(list.GetBackElement() == " world");
		list.PushBack(" test");
		BOOST_CHECK(GetListAsString(list) == "Hello world test");

		auto it = list.rbegin();
		list.Insert(it, std::string(" Ok"));
		BOOST_CHECK(GetListAsString(list) == "Hello world Ok test");
		BOOST_CHECK(list.GetSize() == 4);

		std::string res;
		for (auto&& elem : list)
		{
			res += elem;
		}
		BOOST_CHECK(res == "Hello world Ok test");
	}

	BOOST_AUTO_TEST_CASE(able_delete_element_by_iterator)
	{
		CStringList list = CreatNewOne();
		BOOST_CHECK(list.GetSize() == 2);
		BOOST_CHECK(list.GetBackElement() == " world");
		list.PushBack(" test");
		BOOST_CHECK(GetListAsString(list) == "Hello world test");

		auto it = list.begin();
		list.Delete(it);
		BOOST_CHECK(GetListAsString(list) == " world test");
		BOOST_CHECK(list.GetSize() == 2);
	}

	BOOST_AUTO_TEST_CASE(able_delete_element_by_reverse_iterator)
	{
		CStringList list = CreatNewOne();
		BOOST_CHECK(list.GetSize() == 2);
		BOOST_CHECK(list.GetBackElement() == " world");
		list.PushBack(" test");
		BOOST_CHECK(GetListAsString(list) == "Hello world test");

		auto it = list.rbegin();
		list.Delete(it);
		BOOST_CHECK(GetListAsString(list) == "Hello world");
		BOOST_CHECK(list.GetSize() == 2);
	}

BOOST_AUTO_TEST_SUITE_END()
