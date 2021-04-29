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

		for (auto it = list.cbegin(); it != list.cend(); it++)
		{
			res += *it;
		}
		BOOST_CHECK(res == "Hello world");
		std::sort(res.begin(), res.end());
	}

	BOOST_AUTO_TEST_CASE(able_use_operations_with_begin_and_end)
	{
		CStringList list = CreatNewOne();
		BOOST_CHECK(list.GetSize() == 2);
		BOOST_CHECK(list.GetBackElement() == " world");
		BOOST_CHECK(GetListAsString(list) == "Hello world");
		list.PushBack(" iterator test.");

		auto it = list.begin();
		it++;
		BOOST_CHECK(*it == " world");
		++it;
		BOOST_CHECK(*it == " iterator test.");
		--it;
		BOOST_CHECK(*it == " world");
		it--;
		BOOST_CHECK(*it == "Hello");
		it += 2;
		BOOST_CHECK(*it == " iterator test.");
		it -= 2;
		BOOST_CHECK(*it == "Hello");
	}

	BOOST_AUTO_TEST_CASE(throw_invalid_argument_if_not_correct_offset_in_operation)
	{
		CStringList list = CreatNewOne();
		BOOST_CHECK(list.GetSize() == 2);
		BOOST_CHECK(list.GetBackElement() == " world");
		BOOST_CHECK(GetListAsString(list) == "Hello world");
		list.PushBack(" iterator test.");

		auto it = list.begin();
		BOOST_CHECK_THROW(it += 10, std::invalid_argument);
		BOOST_CHECK_THROW(it -= 10, std::invalid_argument);
	}

	/*BOOST_AUTO_TEST_CASE(able_use_reverse_iterator)
	{
		CStringList list = CreatNewOne();
		BOOST_CHECK(list.GetSize() == 2);
		BOOST_CHECK(list.GetBackElement() == " world");
		BOOST_CHECK(GetListAsString(list) == "Hello world");
		std::string res;
		for (auto it = list.rbegin(); it != list.rend(); it++)
		{
			res += *it;
		}
		BOOST_CHECK(res == " worldHello");
	}*/

BOOST_AUTO_TEST_SUITE_END()
