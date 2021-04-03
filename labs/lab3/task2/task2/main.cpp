#include "stdafx.h"
#include "Calculator.h"
#include "RemoteControl.h"

using namespace std;

int main()
{
	cout << "Hello enter your command! Type 'help' for command reference!\n\n";

	CCalculator calculator;
	CRemoteControl remoteControl(calculator, cin, cout);

	while (!cin.eof() && !cin.fail() && !remoteControl.IsEndInput())
	{
		if (!remoteControl.HandleCommand())
		{
			cout << "Unknown command!" << endl << endl;
		}
	}

	return 0;
}