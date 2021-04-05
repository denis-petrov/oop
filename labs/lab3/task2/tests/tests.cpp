#define CATCH_CONFIG_MAIN
#include "../../../../catch2/catch.hpp"
#include "../task2/Calculator.h"

using namespace std;

bool TestALotOfActions() 
{
	CCalculator calculator;

	calculator.InitializeVariable("x", "1");
	string xPrev = "x";
	for (size_t i = 2; i <= 100000; i++)
	{
		string xNew = "x"s + to_string(i);
		calculator.InitializeFunction(xNew, xPrev, '+', "x");
		xPrev = xNew;
	}
	return (calculator.GetEntityValue("x100000") == "100000.00");
}

SCENARIO("Declare variable use (var)") 
{
	CCalculator calculator;

	WHEN("Variable that has never been used") 
	{
		REQUIRE(calculator.DeclareVariable("test"));
		REQUIRE(calculator.GetEntityValue("test") == "nan");

		REQUIRE(calculator.DeclareVariable("test2"));
		REQUIRE(calculator.GetEntityValue("test2") == "nan");
	}

	WHEN("Variable that contains in calculator")
	{
		REQUIRE(calculator.DeclareVariable("test"));
		REQUIRE(calculator.GetEntityValue("test") == "nan");

		REQUIRE(calculator.DeclareVariable("test2"));
		REQUIRE(calculator.GetEntityValue("test2") == "nan");

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
		REQUIRE(calculator.GetEntityValue("test") == "nan");

		REQUIRE(calculator.InitializeVariable("testInit1", "test"));
		REQUIRE(calculator.GetEntityValue("testInit1") == "nan");
	}

	WHEN("Variable init by exsist variable")
	{
		REQUIRE(calculator.DeclareVariable("test"));
		REQUIRE(calculator.GetEntityValue("test") == "nan");

		REQUIRE(calculator.InitializeVariable("test", "0"));
		REQUIRE(calculator.GetEntityValue("test") == "0.00");
	}
}

