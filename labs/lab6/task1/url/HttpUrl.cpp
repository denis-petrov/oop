#include "stdafx.h"
#include "HttpUrl.h"
#include "UrlParsingError.h"

using namespace std;

CHttpUrl::CHttpUrl(string const& url)
{
	string search(url);

	smatch matches;
	if (!regex_match(search, matches, URL_REGEX))
	{
		throw CUrlParsingError("Not valid URL string.");
	}

	protocol_ = ParseProtocolFromString(matches[1].str());
	domain_ = matches[2].str();
	port_ = ParsePortFromString(matches[3].str());
	document_ = matches[4].str();
}

CHttpUrl::CHttpUrl(string const& domain, string const& document, Protocol protocol)
	: domain_(domain)
	, document_(EnsureDocumentCorrect(document))
	, protocol_(protocol)
	, port_(SetDefaultPort())
{
}

CHttpUrl::CHttpUrl(string const& domain, string const& document, Protocol protocol, unsigned short port)
	: domain_(domain)
	, document_(EnsureDocumentCorrect(document))
	, protocol_(protocol)
	, port_(port)
{
}

string CHttpUrl::GetURL() const 
{
	return ProtocolToString() + "://" + domain_ + document_;
}

string CHttpUrl::GetDomain() const
{
	return domain_;
}

string CHttpUrl::GetDocument() const
{
	return document_;
}

CHttpUrl::Protocol CHttpUrl::GetProtocol() const
{
	return protocol_;
}

unsigned short CHttpUrl::GetPort() const
{
	return port_;
}

/* PRIVATE */
CHttpUrl::Protocol CHttpUrl::ParseProtocolFromString(string const& userProtocol) const
{
	string protocol(userProtocol);
	boost::algorithm::to_lower(protocol);

	if (protocol == HTTP)
		return CHttpUrl::Protocol::HTTP;

	if (protocol == HTTPS)
		return CHttpUrl::Protocol::HTTPS;

	throw CUrlParsingError("Not valid protocol.");
}

unsigned short CHttpUrl::ParsePortFromString(string const& userPort) const
{
	try
	{
		return boost::lexical_cast<unsigned short>(userPort);
	}
	catch (const bad_cast&)
	{
		throw CUrlParsingError("Not valid port.");
	}
}

string CHttpUrl::EnsureDocumentCorrect(string const& document) const
{
	return (document[0] == SLASH) ? document : string(1, SLASH) + document;
}

unsigned short CHttpUrl::SetDefaultPort() const 
{
	return (protocol_ == CHttpUrl::Protocol::HTTP) ? DEFAULT_HTTP_PORT : DEFAULT_HTTPS_PORT;
}

string CHttpUrl::ProtocolToString() const 
{
	if (protocol_ == Protocol::HTTP)
		return HTTP;

	if (protocol_ == Protocol::HTTPS)
		return HTTPS;

	throw CUrlParsingError("Not correct protocol.");
}