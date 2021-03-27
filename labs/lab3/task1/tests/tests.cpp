#define CATCH_CONFIG_MAIN
#include "../../../../catch2/catch.hpp"
#include "../task1/Car.h"

using namespace std;

bool IsCarStateNotChandged(const CCar& car) 
{
	return true;
}


SCENARIO("Validate new car") 
{
	CCar car;

	REQUIRE(!car.IsEngineOn());
	REQUIRE(car.GetGear() == 0);
	REQUIRE(car.GetSpeed() == 0);
	REQUIRE(car.GetDirection() == CCar::Direction::STAY);
}

SCENARIO("Validate turn on engine")
{
	CCar car;

	REQUIRE(car.TurnOnEngine());
	REQUIRE(car.IsEngineOn());
	REQUIRE(car.GetGear() == 0);
	REQUIRE(car.GetSpeed() == 0);
	REQUIRE(car.GetDirection() == CCar::Direction::STAY);
}

SCENARIO("Validate turn off engine")
{
	CCar car;

	REQUIRE(car.TurnOnEngine());
	REQUIRE(car.TurnOffEngine());
	REQUIRE(!car.IsEngineOn());
	REQUIRE(car.GetGear() == 0);
	REQUIRE(car.GetSpeed() == 0);
	REQUIRE(car.GetDirection() == CCar::Direction::STAY);
}

SCENARIO("Validate first gear change") 
{
	GIVEN("Car with first gear") 
	{
		CCar car;

		REQUIRE(car.TurnOnEngine());
		REQUIRE(car.SetGear(1));
		REQUIRE(car.GetGear() == 1);

		WHEN("Speed is max value")
		{
			REQUIRE(car.SetSpeed(30));
			REQUIRE(car.GetSpeed() == 30);
			REQUIRE(car.GetDirection() == CCar::Direction::FORWARD);
		}

		WHEN("Speed is more than max value")
		{
			REQUIRE(!car.SetSpeed(31));
			REQUIRE(car.GetSpeed() == 0);
			REQUIRE(car.GetDirection() == CCar::Direction::STAY);
		}

		WHEN("Speed is min value")
		{
			REQUIRE(car.SetSpeed(0));
			REQUIRE(car.GetSpeed() == 0);
			REQUIRE(car.GetDirection() == CCar::Direction::STAY);
		}

		WHEN("Speed is less than min value")
		{
			REQUIRE(!car.SetSpeed(-1));
			REQUIRE(car.GetSpeed() == 0);
			REQUIRE(car.GetDirection() == CCar::Direction::STAY);
		}
	}
}

SCENARIO("Validate second gear change")
{
	GIVEN("Car with second gear")
	{
		CCar car;

		REQUIRE(car.TurnOnEngine());
		REQUIRE(car.SetGear(1));
		REQUIRE(car.GetGear() == 1);
		REQUIRE(car.SetSpeed(20));
		REQUIRE(car.SetGear(2));
		REQUIRE(car.GetGear() == 2);

		WHEN("Speed is max value")
		{
			REQUIRE(car.SetSpeed(50));
			REQUIRE(car.GetSpeed() == 50);
			REQUIRE(car.GetDirection() == CCar::Direction::FORWARD);
		}

		WHEN("Speed is more than max value")
		{
			REQUIRE(!car.SetSpeed(51));
			REQUIRE(car.GetSpeed() == 20);
			REQUIRE(car.GetDirection() == CCar::Direction::FORWARD);
		}

		WHEN("Speed is min value")
		{
			REQUIRE(car.SetSpeed(20));
			REQUIRE(car.GetSpeed() == 20);
			REQUIRE(car.GetDirection() == CCar::Direction::FORWARD);
		}

		WHEN("Speed is less than min value")
		{
			REQUIRE(!car.SetSpeed(19));
			REQUIRE(car.GetSpeed() == 20);
			REQUIRE(car.GetDirection() == CCar::Direction::FORWARD);
		}
	}
}

SCENARIO("Validate third gear change")
{
	GIVEN("Car with third gear")
	{
		CCar car;

		REQUIRE(car.TurnOnEngine());
		REQUIRE(car.SetGear(1));
		REQUIRE(car.GetGear() == 1);

		REQUIRE(car.SetSpeed(20));
		REQUIRE(car.SetGear(2));
		REQUIRE(car.GetGear() == 2);

		REQUIRE(car.SetSpeed(30));
		REQUIRE(car.SetGear(3));
		REQUIRE(car.GetGear() == 3);

		WHEN("Speed is max value")
		{
			REQUIRE(car.SetSpeed(60));
			REQUIRE(car.GetSpeed() == 60);
			REQUIRE(car.GetDirection() == CCar::Direction::FORWARD);
		}

		WHEN("Speed is more than max value")
		{
			REQUIRE(!car.SetSpeed(61));
			REQUIRE(car.GetSpeed() == 30);
			REQUIRE(car.GetDirection() == CCar::Direction::FORWARD);
		}

		WHEN("Speed is min value")
		{
			REQUIRE(car.SetSpeed(30));
			REQUIRE(car.GetSpeed() == 30);
			REQUIRE(car.GetDirection() == CCar::Direction::FORWARD);
		}

		WHEN("Speed is less than min value")
		{
			REQUIRE(!car.SetSpeed(29));
			REQUIRE(car.GetSpeed() == 30);
			REQUIRE(car.GetDirection() == CCar::Direction::FORWARD);
		}
	}
}

