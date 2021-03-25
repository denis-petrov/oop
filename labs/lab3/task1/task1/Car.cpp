#include "stdafx.h"
#include "Car.h"

using namespace std;

CCar::CCar()
	: m_isEngineOn(false)
	, m_gear(0)
	, m_speed(0)
	, m_direction(Direction::NONE)
{
}

CCar::~CCar()
{
}

/* Public methods */

// property access

bool CCar::IsEngineOn() const
{
	return m_isEngineOn;
}

int CCar::GetGear() const
{
	return m_gear;
}

int CCar::GetSpeed() const
{
	return m_speed;
}

CCar::Direction CCar::GetDirection() const
{
	return m_direction;
}


// Change state of instance

bool CCar::TurnOnEngine() 
{
	m_isEngineOn = IsAbleOnEngine();
	return m_isEngineOn;
}

bool CCar::TurnOffEngine() 
{
	m_isEngineOn = IsAbleOffEngine();
	return m_isEngineOn;
}

bool CCar::SetGear(const int gear)
{
	if (IsAbleChangeGear(gear))
	{
		m_gear = gear;
		return true;
	}
	return false;
}


/* Private sethods */

bool CCar::IsCarStay() const 
{
	return (m_gear == 0) && (m_speed == 0) && (m_direction == CCar::Direction::STAY);
}

bool CCar::IsAbleOnEngine() const
{
	return (m_isEngineOn) && IsCarStay();
}

bool CCar::IsAbleOffEngine() const
{
	return (!m_isEngineOn) && IsCarStay();
}

bool CCar::IsAbleChangeGear(const int gear) 
{
	// TODO
}

bool CCar::IsSpeedInRange(const pair<int, int>& range, const int speed) const 
{
	return (range.first <= speed) && (speed >= range.second);
}