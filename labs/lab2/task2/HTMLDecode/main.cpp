#include "stdafx.h"
#include "HtmlDecode.h"

using namespace std;

int main()
{
	string htmlLine;
	getline(cin, htmlLine);

	htmlLine = DecodeHtmlString(htmlLine);

	cout << htmlLine << endl;
	return 0;
}
