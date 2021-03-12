#pragma once

#include "stdafx.h"

void SerializeDictionary(const std::string& fname, const std::map<std::string, std::string>& dict);
std::map<std::string, std::string> DeserializeDictionary(const std::string& fname);

bool SaveDictionary(const std::string& fname, std::istream& input, const std::map<std::string, std::string>& userDict);
bool IsUserChangeDictionary(const std::map<std::string, std::string>& dict, const std::map<std::string, std::string>& userDict);