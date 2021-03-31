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
		REQUIRE(isnan(calculator.GetVariableValue("test")));

		REQUIRE(calculator.DeclareVariable("test2"));
		REQUIRE(isnan(calculator.GetVariableValue("test2")));
	}

	WHEN("Variable that contains in calculator")
	{
		REQUIRE(calculator.DeclareVariable("test"));
		REQUIRE(isnan(calculator.GetVariableValue("test")));

		REQUIRE(calculator.DeclareVariable("test2"));
		REQUIRE(isnan(calculator.GetVariableValue("test2")));

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
		REQUIRE(calculator.GetVariableValue("test1") == 2.20);

		REQUIRE(calculator.InitializeVariable("test2", "0"));
		REQUIRE(calculator.GetVariableValue("test2") == 0);
	}

	WHEN("Variable init by another variable")
	{
		REQUIRE(calculator.DeclareVariable("test"));
		REQUIRE(isnan(calculator.GetVariableValue("test")));

		REQUIRE(calculator.InitializeVariable("testInit1", "test"));
		REQUIRE(isnan(calculator.GetVariableValue("testInit1")));
	}

	WHEN("Variable init by exsist variable")
	{
		REQUIRE(calculator.DeclareVariable("test"));
		REQUIRE(isnan(calculator.GetVariableValue("test")));

		REQUIRE(calculator.InitializeVariable("test", "0"));
		REQUIRE(calculator.GetVariableValue("test") == 0.00);
	}
}

SCENARIO("Print variable by alphabet sort (printvars)")
{
	CCalculator calculator;

	WHEN("Variables is not empty")
	{
		REQUIRE(calculator.InitializeVariable("c", "11"));
		REQUIRE(calculator.GetVariableValue("c") == 11);

		REQUIRE(calculator.InitializeVariable("a", "2.2"));
		REQUIRE(calculator.GetVariableValue("a") == 2.20);

		REQUIRE(calculator.InitializeVariable("b", "c"));
		REQUIRE(calculator.GetVariableValue("b") == 11);
		REQUIRE(calculator.GetVariables() == "a:2.20\nb:11.00\nc:11.00\n");
	}

	WHEN("Variables is empty")
	{
		REQUIRE(calculator.GetVariables() == "");
	}
}