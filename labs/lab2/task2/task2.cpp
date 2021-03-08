#include "stdafx.h"
#include "HtmlDecoder.h"

using namespace std;

int main()
{
	string htmlLine;
	getline(cin, htmlLine);

	htmlLine = HtmlDecoder(htmlLine);

	cout << htmlLine << endl;
	return 0;
}
