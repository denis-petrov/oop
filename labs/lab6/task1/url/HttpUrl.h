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
	
	std::string GetFullURL() const;
	
	std::string ProtocolToString() const;

private:
	Protocol protocol_;
	std::string domain_;
	unsigned short port_;
	std::string document_;

	Protocol ParseProtocolFromString(std::string const& userProtocol) const;
	unsigned short ParsePortFromString(std::string const& userPort) const;
	std::string EnsureDocumentCorrect(std::string const& document) const;
	unsigned short SetDefaultPort() const;
};
