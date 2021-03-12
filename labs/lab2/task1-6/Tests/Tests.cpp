// Tests.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../../catch2/catch.hpp"

#include "../WorkWithVector/VectorProcessor.h"


SCENARIO("Vector processing with a vector gives sotred processed vector")
{
	GIVEN("A vector with some items")
	{
		std::vector<double> vec;
		std::vector<double> expectedResult;

		WHEN("A vector contains only one item") 
		{
			vec = { 1.0 };
			REQUIRE(ProcessVector(vec) == vec);
		}

		WHEN("A vector where lower value is zero")
		{
			vec = { 0.0, 1.0, 2.0 };
			expectedResult = { 0.0, 2.0, 4.0 };
			REQUIRE(ProcessVector(vec) == expectedResult);
		}

		WHEN("A vector where lower value less zero")
		{
			vec = { -1.0, 1.0, 2.0 };
			std::vector<double> expectedResult = { -4.0, -2.0, 2.0 };
			REQUIRE(ProcessVector(vec) == expectedResult);
		}

		WHEN("A vector contains repeated one items")
		{
			vec = { 1.0, 1.0, 1.0 };
			expectedResult = { 1.0, 1.0, 1.0 };
			REQUIRE(ProcessVector(vec) == expectedResult);
		}

		WHEN("A vector contains repeated zero")
		{
			vec = { 0, 0, 0 };
			expectedResult = { 0, 0, 0 };
			REQUIRE(ProcessVector(vec) == expectedResult);
		}
	}

	GIVEN("An empty vector")
	{
		std::vector<double> empty = {};
		REQUIRE(ProcessVector(empty).size() == 0);
	}
}