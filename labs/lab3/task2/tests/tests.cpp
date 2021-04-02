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
		REQUIRE(calculator.GetEntityValue("test").value() == "nan");

		REQUIRE(calculator.DeclareVariable("test2"));
		REQUIRE(calculator.GetEntityValue("test2").value() == "nan");
	}

	WHEN("Variable that contains in calculator")
	{
		REQUIRE(calculator.DeclareVariable("test"));
		REQUIRE(calculator.GetEntityValue("test").value() == "nan");

		REQUIRE(calculator.DeclareVariable("test2"));
		REQUIRE(calculator.GetEntityValue("test2").value() == "nan");

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
		REQUIRE(calculator.GetEntityValue("test1") == "2.20");

		REQUIRE(calculator.InitializeVariable("test2", "0"));
		REQUIRE(calculator.GetEntityValue("test2") == "0.00");
	}

	WHEN("Variable init by another variable")
	{
		REQUIRE(calculator.DeclareVariable("test"));
		REQUIRE(calculator.GetEntityValue("test").value() == "nan");

		REQUIRE(calculator.InitializeVariable("testInit1", "test"));
		REQUIRE(calculator.GetEntityValue("testInit1").value() == "nan");
	}

	WHEN("Variable init by exsist variable")
	{
		REQUIRE(calculator.DeclareVariable("test"));
		REQUIRE(calculator.GetEntityValue("test").value() == "nan");

		REQUIRE(calculator.InitializeVariable("test", "0"));
		REQUIRE(calculator.GetEntityValue("test").value() == "0.00");
	}
}

SCENARIO("Print variable by alphabet sort (printvars)")
{
	CCalculator calculator;

	WHEN("Variables is not empty")
	{
		REQUIRE(calculator.InitializeVariable("c", "11"));
		REQUIRE(calculator.GetEntityValue("c").value() == "11.00");

		REQUIRE(calculator.InitializeVariable("a", "2.2"));
		REQUIRE(calculator.GetEntityValue("a").value() == "2.20");

		REQUIRE(calculator.InitializeVariable("b", "c"));
		REQUIRE(calculator.GetEntityValue("b") == "11.00");
		REQUIRE(calculator.GetVariables() == "a:2.20\nb:11.00\nc:11.00\n");
	}

	WHEN("Variables is empty")
	{
		REQUIRE(calculator.GetVariables() == "");
	}

	WHEN("Variables is incorrect")
	{
		CHECK_THROWS(calculator.InitializeVariable("a", "#"));
		CHECK_THROWS(calculator.InitializeVariable("a", "!"));
		CHECK_THROWS(calculator.InitializeVariable("a", "="));
		CHECK_THROWS(calculator.InitializeVariable("a", "+"));
	}
}

SCENARIO("Initialize function (fn)") 
{
	CCalculator calculator;

	GIVEN("Init by variable") 
	{
		WHEN("Variable is init") 
		{
			REQUIRE(calculator.InitializeVariable("testVar", "11"));
			REQUIRE(calculator.GetEntityValue("testVar").value() == "11.00");
			REQUIRE(calculator.InitializeFunction("testFn", "testVar"));
		}

		WHEN("Variable is not init")
		{
			REQUIRE(!calculator.InitializeFunction("testFn", "testVar"));
		}
	}

	GIVEN("Init by function")
	{
		WHEN("Function is init by another function")
		{
			REQUIRE(calculator.InitializeVariable("testVar", "11"));
			REQUIRE(calculator.GetEntityValue("testVar").value() == "11.00");

			REQUIRE(calculator.InitializeFunction("testFn", "testVar"));

			REQUIRE(calculator.InitializeFunction("testFn2", "testFn"));
		}

		WHEN("Function is init by variable")
		{
			REQUIRE(calculator.InitializeVariable("testVar", "11"));
			REQUIRE(calculator.GetEntityValue("testVar").value() == "11.00");

			REQUIRE(calculator.InitializeFunction("testFn", "testVar"));
		}

		WHEN("Function is not init cause initialize func not init")
		{
			REQUIRE(!calculator.InitializeFunction("testFn", "testFunc"));
		}

	}

	GIVEN("Init by action")
	{
		WHEN("First and second variable is not init") 
		{
			REQUIRE(!calculator.InitializeFunction("testFn", "first", '*', "second"));
		}

		WHEN("First variable is not init")
		{
			REQUIRE(calculator.InitializeVariable("second", "11"));
			REQUIRE(!calculator.InitializeFunction("testFn", "first", '*', "second"));
		}

		WHEN("Second variable is not init")
		{
			REQUIRE(calculator.InitializeVariable("first", "11"));
			REQUIRE(!calculator.InitializeFunction("testFn", "first", '*', "second"));
		}

		WHEN("Init by 2 variables")
		{
			REQUIRE(calculator.InitializeVariable("first", "11"));
			REQUIRE(calculator.InitializeVariable("second", "11"));
			REQUIRE(calculator.InitializeFunction("testFn", "first", '*', "second"));
		}

		WHEN("Init by function and variable")
		{
			REQUIRE(calculator.InitializeVariable("first", "11"));
			REQUIRE(calculator.InitializeFunction("firstFunc", "first"));

			REQUIRE(calculator.InitializeVariable("second", "11"));
			REQUIRE(calculator.InitializeFunction("testFn", "firstFunc", '*', "second"));
		}

		WHEN("Init by variable and function")
		{
			REQUIRE(calculator.InitializeVariable("first", "11"));

			REQUIRE(calculator.InitializeVariable("second", "11"));
			REQUIRE(calculator.InitializeFunction("secondFunc", "second"));

			REQUIRE(calculator.InitializeFunction("testFn", "first", '*', "secondFunc"));
		}

		WHEN("Init by 2 functions")
		{
			REQUIRE(calculator.InitializeVariable("first", "11"));
			REQUIRE(calculator.InitializeVariable("second", "11"));

			REQUIRE(calculator.InitializeFunction("firstFunc", "first"));
			REQUIRE(calculator.InitializeFunction("secondFunc", "second"));

			REQUIRE(calculator.InitializeFunction("testFn", "firstFunc", '*', "secondFunc"));
		}

		WHEN("Not correct operation") 
		{
			REQUIRE(calculator.InitializeVariable("first", "11"));
			REQUIRE(calculator.InitializeVariable("second", "11"));

			REQUIRE(!calculator.InitializeFunction("first", "firstFunc", '#', "second"));
			REQUIRE(!calculator.InitializeFunction("first", "firstFunc", '@', "second"));
			REQUIRE(!calculator.InitializeFunction("first", "firstFunc", '1', "second"));
			REQUIRE(!calculator.InitializeFunction("first", "firstFunc", 'd', "second"));
			REQUIRE(!calculator.InitializeFunction("first", "firstFunc", ' ', "second"));
			REQUIRE(!calculator.InitializeFunction("first", "firstFunc", '\n', "second"));
		}
	}
}