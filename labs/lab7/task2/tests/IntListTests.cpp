#include "stdafx.h"
#include "../list/List.h"
#include <list>

struct List_
{
};

CList<int> CreatNewOne()
{
	CList<int> list;
	list.PushBack(1);
	list.PushBack(2);
	return list;
}

int const GetListAsInt(CList<int> const& list)
{
	int res = 0;
	for (auto it = list.cbegin(); it != list.cend(); ++it)
	{
		res += (*it);
	}
	return res;
}

BOOST_FIXTURE_TEST_SUITE(IntList_tests, List_)

	BOOST_AUTO_TEST_CASE(all_iterators_is_equal_on_empty_list)
	{
		CList<int> list;
		BOOST_CHECK(list.begin() == list.end());
		BOOST_CHECK(list.cbegin() == list.cend());
		BOOST_CHECK(list.rbegin() == list.rend());
		BOOST_CHECK(list.crbegin() == list.crend());
	}

	BOOST_AUTO_TEST_CASE(able_PushBack_node)
	{
		CList<int> list;
		list.PushBack(1);
		BOOST_CHECK(list.GetSize() == 1);

		list.PushBack(2);
		BOOST_CHECK(list.GetSize() == 2);
		BOOST_CHECK(GetListAsInt(list) == 3);
	}

	BOOST_AUTO_TEST_CASE(able_PushFront_node)
	{
		CList<int> list;
		list.PushFront(1);
		BOOST_CHECK(list.GetSize() == 1);

		list.PushFront(2);
		BOOST_CHECK(list.GetSize() == 2);

		BOOST_CHECK(GetListAsInt(list) == 3);
	}

	BOOST_AUTO_TEST_CASE(able_clear_list)
	{
		CList<int> list;
		list.PushBack(1);
		list.PushBack(2);
		BOOST_CHECK(list.GetSize() == 2);
		BOOST_CHECK(GetListAsInt(list) == 3);
		list.Clear();
		BOOST_CHECK(list.GetSize() == 0);
	}

	BOOST_AUTO_TEST_CASE(able_use_move_constructor)
	{
		CList<int> list;
		list.PushBack(1);
		list.PushBack(2);
		BOOST_CHECK(list.GetSize() == 2);
		BOOST_CHECK(GetListAsInt(list) == 3);

		CList<int> list2 = list;	
		std::cout << list2.GetSize()
		<< "\n";
		BOOST_CHECK(list2.GetSize() == 2);
		BOOST_CHECK(GetListAsInt(list2) == 3);

		CList<int> list3 = list2;
		BOOST_CHECK(list3.GetSize() == 2);
		list3.PushBack(3);
		BOOST_CHECK(GetListAsInt(list3) == 6);
	}

	BOOST_AUTO_TEST_CASE(able_use_replace_constructor)
	{
		CList<int> list = CreatNewOne();
		BOOST_CHECK(list.GetSize() == 2);
		BOOST_CHECK(GetListAsInt(list) == 3);
	}

	BOOST_AUTO_TEST_CASE(able_use_iterator)
	{
		CList<int> list = CreatNewOne();
		BOOST_CHECK(list.GetSize() == 2);
		BOOST_CHECK(GetListAsInt(list) == 3);

		int res = 0;
		for (auto&& elem : list)
		{
			res += elem;
		}
		BOOST_CHECK(res == 3);
		res = 0;

		for (auto it = list.begin(); it != list.end(); ++it)
		{
			res += (*it);
		}
		BOOST_CHECK(res == 3);

		res = 0;

		for (auto it = list.cbegin(); it != list.cend(); ++it)
		{
			res += (*it);
		}
		BOOST_CHECK(res == 3);
	}

	BOOST_AUTO_TEST_CASE(able_use_reverse_iterator)
	{
		CList<int> list = CreatNewOne();
		BOOST_CHECK(list.GetSize() == 2);
		BOOST_CHECK(GetListAsInt(list) == 3);

		int res = 0;
		for (auto it = list.rbegin(); it != list.rend(); it++)
		{
			res += *it;
		}
		BOOST_CHECK(res == 3);
		res = 0;

		for (auto it = list.crbegin(); it != list.crend(); it++)
		{
			res += *it;
		}
		BOOST_CHECK(res == 3);
	}

	BOOST_AUTO_TEST_CASE(able_use_operations_with_begin_and_end)
	{
		CList<int> list = CreatNewOne();
		BOOST_CHECK(list.GetSize() == 2);
		BOOST_CHECK(GetListAsInt(list) == 3);
		list.PushBack(3);

		auto it = list.begin();
		BOOST_CHECK(*(it++) == 2);

		auto itEnd = list.end();
		BOOST_CHECK(*(--itEnd) == 3);
		BOOST_CHECK(*(itEnd--) == 2);
	}

	BOOST_AUTO_TEST_CASE(able_insert_element_to_empty_list_by_iterator)
	{
		CList<int> list;
		BOOST_CHECK(list.GetSize() == 0);

		auto it = list.begin();
		list.Insert(it, 1);
		BOOST_CHECK(GetListAsInt(list) == 1);
		BOOST_CHECK(list.GetSize() == 1);

		int res = 0;
		for (auto&& elem : list)
		{
			res += elem;
		}
		BOOST_CHECK(res == 1);
	}

	BOOST_AUTO_TEST_CASE(able_insert_element_by_iterator)
	{
		CList<int> list = CreatNewOne();
		BOOST_CHECK(list.GetSize() == 2);
		list.PushBack(3);
		BOOST_CHECK(GetListAsInt(list) == 6);

		auto it = list.begin();
		list.Insert(it, 3);
		BOOST_CHECK(GetListAsInt(list) == 9);
		BOOST_CHECK(list.GetSize() == 4);

		int res = 0;
		for (auto&& elem : list)
		{
			res += elem;
		}
		BOOST_CHECK(res == 9);
	}


	BOOST_AUTO_TEST_CASE(throw_when_delete_null_element_by_iterator)
	{
		CList<int> list;
		auto itB = list.begin();
		BOOST_CHECK_THROW(list.Delete(itB), std::invalid_argument);
		auto itE = list.end();
		BOOST_CHECK_THROW(list.Delete(itE), std::invalid_argument);
	}

	BOOST_AUTO_TEST_CASE(able_delete_element_by_iterator)
	{
		CList<int> list = CreatNewOne();
		BOOST_CHECK(list.GetSize() == 2);
		list.PushBack(3);
		BOOST_CHECK(GetListAsInt(list) == 6);

		auto it = list.begin();
		list.Delete(it);
		BOOST_CHECK(GetListAsInt(list) == 5);
		BOOST_CHECK(list.GetSize() == 2);
	}

	BOOST_AUTO_TEST_CASE(able_use_equal_operator)
	{
		CList<int> list = CreatNewOne();
		BOOST_CHECK(list.GetSize() == 2);
		list.PushBack(3);
		BOOST_CHECK(GetListAsInt(list) == 6);

		auto list2 = list;
		BOOST_CHECK(list2.GetSize() == 3);
		list2.PushBack(3);
		BOOST_CHECK(GetListAsInt(list2) == 9);
	}

BOOST_AUTO_TEST_SUITE_END()
