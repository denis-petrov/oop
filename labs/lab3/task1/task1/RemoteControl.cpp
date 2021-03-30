#include "stdafx.h"
#include "RemoteControl.h"
#include "Car.h"

using namespace std;

const string HELP_FILE_NAME = "help.txt";

CRemoteControl::CRemoteControl(CCar& car, std::istream& input, std::ostream& output)
	: m_car(car)
	, m_input(input)
	, m_output(output)
	, m_isEndInput(false)
	, m_actionMap({
		  { "Help", bind(&CRemoteControl::Help, this) },
		  { "Info", bind(&CRemoteControl::Info, this) },
		  { "EngineOn", bind(&CRemoteControl::EngineOn, this) },
		  { "EngineOff", bind(&CRemoteControl::EngineOff, this) },
		  { "SetSpeed", bind(&CRemoteControl::SetSpeed, this) },
		  { "SetGear", bind(&CRemoteControl::SetGear, this) },
		  { "End", bind(&CRemoteControl::End, this) },
	  })
{
}

bool CRemoteControl::HandleCommand()
{
	string action;
	if (!(m_input >> action))
	{
		return false;
	}

	m_isEndInput = (action == "End") ? true : false;

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		it->second();
		return true;
	}

	return false;
}

bool CRemoteControl::IsEndInput() const 
{
	return m_isEndInput;
}

void CRemoteControl::Help()
{
	ifstream source(HELP_FILE_NAME);

	istreambuf_iterator<char> beginSource(source);
	istreambuf_iterator<char> endSource;
	ostreambuf_iterator<char> beginDest(m_output);
	copy(beginSource, endSource, beginDest);
	
	m_output << "\n\n";
}

void CRemoteControl::Info()
{
	m_output << m_car.ToString() << "\n\n";
}

void CRemoteControl::EngineOn()
{
	if (m_car.TurnOnEngine())
	{
		m_output << "Engine has started.\n\n";
	}
	else
	{
		m_output << "Engine is already working.\n\n";
	}
}

void CRemoteControl::EngineOff()
{
	if (m_car.TurnOffEngine())
	{
		m_output << "Engine has stoped.\n\n";
	}
	else
	{
		m_output << "Is not able to stop engine now.\n\n";
	}
}

void CRemoteControl::SetSpeed()
{
	int argument;
	m_input >> argument;
	if (m_car.SetSpeed(argument))
	{
		m_output << "New speed equal: " << argument << "\n\n";
	}
	else
	{
		m_output << "Can not set speed equal: " << argument << "\n\n";
	}
}

void CRemoteControl::SetGear()
{
	int argument;
	m_input >> argument;
	if (m_car.SetGear(argument))
	{
		m_output << "New gear equal: " << argument << "\n\n";
	}
	else
	{
		m_output << "Can not set gear equal: " << argument << "\n\n";
	}
}

void CRemoteControl::End()
{
	m_output << "Goodbye.\n\n";
}