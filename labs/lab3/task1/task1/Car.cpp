#include "stdafx.h"
#include "Car.h"

using namespace std;

const map<int, pair<int, int>> SPEED_BY_GEAR{
	{ -1, { 0, 20 } },
	{ 0, { 0, 150 } },
	{ 1, { 0, 30 } },
	{ 2, { 20, 50 } },
	{ 3, { 30, 60 } },
	{ 4, { 40, 90 } },
	{ 5, { 50, 150 } }
};

const map<CCar::Direction, string> STRING_BY_DIRECTION{
	{ CCar::Direction::BACK, "Back" },
	{ CCar::Direction::FORWARD, "Forward" },
	{ CCar::Direction::STAY, "Stay" },
};

const pair<int, int> DEFAULT_SPEED_RANGE = { 0, 0 };
const int MIN_GEAR = -1;
const int MAX_GEAR = 5;


CCar::CCar()
	: m_isEngineOn(false)
	, m_gear(0)
	, m_speed(0)
	, m_direction(Direction::STAY)
{
}

CCar::~CCar()
{
}

/* Public methods */

// Property access

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

string CCar::ToString() const 
{
	string isEngineOn = CCar::IsEngineOn() ? "Working" : "Not working";

	string direction = STRING_BY_DIRECTION.at(CCar::GetDirection());

	return (string) "Car info:\n" + (string) "Engine working: " + isEngineOn + +"\nDirection: " + direction
		+ "\nGear: " + to_string(CCar::GetGear()) + "\nSpeed: " + to_string(CCar::GetSpeed());
}

// Change state of instance

bool CCar::TurnOnEngine()
{
	m_isEngineOn = IsAbleOnEngine();
	return m_isEngineOn;
}

bool CCar::TurnOffEngine()
{
	m_isEngineOn = !IsAbleOffEngine();
	return !m_isEngineOn;
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

bool CCar::SetSpeed(const int speed) 
{
	if (IsAbleChangeSpeed(speed))
	{
		m_speed = speed;
		UpdateDirection();
		return true;
	}
	return false;
}

/* Private methods */

bool CCar::IsCarStay() const
{
	return (m_gear == 0) && (m_speed == 0) && (m_direction == CCar::Direction::STAY);
}

bool CCar::IsAbleOnEngine() const
{
	return (!m_isEngineOn) && IsCarStay();
}

bool CCar::IsAbleOffEngine() const
{
	return m_isEngineOn && IsCarStay();
}

bool CCar::IsAbleChangeGear(const int gear) const
{
	bool IsGearCorrect = (MIN_GEAR <= gear) && (gear <= MAX_GEAR);

	bool IsSpeedInNewGearRange = IsSpeedInRange(GetSpeedRange(gear), m_speed);

	bool IsDirectionCorrect = (gear == 0) || (m_direction == Direction::STAY) ||
		(gear > 0 && m_direction == Direction::FORWARD) || (gear < 0 && m_direction == Direction::BACK);

	return IsGearCorrect && IsSpeedInNewGearRange && IsDirectionCorrect;
}

bool CCar::IsAbleChangeSpeed(const int speed) const 
{
	return (m_gear == 0 && speed < m_speed) || (m_gear != 0 && IsSpeedInRange(GetSpeedRange(m_gear), speed));
}

void CCar::UpdateDirection() 
{
	if (m_speed == 0)
	{
		m_direction = Direction::STAY;
	}
	else if (m_gear > 0)
	{
		m_direction = Direction::FORWARD;
	}
	else if (m_gear < 0)
	{
		m_direction = Direction::BACK;
	}
}

pair<int, int> CCar::GetSpeedRange(const int gear) const
{
	try
	{
		return SPEED_BY_GEAR.at(gear);
	}
	catch (const out_of_range&)
	{
		return DEFAULT_SPEED_RANGE;
	}
}

bool CCar::IsSpeedInRange(const pair<int, int>& range, const int speed) const
{
	return (range.first <= speed) && (speed <= range.second);
}
