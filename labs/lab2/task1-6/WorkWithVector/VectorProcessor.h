#pragma once

#include "stdafx.h"

bool ReadVectorOfDouble(std::istream& stream, std::vector<double>& vec);
std::vector<double> ProcessVector(const std::vector<double>& vec);
void PrintVector(std::ostream& out, const std::vector<double>& vec);
