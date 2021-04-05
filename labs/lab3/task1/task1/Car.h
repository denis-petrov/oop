#pragma once
#include "stdafx.h"

class CCar
{
public:
	enum class Direction
	{
		STAY,
		FORWARD,
		BACK
	};

	CCar();
	~CCar();

	bool IsEngineOn() const;
	int GetGear() const;
	int GetSpeed() const;
	Direction GetDirection() const;

	std::string ToString() const;

	bool TurnOnEngine();
	bool TurnOffEngine();

	bool SetGear(int gear);
	bool SetSpeed(int speed);

private:
	bool m_isEngineOn;
	int m_gear;
	int m_speed;
	Direction m_direction;

	bool IsCarStay() const;
	bool IsAbleOnEngine() const;
	bool IsAbleOffEngine() const;
	bool IsAbleChangeGear(const int gear) const;

	std::pair<int, int> GetSpeedRange(const int gear) const;
	bool IsAbleChangeSpeed(const int speed) const;

	void UpdateDirection();

	bool IsSpeedInRange(const std::pair<int, int>& range, const int speed) const;
};

