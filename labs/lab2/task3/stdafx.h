#pragma once

#include "targetver.h"

#include <fstream>
#include <optional>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <unordered_map>

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>

#include <boost/serialization/map.hpp>
#include <boost/algorithm/string.hpp>

#include <stdio.h>
#include <windows.h>


const std::string EXIT = "...";
const std::string AGREE = "y";