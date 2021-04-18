#pragma once

#include "targetver.h"
#include <exception>
#include <iostream>
#include <regex>
#include <stdexcept>
#include <string>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

const std::regex URL_REGEX("(http|https)://([^/:]+):?([^/]*)(/?[^#?]*)");
const int DEFAULT_HTTP_PORT = 80;
const int DEFAULT_HTTPS_PORT = 443;
const std::string HTTP = "http";
const std::string HTTPS = "https";

const char SLASH = '/';

const int MIN_PORT = 1;
const int MAX_PORT = 65535;
