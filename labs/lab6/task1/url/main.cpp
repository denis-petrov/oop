#include "stdafx.h"
#include "HttpUrl.h"

using namespace std;

int main()
{
	string userLine;

	cout << "Hello, you are able type string for parsing to URL or type ... for exit.\n\n"; 
	while (getline(cin, userLine) && (userLine != "..."))
	{
		try
		{
			CHttpUrl url(userLine);

			cout << "\nURL: " << url.GetURL() << "\n"
				 << "PROTOCOL: " << url.ProtocolToString() << "\n"
				 << "DOMAIN: " << url.GetDomain() << "\n"
				 << "PORT: " << to_string(url.GetPort()) << "\n"
				 << "DOCUMENT: " << url.GetDocument() << "\n\n";
		}
		catch (const exception& e)
		{
			cout << e.what() << "\n\n";
		}
	}
	cout << "Goodbye\n";

	return 0;
}
