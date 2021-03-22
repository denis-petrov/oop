#include "stdafx.h"
#include "Parser.h"

using namespace std;

optional<Protocol> GetProtocol(const string& protocolStr) 
{
	try
	{
		auto res = PROTOCOL_BY_STRING.at(protocolStr);
		return res; 
	}
	catch (const exception&)
	{
		return nullopt;
	}
}

int GetDefaultPort(const Protocol& protocol) 
{
	return PORT_BY_PROTOCOL.at(protocol);
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
		auto protocol = GetProtocol(matches[1].str());
		if (protocol == nullopt)
		{
			return false;
		}
		parsedURL.protocol = protocol.value();

		parsedURL.host = matches[2].str();
		parsedURL.port = GetPort(matches[3].str(), parsedURL.protocol);
		parsedURL.document = matches[4].str();

		return ValidatePort(parsedURL.port);
	}

	return false;
}

