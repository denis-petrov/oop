#pragma once
#include <vector>

template <typename T, typename Less>
bool FindMax(std::vector<T> const& arr, T& maxValue, Less const& less)
{
	if (arr.empty())
		return false;

	size_t indexOfMax = 0;
	for (size_t i = 0; i < arr.size(); i++)
	{
		if (!less(arr[i], arr[indexOfMax]))
			indexOfMax = i;
	}

	maxValue = arr[indexOfMax];
	return true;
}