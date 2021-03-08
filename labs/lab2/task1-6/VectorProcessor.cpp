#include "stdafx.h"
#include "VectorProcessor.h"

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

	minElem = (minElem == 0) ? 1 : minElem;
	transform(vecStart, vecEnd, vecStart, [&maxElem, &minElem](auto& elem) { return (elem * maxElem) / minElem; });
	
	sort(vecStart, vecEnd);
}

void PrintVector(ostream& out, const vector<double>& vec)
{
	copy(vec.begin(), vec.end(), ostream_iterator<double>(out, " "));
}