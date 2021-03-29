#include "stdafx.h"
#include "Car.h"
#include "RemoteControl.h"

using namespace std;


int main()
{
	cout << "Hello enter your command! Type 'Help' for command reference!\n\n";

	CCar car;
	CRemoteControl remoteControl(car, cin, cout);

	while (!cin.eof() && !cin.fail() && !remoteControl.IsEndInput())
	{
		if (!remoteControl.HandleCommand())
		{
			cout << "Unknown command!" << endl << endl;
		}
	}

	return 0;
}