SCENARIO("Validate fourth gear change")
{
	GIVEN("Car with fourth gear")
	{
		CCar car;

		REQUIRE(car.TurnOnEngine());
		REQUIRE(car.SetGear(1));
		REQUIRE(car.GetGear() == 1);

		REQUIRE(car.SetSpeed(20));
		REQUIRE(car.SetGear(2));
		REQUIRE(car.GetGear() == 2);

		REQUIRE(car.SetSpeed(30));
		REQUIRE(car.SetGear(3));
		REQUIRE(car.GetGear() == 3);
		
		REQUIRE(car.SetSpeed(40));
		REQUIRE(car.SetGear(4));
		REQUIRE(car.GetGear() == 4);

		WHEN("Speed is max value")
		{
			REQUIRE(car.SetSpeed(90));
			REQUIRE(car.GetSpeed() == 90);
			REQUIRE(car.GetDirection() == CCar::Direction::FORWARD);
		}

		WHEN("Speed is more than max value")
		{
			REQUIRE(!car.SetSpeed(91));
			REQUIRE(car.GetSpeed() == 40);
			REQUIRE(car.GetDirection() == CCar::Direction::FORWARD);
		}

		WHEN("Speed is min value")
		{
			REQUIRE(car.SetSpeed(40));
			REQUIRE(car.GetSpeed() == 40);
			REQUIRE(car.GetDirection() == CCar::Direction::FORWARD);
		}

		WHEN("Speed is less than min value")
		{
			REQUIRE(!car.SetSpeed(39));
			REQUIRE(car.GetSpeed() == 40);
			REQUIRE(car.GetDirection() == CCar::Direction::FORWARD);
		}
	}
}

SCENARIO("Validate fifth gear change")
{
	GIVEN("Car with fifth gear")
	{
		CCar car;

		REQUIRE(car.TurnOnEngine());
		REQUIRE(car.SetGear(1));
		REQUIRE(car.GetGear() == 1);

		REQUIRE(car.SetSpeed(20));
		REQUIRE(car.GetSpeed() == 20);
		REQUIRE(car.SetGear(2));
		REQUIRE(car.GetGear() == 2);

		REQUIRE(car.SetSpeed(30));
		REQUIRE(car.SetGear(3));
		REQUIRE(car.GetGear() == 3);

		REQUIRE(car.SetSpeed(40));
		REQUIRE(car.SetGear(4));
		REQUIRE(car.GetGear() == 4);
		
		REQUIRE(car.SetSpeed(50));
		REQUIRE(car.SetGear(5));
		REQUIRE(car.GetGear() == 5);

		WHEN("Speed is max value")
		{
			REQUIRE(car.SetSpeed(150));
			REQUIRE(car.GetSpeed() == 150);
			REQUIRE(car.GetDirection() == CCar::Direction::FORWARD);
		}

		WHEN("Speed is more than max value")
		{
			REQUIRE(!car.SetSpeed(151));
			REQUIRE(car.GetSpeed() == 50);
			REQUIRE(car.GetDirection() == CCar::Direction::FORWARD);
		}

		WHEN("Speed is min value")
		{
			REQUIRE(car.SetSpeed(50));
			REQUIRE(car.GetSpeed() == 50);
			REQUIRE(car.GetDirection() == CCar::Direction::FORWARD);
		}

		WHEN("Speed is less than min value")
		{
			REQUIRE(!car.SetSpeed(49));
			REQUIRE(car.GetSpeed() == 50);
			REQUIRE(car.GetDirection() == CCar::Direction::FORWARD);
		}
	}
}

SCENARIO("Validate change gear to back") 
{
	GIVEN("Car with back gear")
	{
		CCar car;

		REQUIRE(car.TurnOnEngine());
		REQUIRE(car.SetGear(-1));
		REQUIRE(car.GetGear() == -1);
		REQUIRE(car.SetSpeed(20));
		REQUIRE(car.GetSpeed() == 20);

		WHEN("Speed is max value")
		{
			REQUIRE(car.SetSpeed(20));
			REQUIRE(car.GetSpeed() == 20);
			REQUIRE(car.GetDirection() == CCar::Direction::BACK);
		}

		WHEN("Speed is more than max value")
		{
			REQUIRE(!car.SetSpeed(21));
			REQUIRE(car.GetSpeed() == 20);
			REQUIRE(car.GetDirection() == CCar::Direction::BACK);
		}

		WHEN("Speed is min value")
		{
			REQUIRE(car.SetSpeed(0));
			REQUIRE(car.GetSpeed() == 0);
			REQUIRE(car.GetDirection() == CCar::Direction::STAY);
		}

		WHEN("Speed is less than min value")
		{
			REQUIRE(!car.SetSpeed(-1));
			REQUIRE(car.GetSpeed() == 20);
			REQUIRE(car.GetDirection() == CCar::Direction::BACK);
		}
	}
}

SCENARIO("Change incorrect gear") 
{
	GIVEN("Car with gear") 
	{
		CCar car;

		REQUIRE(car.TurnOnEngine());
		REQUIRE(car.SetGear(1));
		REQUIRE(car.GetGear() == 1);
		REQUIRE(car.SetSpeed(20));

		WHEN("Try to switch gear more than one unit") 
		{
			REQUIRE(!car.SetGear(-1));
			REQUIRE(!car.SetGear(3));
			REQUIRE(!car.SetGear(4));
			REQUIRE(!car.SetGear(5));
		}
	}
}

SCENARIO("Change incorrect speed")
{
	GIVEN("Car with first gear")
	{
		CCar car;

		REQUIRE(car.TurnOnEngine());
		REQUIRE(car.SetGear(1));
		REQUIRE(car.GetGear() == 1);
		REQUIRE(car.SetSpeed(20));

		WHEN("Try to switch gear more than one unit")
		{
			REQUIRE(!car.SetSpeed(100));
			REQUIRE(!car.SetGear(21));
			REQUIRE(!car.SetGear(-20));
			REQUIRE(!car.SetGear(-1));
		}
	}
}