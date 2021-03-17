#include "stdafx.h"
#include "HtmlDecode.h"

using namespace std;

int main()
{
	string htmlLine;
	getline(cin, htmlLine);

	cout << DecodeHtmlString(htmlLine) << endl;
	
	return 0;
}
