#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#define _USE_MATH_DEFINES
#include <iomanip>
#include <math.h>
#include <string>
#include "../string/MyString.h"
#include "../string/Iterator.h"
#include <string.h>
#include <cassert>

#include <boost/algorithm/string/replace.hpp>
#include <boost/test/execution_monitor.hpp>  

#define BOOST_TEST_INCLUDED
#pragma warning(disable : 4702)
#include <boost/test/unit_test.hpp>

CMyString generateItem(const std::string& str);

CMyString generateEmptyItem();