// task2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <regex>

using namespace std;

string HtmlDecode(const string& html)
{
	map<string, string> mapHtmlDecode = {
		{ "&qout;", "\"" }, 
		{ "&apos;", "'" }, 
		{ "&lt;", "<" },
		{ "&gt;", ">" },
		{ "&amp;", "&" }
	};

	string result;
	const regex decodeHtmlRegex("&(qout|apos|lt|gt|amp);");

	smatch match;
	int startPos = 0;
	while (regex_search(html.begin() + startPos, html.end(), match, decodeHtmlRegex))
	{
		result += (string)match.prefix() + mapHtmlDecode[match[0]];
		startPos += match.position() + match[0].length();
	}
	result += (string)match.suffix();

	return result;
}

int main()
{
	string htmlLine;
	getline(std::cin, htmlLine);

	htmlLine = HtmlDecode(htmlLine);

	cout << htmlLine << endl;
	return 0;
}
