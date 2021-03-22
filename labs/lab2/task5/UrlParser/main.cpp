#include "stdafx.h"
#include "Parser.h"

using namespace std;

const string EXIT = "...";

bool ReadURL(istream& input, string& userString)
{
	if (!(input >> userString))
	{
		return false;
	}
	if (userString == EXIT)
	{
		return false;
	}
	return true;
}

void PrintParsedURL(ostream& output, const ParsedURL& url)
{
	output << "HOST: " << url.host << "\n"
		   << "PORT: " << url.port << "\n"
		   << "DOC: " << url.document << "\n";
}

void PrintError(ostream& output, const string& userUrl)
{
	output << "URL <" << userUrl << "> does not correct.\nPlease try again.\n";
}

int main(int argc, char* argv[])
{
	cout << "Enter URL or ... if you want to exit.\n";

	string userURL;
	while (ReadURL(cin, userURL))
	{
		ParsedURL parsedURL;
		if (ParseURL(userURL, parsedURL))
		{
			PrintParsedURL(cout, parsedURL);
		}
		else
		{
			PrintError(cout, userURL);
		}
	}

	cout << "Goodbye.\n";

	return 0;
}
