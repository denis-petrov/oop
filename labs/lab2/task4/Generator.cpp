#include "stdafx.h"
#include "Generator.h"

using namespace std;

bool IsCorrectUpperBound(const int uppedBound)
{
	return (1 < uppedBound) && (uppedBound <= MAX_BOUND);
}

int GetUpperBound(const string& value)
{
	auto upperBound = boost::lexical_cast<int>(value);
	if (!IsCorrectUpperBound(upperBound))
	{
		throw bad_cast();
	}
	return upperBound;
}

void EraseNumberSequence(vector<bool>& sieve, const int current)
{
	for (size_t index = current * current; index < sieve.size(); index += current)
	{
		sieve[index] = false;
	}
}

void EraseCompositeNumbers(vector<bool>& sieve)
{
	for (size_t index = FIRST_PRIME; index <= sqrt(sieve.size()); index++)
	{
		if (sieve[index])
		{
			EraseNumberSequence(sieve, index);
		}
	}
}

set<int> SieveToSet(const vector<bool>& sieve)
{
	set<int> primes;

	for (size_t index = FIRST_PRIME; index < sieve.size(); index++)
	{
		if (sieve[index])
		{
			primes.insert(primes.end(), index);
		}
	}

	return primes;
}

set<int> GeneratePrimeNumbersSet(const int upperBound)
{
	vector<bool> sieve(upperBound + 1, true);
	EraseCompositeNumbers(sieve);

	return SieveToSet(sieve);
}