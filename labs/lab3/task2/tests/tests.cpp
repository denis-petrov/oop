#define CATCH_CONFIG_MAIN
#include "../../../../catch2/catch.hpp"
#include "../task2/Calculator.h"

using namespace std;

SCENARIO("Declare variable use (var)") 
{
	CCalculator calculator;

	WHEN("Variable that has never been used") 
	{
		REQUIRE(calculator.DeclareVariable("test"));
		REQUIRE(calculator.DeclareVariable("test2"));
	}

	WHEN("Variable that contains in calculator")
	{
		REQUIRE(calculator.DeclareVariable("test"));
		REQUIRE(calculator.DeclareVariable("test2"));

		REQUIRE(!calculator.DeclareVariable("test"));
		REQUIRE(!calculator.DeclareVariable("test2"));
	}

	WHEN("Variable is empty")
	{
		REQUIRE(!calculator.DeclareVariable(""));
	}
}

SCENARIO("Initialize variable use (let)") 
{
	CCalculator calculator;

	WHEN("Variable init by double value") 
	{
		REQUIRE(calculator.InitializeVariable("test1", "2.2"));
		REQUIRE(calculator.InitializeVariable("test2", "0"));
	}

	WHEN("Variable init by another variable")
	{
		REQUIRE(calculator.DeclareVariable("test"));
		REQUIRE(calculator.InitializeVariable("testInit1", "test"));
	}

	WHEN("Variable init by exsist variable")
	{
		REQUIRE(calculator.DeclareVariable("test"));
		REQUIRE(!calculator.InitializeVariable("test", "test"));
		REQUIRE(!calculator.InitializeVariable("test", "0.0"));
	}
}