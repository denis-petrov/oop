#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

bool ReadVectorOfDouble(istream& stream, vector<double>& vec)
{
	vec.clear();
	istream_iterator<double> start(stream);
	istream_iterator<double> end;

	copy(start, end, back_inserter(vec));

	return !vec.empty();
}

/*
*	All vec elems *= maxElem / minElem
*	Sort elements in vector
*/
void ProcessVector(vector<double>& vec) 
{
	auto vecStart = vec.begin();
	auto vecEnd = vec.end();

	auto maxElem = *max_element(vecStart, vecEnd);
	auto minElem = *min_element(vecStart, vecEnd);

	transform(vecStart, vecEnd, vecStart, [&maxElem, &minElem](auto& elem) { return (elem * maxElem) / minElem; });

	sort(vecStart, vecEnd);
}

void PrintVector(ostream& out, const vector<double>& vec)
{
	copy(vec.begin(), vec.end(), ostream_iterator<double>(out, " "));
}

int main(int argc, char* argv[])
{
	vector<double> vec;

	if (!ReadVectorOfDouble(cin, vec))
	{
		cout << "Please enter a number sequence.\n";
		return 1;
	}

	ProcessVector(vec);

	PrintVector(std::cout, vec);

	return 0;
}
