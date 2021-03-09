#pragma once

#include "stdafx.h"

bool IsCorrectUpperBound(const int uppedBound);
int GetUpperBound(const std::string& value);

void EraseNumberSequence(std::vector<bool>& sieve, const int current);
void EraseCompositeNumbers(std::vector<bool>& sieve);

std::set<int> SieveToSet(const std::vector<bool>& sieve);
std::set<int> GeneratePrimeNumbersSet(const int upperBound);