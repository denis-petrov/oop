#pragma once

#include "stdafx.h"

bool IsCorrectUpperBound(const int uppedBound);
int GetUpperBound(const std::string& value);

void EraseNumberSequence(std::vector<bool>& vec, const int current);
void EraseCompositeNumbers(std::vector<bool>& vec);

std::set<int> VectorToSet(const std::vector<bool>& vec);
std::set<int> GenerateSetOfPrimeNumbers(const int upperBound);