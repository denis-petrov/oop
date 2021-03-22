#define CATCH_CONFIG_MAIN
#include "../../../../catch2/catch.hpp"
#include "../PrimeNumbersGenerator/Generator.h"

SCENARIO("Test validation of upper bound") // 1 scenario
{
	GIVEN("Int")
	{
		WHEN("Bound less min value") // 1 case
		{
			REQUIRE(IsCorrectUpperBound(0) == false);

			REQUIRE(IsCorrectUpperBound(-2) == false);
		}

		WHEN("Bound is more than min value") // 2 case
		{
			REQUIRE(IsCorrectUpperBound(INT_MAX) == false);
		}

		WHEN("Bound is correct") // 3 case
		{
			REQUIRE(IsCorrectUpperBound(2) == true);

			REQUIRE(IsCorrectUpperBound(100) == true);
		}

		WHEN("Near to border value is correct") // 4 case
		{
			REQUIRE(IsCorrectUpperBound(1) == true);

			REQUIRE(IsCorrectUpperBound(100000000) == true);
		}
	}
}

SCENARIO("Convert bound from string to int with boost lexical cast") // 2 scenario
{
	GIVEN("String")
	{
		WHEN("Incorrect value") // 1 case
		{
			CHECK_THROWS(GetUpperBound("0"));

			CHECK_THROWS(GetUpperBound("-2"));

			CHECK_THROWS(GetUpperBound("lol"));
		}

		WHEN("Correct value") // 2 case
		{
			REQUIRE(GetUpperBound("10") == 10);

			REQUIRE(GetUpperBound("2") == 2);
		}

		WHEN("Near to border value is correct") // 3 case
		{
			REQUIRE(GetUpperBound("1") == 1);

			REQUIRE(GetUpperBound("100000000") == 100000000);
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
		std::set<int> expectedSet;

		WHEN("Not correct value(bound)") // 1 case
		{
			expectedSet = {};

			REQUIRE(GenerateSetOfPrimeNumbers(0) == expectedSet);
		}

		WHEN("Correct value(bound)") // 2 case
		{
			expectedSet = { 2, 3, 5, 7 };

			REQUIRE(GenerateSetOfPrimeNumbers(9) == expectedSet);
		}
	}
}