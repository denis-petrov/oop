#include "stdafx.h"
#include "VectorProcessor.h"

using namespace std;

int main()
{
	vector<double> vec = ReadVectorOfDouble(cin, vec);

	if (vec.empty())
	{
		cout << "Please enter a number sequence.\n";
		return 1;
	}

	auto processedVec = ProcessVector(vec);

	PrintVector(cout, processedVec);

	return 0;
}
