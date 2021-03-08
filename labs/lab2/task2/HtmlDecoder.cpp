#include "stdafx.h"
#include "HtmlDecoder.h"

using namespace std;

string HtmlDecoder(const string& html)
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

	return (startPos != 0) ? result : html;
}