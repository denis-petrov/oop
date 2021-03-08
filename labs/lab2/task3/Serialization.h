#pragma once

#include "stdafx.h"

void SerializeDictionary(const std::map<std::string, std::string>& dict, const std::string& fname);
std::map<std::string, std::string> DeserializeDictionary(const std::string& fname);
void SaveDictionaty(const std::string& fname, std::istream& input, std::ostream& output, const std::map<std::string, std::string>& dict, const std::map<std::string, std::string>& tempDict);
