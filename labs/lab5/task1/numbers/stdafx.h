#pragma once

#include "targetver.h"
#include <exception>
#include <stdexcept>
#include <iostream>
#include <string>
#include <regex>
#include "boost/lexical_cast.hpp"

#define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers

const int DEFAULT_NUMERATOR = 0;
const int DEFAULT_DENOMINATOR = 1;
const int NOT_CORRECT_DENOMINATOR = 0;