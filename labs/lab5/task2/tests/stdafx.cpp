// stdafx.cpp : source file that includes just the standard includes
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

#define BOOST_TEST_NO_MAIN
#include <boost/test/included/unit_test.hpp>

CMyString generateItem(const std::string& str)
{
	return CMyString(str);
}

CMyString generateEmptyItem()
{
	return CMyString();
}