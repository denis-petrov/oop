#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

bool ReadVectorOfDouble(std::istream& stream, std::vector<double>& vec)
{
	vec.clear();

	std::copy(std::istream_iterator<double>(stream),
		std::istream_iterator<double>(),
		std::back_inserter<std::vector<double>>(vec));

	return !vec.empty();
}

/*
*	All vec elems *= maxElem / minElem
*	Sort elements in vector
*/
void ProcessVector(std::vector<double>& vec) 
{
	auto vecStart = vec.begin();
	auto vecEnd = vec.end();

	auto maxElem = *std::max_element(vecStart, vecEnd);
	auto minElem = *std::min_element(vecStart, vecEnd);

	std::transform(vecStart, vecEnd, vecStart, [&maxElem, &minElem](auto& elem) { return (elem * maxElem) / minElem; });

	std::sort(vecStart, vecEnd);
}

void PrintVector(std::ostream& out, const std::vector<double>& vec)
{
	std::copy(vec.begin(), vec.end(), std::ostream_iterator<double>(out, " "));
}

int main(int argc, char* argv[])
{
	std::vector<double> vec;

	if (!ReadVectorOfDouble(std::cin, vec))
	{
		std::cout << "Please enter a number sequence.\n";
		return 1;
	}

	ProcessVector(vec);

	PrintVector(std::cout, vec);

	return 0;
}
