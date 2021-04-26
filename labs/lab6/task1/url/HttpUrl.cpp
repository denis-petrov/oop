#include "stdafx.h"
#include "HttpUrl.h"
#include "UrlParsingError.h"

const std::regex URL_REGEX("(http|https)://([^/:]+)(:\\d+)?(/[^\\?\\#]*)*", std::regex_constants::icase);
const int DEFAULT_HTTP_PORT = 80;
const int DEFAULT_HTTPS_PORT = 443;
const std::string HTTP = "http";
const std::string HTTPS = "https";

const int MIN_PORT = 1;
const int MAX_PORT = 65535;

using namespace std;

CHttpUrl::Protocol ParseProtocolFromString(string const& userProtocol)
{
	string protocol(userProtocol);
	boost::algorithm::to_lower(protocol);

	if (protocol == HTTP)
		return CHttpUrl::Protocol::HTTP;

	if (protocol == HTTPS)
		return CHttpUrl::Protocol::HTTPS;

	throw CUrlParsingError("Not valid protocol.");
}

unsigned short ParsePortFromString(string const& userPort)
{
	try
	{
		int intPort = boost::lexical_cast<int>(userPort.substr(1));
		if ((intPort < MIN_PORT) || (intPort > MAX_PORT))
			throw CUrlParsingError("Not valid port.");

		return boost::lexical_cast<unsigned short>(intPort);
	}
	catch (const bad_cast&)
	{
		throw CUrlParsingError("Not valid port.");
	}
}

string EnsureDocumentCorrect(string const& document)
{
	return (document[0] == '/') ? document : string(1, '/') + document;
}

CHttpUrl::CHttpUrl(string const& url)
{
	smatch matches;
	if (!regex_match(url, matches, URL_REGEX))
	{
		throw CUrlParsingError("Not valid URL string.");
	}

	m_protocol = ParseProtocolFromString(matches[1].str());
	m_domain = matches[2].str();
	m_port = matches[3].str().empty() ? SetDefaultPort() : ParsePortFromString(matches[3].str());
	m_document = matches[4].str().empty() ? string(1, '/') : matches[4].str();
}

CHttpUrl::CHttpUrl(string const& domain, string const& document, Protocol protocol)
	: m_domain(domain)
	, m_document(EnsureDocumentCorrect(document))
	, m_protocol(protocol)
	, m_port(SetDefaultPort())
{
}

CHttpUrl::CHttpUrl(string const& domain, string const& document, Protocol protocol, unsigned short port)
	: m_domain(domain)
	, m_document(EnsureDocumentCorrect(document))
	, m_protocol(protocol)
	, m_port(port)
{
}

string CHttpUrl::GetURL() const
{
	if (m_port == DEFAULT_HTTP_PORT || m_port == DEFAULT_HTTPS_PORT)
		return ProtocolToString() + "://" + m_domain + m_document;
	else
		return ProtocolToString() + "://" + m_domain + string(1, ':') + to_string(m_port) + m_document;
}

string CHttpUrl::GetDomain() const
{
	return m_domain;
}

string CHttpUrl::GetDocument() const
{
	return m_document;
}

CHttpUrl::Protocol CHttpUrl::GetProtocol() const
{
	return m_protocol;
}

unsigned short CHttpUrl::GetPort() const
{
	return m_port;
}

string CHttpUrl::ProtocolToString() const
{
	if (m_protocol == Protocol::HTTP)
		return HTTP;

	if (m_protocol == Protocol::HTTPS)
		return HTTPS;

	throw CUrlParsingError("Not correct protocol.");
}

/* PRIVATE */
unsigned short CHttpUrl::SetDefaultPort() const
{
	return (m_protocol == CHttpUrl::Protocol::HTTP) ? DEFAULT_HTTP_PORT : DEFAULT_HTTPS_PORT;
}
