#include "stdafx.h"
#include "HtmlDecode.h"

using namespace std;

const string EXIT = "...";

bool ReadHTMLLine(istream& input, string& userString)
{
	if (!getline(input, userString))
	{
		return false;
	}
	if (userString == EXIT)
	{
		return false;
	}
	return true;
}

vector<string> ReadUserHTML(istream& input) 
{
	vector<string> result;

	string userInput;
	while (ReadHTMLLine(input, userInput))
	{	
		result.push_back(userInput);
	}

	return result;
}

int main()
{
	cout << "Enter HTML or ... if you want to exit.\n";
	vector<string> userInput = ReadUserHTML(cin);

	for (auto& htmlLine : userInput)
	{
		cout << DecodeHtmlString(htmlLine) << endl;
	}

	cout << "Goodbye.\n";
	
	return 0;
}
