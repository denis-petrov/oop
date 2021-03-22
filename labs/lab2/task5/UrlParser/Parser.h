#pragma once

#include "stdafx.h"

enum class Protocol
{
	HTTP,
	HTTPS,
	FTP
};

struct ParsedURL
{
	Protocol protocol;
	std::string host;
	int port;
	std::string document;
};

const std::string HTTP = "http";
const std::string HTTPS = "https";
const std::string FTP = "ftp";

const int DEFAULT_HTTP_PORT = 80;
const int DEFAULT_HTTPS_PORT = 443;
const int DEFAULT_FTP_PORT = 21;
const int NOT_SET_PORT = 0;

const int MIN_PORT = 1;
const int MAX_PORT = 65535;

const std::regex PARSE_REGEX("(http[s]?|ftp)://([^/:]+):?([^/]*)(/?[^#?]*)");

const std::map<std::string, Protocol> PROTOCOL_BY_STRING {
	{ HTTP, Protocol::HTTP },
	{ HTTPS, Protocol::HTTPS },
	{ FTP, Protocol::FTP }
};

const std::map<Protocol, int> PORT_BY_PROTOCOL {
	{ Protocol::HTTP, DEFAULT_HTTP_PORT },
	{ Protocol::HTTPS, DEFAULT_HTTPS_PORT },
	{ Protocol::FTP, DEFAULT_FTP_PORT },
};

std::optional<Protocol> GetProtocol(const std::string& protocolStr);
int GetDefaultPort(const Protocol& protocol);
int GetPort(const std::string& portStr, const Protocol& protocol);

bool ValidatePort(const int port);
bool ParseURL(const std::string& userURL, ParsedURL& parsedURL);

