#include "stdafx.h"
#include "HtmlDecode.h"

using namespace std;

string DecodeHtmlString(const string& html)
{
	unordered_map<string, string> symbolByHtmlString = {
		{ "&qout;", "\"" },
		{ "&apos;", "'" },
		{ "&lt;", "<" },
		{ "&gt;", ">" },
		{ "&amp;", "&" }
	};

	string result;
	const regex DECODE_HTML_REGEX("&(qout|apos|lt|gt|amp);");

	smatch match;
	int startPos = 0;
	while (regex_search(html.begin() + startPos, html.end(), match, DECODE_HTML_REGEX))
	{
		result += (string)match.prefix() + symbolByHtmlString[match[0]];
		startPos += match.position() + match[0].length();
	}
	result += (string)match.suffix();

	return (startPos != 0) ? result : html;
}