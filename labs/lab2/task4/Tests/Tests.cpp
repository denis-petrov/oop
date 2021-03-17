#define CATCH_CONFIG_MAIN
#include "../../../../catch2/catch.hpp"
#include "../PrimeNumbersGenerator/Generator.h"

SCENARIO("Test validation of upper bound") // 1 scenario
{
	GIVEN("Int")
	{
		int bound;

		WHEN("Bound less min value") // 1 case
		{
			bound = 0;

			REQUIRE(IsCorrectUpperBound(bound) == false);

			bound = -2;

			REQUIRE(IsCorrectUpperBound(bound) == false);
		}

		WHEN("Bound is more than min value") // 2 case
		{
			bound = INT_MAX;

			REQUIRE(IsCorrectUpperBound(bound) == false);
		}

		WHEN("Bound is correct") // 3 case
		{
			bound = 2;

			REQUIRE(IsCorrectUpperBound(bound) == true);

			bound = 100;

			REQUIRE(IsCorrectUpperBound(bound) == true);
		}
	}
}

SCENARIO("Convert bound from stringto int with boost lexical cast") // 2 scenario
{
	GIVEN("String")
	{
		std::string value;
		int expectedValue;

		WHEN("Incorrect value") // 1 case
		{
			value = "0";

			CHECK_THROWS(GetUpperBound(value));

			value = "-2";

			CHECK_THROWS(GetUpperBound(value));

			value = "lol";

			CHECK_THROWS(GetUpperBound(value));
		}

		WHEN("Correct value") // 2 case
		{
			value = "10";
			expectedValue = 10;

			REQUIRE(GetUpperBound(value) == expectedValue);

			value = "2";
			expectedValue = 2;

			REQUIRE(GetUpperBound(value) == expectedValue);
		}
	}
}

SCENARIO("Erase Composite Numbers") // 3 scenario
{
	GIVEN("Vector")
	{
		std::vector<bool> vec;
		std::vector<bool> expectedVec;

		WHEN("Empty vector") // 1 case
		{
			vec = {};
			expectedVec = {};
			WipeCompositeNumbers(vec);

			REQUIRE(vec == expectedVec);
		}

		WHEN("Not empty vector contains value 0 to 9") // 2 case
		{
			vec = { true, true, true, true, true, true, true, true, true };
			expectedVec = { true, true, true, true, false, true, false, true, false };
			WipeCompositeNumbers(vec);

			REQUIRE(vec == expectedVec);
		}
	}
}

SCENARIO("Convert vector to set") // 4 scenario
{
	GIVEN("Vector")
	{
		std::vector<bool> vec;
		std::set<int> expectedSet;

		WHEN("Empty vector") // 1 case
		{
			vec = {};
			expectedSet = {};

			REQUIRE(VectorToSet(vec) == expectedSet);
		}

		WHEN("Not empty vector contains value 0 to 9") // 2 case
		{
			vec = { true, true, true, true, false, true, false, true, false };
			expectedSet = { 2, 3, 5, 7};

			REQUIRE(VectorToSet(vec) == expectedSet);
		}
	}
}

SCENARIO("Generate set of prime numbers") // 5 scenario
{
	GIVEN("Int value")
	{
		int value;
		std::set<int> expectedSet;

		WHEN("Not correct value(bound)") // 1 case
		{
			value = 0;
			expectedSet = {};

			REQUIRE(GenerateSetOfPrimeNumbers(value) == expectedSet);
		}

		WHEN("Correct value(bound)") // 2 case
		{
			value = 9;
			expectedSet = { 2, 3, 5, 7 };

			REQUIRE(GenerateSetOfPrimeNumbers(value) == expectedSet);
		}
	}
}