SCENARIO("Print variable by alphabet sort (printvars)")
{
	CCalculator calculator;

	WHEN("Variables is not empty")
	{
		REQUIRE(calculator.InitializeVariable("c", "11"));
		REQUIRE(calculator.GetEntityValue("c") == "11.00");

		REQUIRE(calculator.InitializeVariable("a", "2.2"));
		REQUIRE(calculator.GetEntityValue("a") == "2.20");

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
			REQUIRE(calculator.GetEntityValue("testVar") == "11.00");
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
			REQUIRE(calculator.GetEntityValue("testVar") == "11.00");

			REQUIRE(calculator.InitializeFunction("testFn", "testVar"));

			REQUIRE(calculator.InitializeFunction("testFn2", "testFn"));
		}

		WHEN("Function is init by variable")
		{
			REQUIRE(calculator.InitializeVariable("testVar", "11"));
			REQUIRE(calculator.GetEntityValue("testVar") == "11.00");

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

SCENARIO("Calculate function (print fn)") 
{
	CCalculator calculator;

	WHEN("fn is not exist")
	{
		CHECK_THROWS(calculator.GetEntityValue("fn"));
	}

	WHEN("short fn init by NAN variable")
	{
		REQUIRE(calculator.DeclareVariable("first"));
		REQUIRE(calculator.InitializeFunction("fn", "first"));
		REQUIRE(calculator.GetEntityValue("fn") == "nan");
	}

	WHEN("fn init by variable")
	{
		REQUIRE(calculator.InitializeVariable("first", "11"));
		REQUIRE(calculator.InitializeFunction("fn", "first"));
		REQUIRE(calculator.GetEntityValue("fn") == "11.00");
	}

	WHEN("fn init by variable")
	{
		REQUIRE(calculator.InitializeVariable("first", "11"));
		REQUIRE(calculator.InitializeVariable("second", "11"));
		REQUIRE(calculator.InitializeFunction("fn", "first", '+', "second"));
		REQUIRE(calculator.GetEntityValue("fn") == "22.00");
	}

	WHEN("full fn init by NAN variable")
	{
		REQUIRE(calculator.DeclareVariable("first"));
		REQUIRE(calculator.InitializeVariable("second", "11"));
		REQUIRE(calculator.InitializeFunction("fn", "first", '+', "second"));
		REQUIRE(calculator.GetEntityValue("fn") == "nan");
	}

	WHEN("full fn init by variable, check sub")
	{
		REQUIRE(calculator.InitializeVariable("first", "11"));
		REQUIRE(calculator.InitializeVariable("second", "11"));
		REQUIRE(calculator.InitializeFunction("fn", "first", '-', "second"));
		REQUIRE(calculator.GetEntityValue("fn") == "0.00");
	}

	WHEN("full fn init by variable, check multiplication")
	{
		REQUIRE(calculator.InitializeVariable("first", "11"));
		REQUIRE(calculator.InitializeVariable("second", "11"));
		REQUIRE(calculator.InitializeFunction("fn", "first", '*', "second"));
		REQUIRE(calculator.GetEntityValue("fn") == "121.00");
	}

	WHEN("full fn init by variable, check division")
	{
		REQUIRE(calculator.InitializeVariable("first", "11"));
		REQUIRE(calculator.InitializeVariable("second", "11"));
		REQUIRE(calculator.InitializeFunction("fn", "first", '/', "second"));
		REQUIRE(calculator.GetEntityValue("fn") == "1.00");
	}

	WHEN("full fn init by variable, check division by 0")
	{
		REQUIRE(calculator.InitializeVariable("first", "11"));
		REQUIRE(calculator.InitializeVariable("second", "0"));
		REQUIRE(calculator.InitializeFunction("fn", "first", '/', "second"));
		REQUIRE(calculator.GetEntityValue("fn") == "Division by 0");
	}

	WHEN("short fn2 init by short fn")
	{
		REQUIRE(calculator.InitializeVariable("first", "11"));
		REQUIRE(calculator.InitializeFunction("fn", "first"));
		REQUIRE(calculator.GetEntityValue("fn") == "11.00");

		REQUIRE(calculator.InitializeFunction("fn2", "fn"));
		REQUIRE(calculator.GetEntityValue("fn2") == "11.00");
	}

	WHEN("short fn2 init by full fn")
	{
		REQUIRE(calculator.InitializeVariable("first", "11"));
		REQUIRE(calculator.InitializeVariable("second", "11"));
		REQUIRE(calculator.InitializeFunction("fn", "first", '+', "second"));
		REQUIRE(calculator.GetEntityValue("fn") == "22.00");

		REQUIRE(calculator.InitializeFunction("fn2", "fn"));
		REQUIRE(calculator.GetEntityValue("fn2") == "22.00");
	}

	WHEN("full fn3 init by full fn1 and full fn2")
	{
		REQUIRE(calculator.InitializeVariable("first", "11"));
		REQUIRE(calculator.InitializeVariable("second", "11"));

		REQUIRE(calculator.InitializeFunction("fn1", "first", '+', "second"));
		REQUIRE(calculator.GetEntityValue("fn1") == "22.00");

		REQUIRE(calculator.InitializeFunction("fn2", "first", '+', "second"));
		REQUIRE(calculator.GetEntityValue("fn2") == "22.00");

		REQUIRE(calculator.InitializeFunction("fn3", "fn1", '+', "fn2"));
		REQUIRE(calculator.GetEntityValue("fn3") == "44.00");
	}

	WHEN("full fn3 init by full fn1 and variable")
	{
		REQUIRE(calculator.InitializeVariable("first", "11"));
		REQUIRE(calculator.InitializeVariable("second", "11"));

		REQUIRE(calculator.InitializeFunction("fn1", "first", '+', "second"));
		REQUIRE(calculator.GetEntityValue("fn1") == "22.00");

		REQUIRE(calculator.InitializeFunction("fn3", "fn1", '+', "second"));
		REQUIRE(calculator.GetEntityValue("fn3") == "33.00");
	}

	WHEN("full fn3 init by variable and full fn1")
	{
		REQUIRE(calculator.InitializeVariable("first", "11"));
		REQUIRE(calculator.InitializeVariable("second", "11"));

		REQUIRE(calculator.InitializeFunction("fn1", "first", '+', "second"));
		REQUIRE(calculator.GetEntityValue("fn1") == "22.00");

		REQUIRE(calculator.InitializeFunction("fn3", "first", '+', "fn1"));
		REQUIRE(calculator.GetEntityValue("fn3") == "33.00");
	}

	WHEN("full fn3 init by NAN variable and full fn1 with NAN")
	{
		REQUIRE(calculator.DeclareVariable("first"));
		REQUIRE(calculator.InitializeVariable("second", "11"));

		REQUIRE(calculator.InitializeFunction("fn1", "first", '+', "second"));
		REQUIRE(calculator.GetEntityValue("fn1") == "nan");

		REQUIRE(calculator.InitializeFunction("fn3", "first", '+', "fn1"));
		REQUIRE(calculator.GetEntityValue("fn3") == "nan");
	}
}

SCENARIO("Check print <identificator>") 
{
	CCalculator calculator;

	WHEN("Variable or Function does not init") 
	{
		CHECK_THROWS(calculator.GetEntityValue("fn3"));
	}

	WHEN("Variable init")
	{
		REQUIRE(calculator.DeclareVariable("first"));
		REQUIRE(calculator.GetEntityValue("first") == "nan");
	}
}

SCENARIO("Check printfns")
{
	CCalculator calculator;

	WHEN("Functions does not init")
	{
		REQUIRE(calculator.GetFunctions().empty());
	}

	WHEN("Function was init")
	{
		REQUIRE(calculator.DeclareVariable("first"));
		REQUIRE(calculator.InitializeVariable("second", "11"));

		REQUIRE(calculator.InitializeFunction("fn1", "first", '+', "second"));
		REQUIRE(calculator.GetEntityValue("fn1") == "nan");

		REQUIRE(calculator.GetFunctions() == "fn1:nan\n");
	}

	WHEN("Functions was init")
	{
		REQUIRE(calculator.DeclareVariable("first"));
		REQUIRE(calculator.InitializeVariable("second", "11"));

		REQUIRE(calculator.InitializeFunction("fn1", "first", '+', "second"));
		REQUIRE(calculator.GetEntityValue("fn1") == "nan");

		REQUIRE(calculator.InitializeVariable("first", "22"));
		REQUIRE(calculator.InitializeFunction("fn2", "first", '-', "second"));
		REQUIRE(calculator.GetEntityValue("fn2") == "11.00");

		REQUIRE(calculator.GetFunctions() == "fn1:33.00\nfn2:11.00\n");
	}
}

SCENARIO("Test a lot of action ") 
{
	REQUIRE(TestALotOfActions());
}