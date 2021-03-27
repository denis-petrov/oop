#include "stdafx.h"
#include "Car.h"

using namespace std;

enum class Action
{
	Help,
	Info,
	SetSpeed,
	SetGear,
	EngineOn,
	EngineOff,
	End
};

struct Command
{
	Action action;
	int argument;
};

const map<string, Action> ACTION_BY_STRING{
	{ "Help", Action::Help },
	{ "Info", Action::Info },
	{ "EngineOn", Action::EngineOn },
	{ "EngineOff", Action::EngineOff },
	{ "SetSpeed", Action::SetSpeed },
	{ "SetGear", Action::SetGear },
	{ "End", Action::End },
};

void ExecuteHelp(CCar& car, const int argument) 
{
	ifstream source("help.txt");

	istreambuf_iterator<char> begin_source(source);
	istreambuf_iterator<char> end_source;
	ostreambuf_iterator<char> begin_dest(cout);
	copy(begin_source, end_source, begin_dest);
	cout << "\n\n";
}

void ExecuteInfo(CCar& car, const int argument)
{
	cout << car.ToString() << "\n\n";
}

void ExecuteEngineOn(CCar& car, const int argument)
{
	if (car.TurnOnEngine())
	{
		cout << "Engine have started.\n\n";
	}
	else
	{
		cout << "Engine is already working.\n\n";
	}
}

void ExecuteEngineOff(CCar& car, const int argument)
{
	if (car.TurnOffEngine())
	{
		cout << "Engine have stoped.\n\n";
	}
	else
	{
		cout << "Is not able to stop engine now.\n\n";
	}
}

void ExecuteSetSpeed(CCar& car, const int argument)
{
	if (car.SetSpeed(argument))
	{
		cout << "New speed equal: " << argument << "\n\n";
	}
	else
	{
		cout << "Can not set speed equal: " << argument << "\n\n";
	}
}

void ExecuteSetGear(CCar& car, const int argument)
{
	if (car.SetGear(argument))
	{
		cout << "New gear equal: " << argument << "\n\n";
	}
	else
	{
		cout << "Can not set gear equal: " << argument << "\n\n";
	}
}


const map<Action, function<void(CCar& car, const int argument)>> FUNCTION_BY_ACTION{
	{ Action::Help, ExecuteHelp },
	{ Action::Info, ExecuteInfo },
	{ Action::EngineOn, ExecuteEngineOn },
	{ Action::EngineOff, ExecuteEngineOff },
	{ Action::SetSpeed, ExecuteSetSpeed },
	{ Action::SetGear, ExecuteSetGear },
};

bool ParseCommand(const string& userInput, Action& userAction)
{
	try
	{
		userAction = ACTION_BY_STRING.at(userInput);
		return true;
	}
	catch (const out_of_range&)
	{
		return false;
	}
}

bool IsNeedArgument(const Action& action)
{
	return (action == Action::SetGear) || (action == Action::SetSpeed);
}

bool IsNotReadUserCommand(Command& userCommand)
{
	string command, userInput;
	if (!getline(cin, userInput))
	{
		throw invalid_argument("Was error while read input\n");
	}

	istringstream input(userInput);

	if (!((input >> command) && ParseCommand(command, userCommand.action)))
	{
		cout << "Invalid command: " << command << "\n";
		return true;
	}

	if (IsNeedArgument(userCommand.action) && !(input >> userCommand.argument))
	{
		cout << "Invalid argument for command: " << command << "\n";
		return true;
	}

	return false;
}

Command ReadCommand()
{
	Command userCommand;
	try
	{
		while (IsNotReadUserCommand(userCommand))
		{
			cout << "Your input was wrong. Use 'Help' from command list.\n\n";
		}
	}
	catch (const invalid_argument& e)
	{
		throw invalid_argument(e.what());
	}

	return userCommand;
}

void ExecuteCommand(CCar& car, Command& command)
{
	auto& func = FUNCTION_BY_ACTION.at(command.action);
	func(car, command.argument);
}

int main()
{
	CCar car{};

	cout << "Hello enter your command! Type 'Help' for command reference!\n\n";

	try
	{
		Command command = ReadCommand();
		while (command.action != Action::End)
		{
			ExecuteCommand(car, command);
			command = ReadCommand();
		}
	}
	catch (const exception& e)
	{
		cout << e.what();
	}

	cout << "Goodbye.\n";

	return 0;
}
