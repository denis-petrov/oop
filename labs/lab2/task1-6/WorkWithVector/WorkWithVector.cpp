#include "stdafx.h"
#include "VectorProcessor.h"

using namespace std;

int main()
{
	vector<double> vec;

	if (!ReadVectorOfDouble(cin, vec))
	{
		cout << "Please enter a number sequence.\n";
		return 1;
	}

	auto processedVec = ProcessVector(vec);

	PrintVector(cout, processedVec);

	return 0;
}
