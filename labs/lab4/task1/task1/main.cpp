#include "stdafx.h"
#include "BodiesControl.h"

using namespace std;

int main()
{
	cout << "Hello, enter your command! Type 'help' for more information!\n\n";

	CBodiesControl bodiesControl(cin, cout);

	while (!cin.eof() && !cin.fail() && !bodiesControl.IsEndInput())
	{
		if (!bodiesControl.HandleCommand())
		{
			cout << "Unknown command!" << endl << endl;
		}
	}

	return 0;
}
