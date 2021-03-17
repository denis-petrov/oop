#pragma once

#include "stdafx.h"

std::vector<double> ReadVectorOfDouble(std::istream& stream, const std::vector<double>& vec);
std::vector<double> ProcessVector(const std::vector<double>& vec);
void PrintVector(std::ostream& out, const std::vector<double>& vec);
