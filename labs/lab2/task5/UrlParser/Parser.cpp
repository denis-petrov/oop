#include "stdafx.h"
#include "Parser.h"

using namespace std;

Protocol GetProtocol(const string& protocolStr) 
{
	map<string, Protocol> protocolByString{ 
		{ HTTP, Protocol::HTTP },
		{ HTTPS, Protocol::HTTPS },
		{ FTP, Protocol::FTP }
	};

	return protocolByString.count(protocolStr) ? protocolByString[protocolStr] : Protocol::NOT_SET;
}

int GetDefaultPort(const Protocol& protocol) 
{
	map<Protocol, int> portByProtocol{
		{ Protocol::HTTP, DEFAULT_HTTP_PORT },
		{ Protocol::HTTPS, DEFAULT_HTTPS_PORT },
		{ Protocol::FTP, DEFAULT_FTP_PORT },
		{ Protocol::NOT_SET, NOT_SET_PORT },
	};

	return portByProtocol[protocol];
}

int GetPort(const string& portStr, const Protocol& protocol) 
{
	try
	{
		return boost::lexical_cast<int>(portStr);
	}
	catch (const bad_cast&)
	{
		return GetDefaultPort(protocol);
	}
}

bool ValidatePort(const int port)
{
	return (MIN_PORT <= port) && (port <= MAX_PORT);
}

bool ParseURL(const string& userURL, ParsedURL& parsedURL)
{
	string search(userURL);
	boost::algorithm::to_lower(search);

	smatch matches;
	if (regex_match(search, matches, PARSE_REGEX))
	{
		parsedURL.protocol = GetProtocol(matches[1].str());
		parsedURL.host = matches[2].str();
		parsedURL.port = GetPort(matches[3].str(), parsedURL.protocol);
		parsedURL.document = matches[4].str();

		return ValidatePort(parsedURL.port);
	}

	return false;
}

