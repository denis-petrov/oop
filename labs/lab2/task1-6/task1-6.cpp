#include "stdafx.h"
#include "VectorProcessor.h"

using namespace std;

int main(int argc, char* argv[])
{
	vector<double> vec;

	if (!ReadVectorOfDouble(cin, vec))
	{
		cout << "Please enter a number sequence.\n";
		return 1;
	}

	ProcessVector(vec);

	PrintVector(cout, vec);

	return 0;
}
