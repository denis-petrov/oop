#pragma once

#include "stdafx.h"

bool IsCorrectUpperBound(const int uppedBound);
int GetUpperBound(const std::string& value);

void WipeSequence(std::vector<bool>& vec, const int current);
void WipeCompositeNumbers(std::vector<bool>& vec);

std::set<int> VectorToSet(const std::vector<bool>& vec);
std::set<int> GenerateSetOfPrimeNumbers(const int upperBound);