#pragma once

#include "targetver.h"

#include <fstream>
#include <iostream>
#include <map>
#include <optional>
#include <sstream>
#include <string>
#include <unordered_map>
#include <optional>

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>

#include <boost/algorithm/string.hpp>
#include <boost/serialization/map.hpp>

#include <stdio.h>
#include <windows.h>

const std::string EXIT = "...";
const std::string AGREE = "y";