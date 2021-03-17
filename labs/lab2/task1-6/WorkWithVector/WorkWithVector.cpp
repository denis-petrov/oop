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

	vector<double> processedVec;
	try
	{
		processedVec = ProcessVector(vec);
	}
	catch (const runtime_error& e)
	{
		cout << e.what() << "\n";
		return 1;
	}
	

	PrintVector(cout, processedVec);

	return 0;
}
