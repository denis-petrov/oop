#pragma once
#include "stdafx.h"

class CHttpUrl
{
public:
	enum class Protocol
	{
		HTTP,
		HTTPS
	};

public:
	CHttpUrl(std::string const& url);

	CHttpUrl(std::string const& domain,
		std::string const& document,
		Protocol protocol = Protocol::HTTP);

	CHttpUrl(std::string const& domain,
		std::string const& document,
		Protocol protocol,
		unsigned short port);

public:
	std::string GetURL() const;
	std::string GetDomain() const;
	std::string GetDocument() const;
	Protocol GetProtocol() const;
	unsigned short GetPort() const;

	std::string ProtocolToString() const;

private:
	Protocol m_protocol;
	std::string m_domain;
	unsigned short m_port;
	std::string m_document;

	unsigned short SetDefaultPort() const;
};
