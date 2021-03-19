#pragma once

#include "stdafx.h"

enum class Protocol
{
	HTTP,
	HTTPS,
	FTP,
	ERROR
};

struct ParsedURL
{
	Protocol protocol;
	int port;
	std::string host;
	std::string document;
};

const std::string HTTP = "http";
const std::string HTTPS = "https";
const std::string FTP = "ftp";

const int DEFAULT_HTTP = 80;
const int DEFAULT_HTTPS = 443;
const int DEFAULT_FTP = 21;
const int ERROR_PORT = 0;

const int MIN_PORT = 1;
const int MAX_PORT = 65535;

const std::regex PARSE_REGEX("(http[s]?|ftp)://([^/:]+):?([^/]*)(/?[^#?]*)");

Protocol GetProtocol(const std::string& protocolStr);
int GetDefaultPort(const Protocol& protocol);
int GetPort(const std::string& portStr, const Protocol& protocol);

bool ValidatePort(const int port);
bool ParseURL(const std::string& userURL, ParsedURL& parsedURL);

