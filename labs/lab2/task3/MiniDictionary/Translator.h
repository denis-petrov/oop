#pragma once

#include "stdafx.h"

std::map<std::string, std::string> UseTranslator(std::istream& input, std::ostream& output, const std::map<std::string, std::string>& dict);

std::string AddTransateToDictionry(std::istream& input, std::map<std::string, std::string>& userDict, const std::string& lineInLowerCase);
