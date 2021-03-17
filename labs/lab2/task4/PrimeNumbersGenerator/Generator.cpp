#include "stdafx.h"
#include "Generator.h"

using namespace std;

bool IsCorrectUpperBound(const int uppedBound)
{
	return (MIN_BOUND <= uppedBound) && (uppedBound <= MAX_BOUND);
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

void WipeSequence(vector<bool>& vec, const int current)
{
	for (size_t index = current * current; index < vec.size(); index += current)
	{
		vec[index] = false;
	}
}

void WipeCompositeNumbers(vector<bool>& vec)
{
	for (size_t index = FIRST_PRIME; index <= sqrt(vec.size()); index++)
	{
		if (vec[index])
		{
			WipeSequence(vec, index);
		}
	}
}

set<int> VectorToSet(const vector<bool>& vec)
{
	set<int> primes;

	for (size_t index = FIRST_PRIME; index < vec.size(); index++)
	{
		if (vec[index])
		{
			primes.insert(index);
		}
	}

	return primes;
}

set<int> GenerateSetOfPrimeNumbers(const int upperBound)
{
	vector<bool> sieve(upperBound + 1, true);
	WipeCompositeNumbers(sieve);

	return VectorToSet(sieve);
}