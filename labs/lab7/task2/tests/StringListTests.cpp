#include "stdafx.h"
#include "../list/List.h"

struct List_
{
};

CList<std::string> CreatNewOne()
{
	CList<std::string> list;
	list.PushBack("Hello");
	list.PushBack(" world");
	return list;
}

std::string const GetListAsString(CList<std::string> const& list)
{
	std::string res;
	for (auto it = list.cbegin(); it != list.cend(); ++it)
	{
		std::cout << "1";
		//res += (*it).value();
	}
	return res;
}

BOOST_FIXTURE_TEST_SUITE(StringList_tests, List_)

	BOOST_AUTO_TEST_CASE(able_PushBack_node)
	{
		CList<std::string> list;
		//list.PushBack("Hello");
		//BOOST_CHECK(list.GetSize() == 1);
		//BOOST_CHECK(list.GetBackElement().value() == "Hello");

		//list.PushBack(" world");
		//BOOST_CHECK(list.GetSize() == 2);
		//BOOST_CHECK(list.GetBackElement().value() == " world");
		//BOOST_CHECK(GetListAsString(list) == "Hello world");
	}

	//BOOST_AUTO_TEST_CASE(able_PushFront_node)
	//{
	//	CList<std::string> list;
	//	list.PushFront("Hello");
	//	BOOST_CHECK(list.GetSize() == 1);
	//	BOOST_CHECK(list.GetBackElement() == "Hello");

	//	list.PushFront(" world");
	//	BOOST_CHECK(list.GetSize() == 2);
	//	BOOST_CHECK(list.GetBackElement() == "Hello");

	//	BOOST_CHECK(GetListAsString(list) == " worldHello");
	//}

	//BOOST_AUTO_TEST_CASE(able_clear_list)
	//{
	//	CList<std::string> list;
	//	list.PushBack("Hello");
	//	list.PushBack(" world");
	//	BOOST_CHECK(list.GetSize() == 2);
	//	BOOST_CHECK(list.GetBackElement() == " world");
	//	BOOST_CHECK(GetListAsString(list) == "Hello world");
	//	list.Clear();
	//	BOOST_CHECK(list.GetSize() == 0);
	//}

	//BOOST_AUTO_TEST_CASE(able_use_move_constructor)
	//{
	//	CList<std::string> list;
	//	list.PushBack("Hello");
	//	list.PushBack(" world");
	//	BOOST_CHECK(list.GetSize() == 2);
	//	BOOST_CHECK(list.GetBackElement() == " world");
	//	BOOST_CHECK(GetListAsString(list) == "Hello world");

	//	CList<std::string> list2(list);
	//	BOOST_CHECK(list2.GetSize() == 2);
	//	BOOST_CHECK(list2.GetBackElement() == " world");
	//	BOOST_CHECK(GetListAsString(list2) == "Hello world");

	//	CList<std::string> list3(list2);
	//	BOOST_CHECK(list3.GetSize() == 2);
	//	BOOST_CHECK(list3.GetBackElement() == " world");
	//	list3.PushBack(" lol");
	//	BOOST_CHECK(GetListAsString(list3) == "Hello world lol");
	//}

	//BOOST_AUTO_TEST_CASE(able_use_replace_constructor)
	//{
	//	CList<std::string> list = CreatNewOne();
	//	BOOST_CHECK(list.GetSize() == 2);
	//	BOOST_CHECK(list.GetBackElement() == " world");
	//	BOOST_CHECK(GetListAsString(list) == "Hello world");
	//}

	//BOOST_AUTO_TEST_CASE(able_use_iterator)
	//{
	//	CList<std::string> list = CreatNewOne();
	//	BOOST_CHECK(list.GetSize() == 2);
	//	BOOST_CHECK(list.GetBackElement() == " world");
	//	BOOST_CHECK(GetListAsString(list) == "Hello world");

	//	std::string res;
	//	for (auto&& elem : list)
	//	{
	//		//res += elem.value();
	//		std::cout << "1\n";
	//	}
	//	BOOST_CHECK(res == "Hello world");
	//	res.clear();

	//	for (auto it = list.begin(); it != list.end(); ++it)
	//	{
	//		//res += (*it).value();
	//	}
	//	BOOST_CHECK(res == "Hello world");

	//	res.clear();

	//	for (auto it = list.cbegin(); it != list.cend(); ++it)
	//	{
	//		//res += (*it).value();
	//	}
	//	BOOST_CHECK(res == "Hello world");
	//}

	//BOOST_AUTO_TEST_CASE(able_use_reverse_iterator)
	//{
	//	CList<std::string> list = CreatNewOne();
	//	BOOST_CHECK(list.GetSize() == 2);
	//	BOOST_CHECK(list.GetBackElement() == " world");
	//	BOOST_CHECK(GetListAsString(list) == "Hello world");

	//	std::string res;
	//	for (auto it = list.rbegin(); it != list.rend(); it++)
	//	{
	//		//res += *it;
	//	}
	//	BOOST_CHECK(res == " worldHello");
	//	res.clear();

	//	for (auto it = list.crbegin(); it != list.crend(); it++)
	//	{
	//		//res += *it;
	//	}
	//	BOOST_CHECK(res == " worldHello");
	//}

	//BOOST_AUTO_TEST_CASE(able_use_operations_with_begin_and_end)
	//{
	//	CList<std::string> list = CreatNewOne();
	//	BOOST_CHECK(list.GetSize() == 2);
	//	BOOST_CHECK(list.GetBackElement() == " world");
	//	BOOST_CHECK(GetListAsString(list) == "Hello world");
	//	list.PushBack(" iterator test.");

	//	auto it = list.begin();
	//	BOOST_CHECK(*(it++) == " world");

	//	auto itEnd = list.end();
	//	BOOST_CHECK(*(--itEnd) == " iterator test.");
	//	BOOST_CHECK(*(itEnd--) == " world");
	//}

	//BOOST_AUTO_TEST_CASE(able_insert_element_to_empty_list_by_iterator)
	//{
	//	CList<std::string> list;
	//	BOOST_CHECK(list.GetSize() == 0);
	//	BOOST_CHECK(GetListAsString(list) == "");

	//	auto it = list.begin();
	//	list.Insert(it, std::string("Ok "));
	//	BOOST_CHECK(GetListAsString(list) == "Ok ");
	//	BOOST_CHECK(list.GetSize() == 1);

	//	std::string res;
	//	for (auto&& elem : list)
	//	{
	//		//res += elem.value();
	//	}
	//	BOOST_CHECK(res == "Ok ");
	//}

	//BOOST_AUTO_TEST_CASE(able_insert_element_by_iterator)
	//{
	//	CList<std::string> list = CreatNewOne();
	//	BOOST_CHECK(list.GetSize() == 2);
	//	BOOST_CHECK(list.GetBackElement() == " world");
	//	list.PushBack(" test");
	//	BOOST_CHECK(GetListAsString(list) == "Hello world test");

	//	auto it = list.begin();
	//	list.Insert(it, std::string("Ok "));
	//	BOOST_CHECK(GetListAsString(list) == "Ok Hello world test");
	//	BOOST_CHECK(list.GetSize() == 4);

	//	std::string res;
	//	for (auto&& elem : list)
	//	{
	//		//res += elem.value();
	//	}
	//	BOOST_CHECK(res == "Ok Hello world test");
	//}

	//BOOST_AUTO_TEST_CASE(able_insert_element_to_empty_list_by_reverse_iterator)
	//{
	//	CList<std::string> list;
	//	BOOST_CHECK(list.GetSize() == 0);
	//	BOOST_CHECK(GetListAsString(list) == "");

	//	auto it = list.rbegin();
	//	list.Insert(it, std::string("Ok "));
	//	BOOST_CHECK(GetListAsString(list) == "Ok ");
	//	BOOST_CHECK(list.GetSize() == 1);

	//	std::string res;
	//	for (auto&& elem : list)
	//	{
	//		//res += elem.value();
	//	}
	//	BOOST_CHECK(res == "Ok ");
	//}

	//BOOST_AUTO_TEST_CASE(able_insert_element_by_reverse_iterator)
	//{
	//	CList<std::string> list = CreatNewOne();
	//	BOOST_CHECK(list.GetSize() == 2);
	//	BOOST_CHECK(list.GetBackElement() == " world");
	//	list.PushBack(" test");
	//	BOOST_CHECK(GetListAsString(list) == "Hello world test");

	//	auto it = list.rbegin();
	//	list.Insert(it, std::string(" Ok"));
	//	BOOST_CHECK(GetListAsString(list) == "Hello world test Ok");
	//	BOOST_CHECK(list.GetSize() == 4);

	//	std::string res;
	//	for (auto&& elem : list)
	//	{
	//		//res += elem.value();
	//	}
	//	BOOST_CHECK(res == "Hello world test Ok");
	//}

	/*BOOST_AUTO_TEST_CASE(throw_when_delete_null_element_by_iterator)
	{
		CList<std::string> list;
		auto itB = list.begin();
		BOOST_CHECK_THROW(list.Delete(itB), std::invalid_argument);
		auto itE = list.end();
		BOOST_CHECK_THROW(list.Delete(itE), std::invalid_argument);
	}

	BOOST_AUTO_TEST_CASE(able_delete_element_by_iterator)
	{
		CList<std::string> list = CreatNewOne();
		BOOST_CHECK(list.GetSize() == 2);
		BOOST_CHECK(list.GetBackElement() == " world");
		list.PushBack(" test");
		BOOST_CHECK(GetListAsString(list) == "Hello world test");

		auto it = list.begin();
		list.Delete(it);
		BOOST_CHECK(GetListAsString(list) == " world test");
		BOOST_CHECK(list.GetSize() == 2);
	}

	BOOST_AUTO_TEST_CASE(throw_when_delete_null_element_by_reverse_iterator)
	{
		CList<std::string> list;
		auto itRB = list.rbegin();
		BOOST_CHECK_THROW(list.Delete(itRB), std::invalid_argument);
		auto itRE = list.rend();
		BOOST_CHECK_THROW(list.Delete(itRE), std::invalid_argument);
	}

	BOOST_AUTO_TEST_CASE(able_delete_element_by_reverse_iterator)
	{
		CList<std::string> list = CreatNewOne();
		BOOST_CHECK(list.GetSize() == 2);
		BOOST_CHECK(list.GetBackElement() == " world");
		list.PushBack(" test");
		BOOST_CHECK(GetListAsString(list) == "Hello world test");

		auto it = list.rbegin();
		list.Delete(it);
		BOOST_CHECK(GetListAsString(list) == "Hello world");
		BOOST_CHECK(list.GetSize() == 2);
	}*/

BOOST_AUTO_TEST_SUITE_END()
