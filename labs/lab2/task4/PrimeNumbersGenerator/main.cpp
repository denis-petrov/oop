#include "stdafx.h"
#include "Generator.h"

using namespace std;

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		cout << "Not valid count of arguments.\nUse: task4.exe <upper bound>.\n";
		return 1;
	}

	int upperBound;
	try
	{
		upperBound = GetUpperBound(argv[1]);
	}
	catch (bad_cast const&)
	{
		cout << "Invalid <upper bound> - less then 2 or more t hen 100 000 000\n";
		return 1;
	}

	auto primes = GenerateSetOfPrimeNumbers(upperBound);

	ostream_iterator<int> output(cout, " ");
	copy(primes.begin(), primes.end(), output);
	cout << endl;

	return 0;
}
