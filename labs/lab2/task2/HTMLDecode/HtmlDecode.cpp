#include "stdafx.h"
#include "HtmlDecode.h"

using namespace std;

string DecodeHtmlString(const string& html)
{
	vector<pair<string, string>> symbolByHtmlString = {
		{ "&qout;", "\"" },
		{ "&apos;", "'" },
		{ "&lt;", "<" },
		{ "&gt;", ">" },
		{ "&amp;", "&" } // must be last because nested cases
	};

	string decodedString(html);

	for (auto& pair : symbolByHtmlString)
	{
		decodedString = regex_replace(decodedString, regex(pair.first), pair.second);
	}

	return decodedString;
}