#define CATCH_CONFIG_MAIN
#include "../../../../catch2/catch.hpp"
#include "../UrlParser/Parser.h"

bool IsEqualURLs(ParsedURL first, ParsedURL second) 
{
	return (first.protocol == second.protocol) && (first.host == second.host) 
		&& (first.port == second.port) && (first.document == second.document);
}

SCENARIO("Test get protocol") // 1 scenario
{
	GIVEN("String")
	{
		std::string protocolStr;

		WHEN("Incorrect Value") // 1 case
		{
			protocolStr = "test@@";
			REQUIRE(GetProtocol(protocolStr) == Protocol::NOT_SET);

			protocolStr = "";
			REQUIRE(GetProtocol(protocolStr) == Protocol::NOT_SET);
		}

		WHEN("Correct Value") // 2 case
		{
			protocolStr = "http";
			REQUIRE(GetProtocol(protocolStr) == Protocol::HTTP);

			protocolStr = "https";
			REQUIRE(GetProtocol(protocolStr) == Protocol::HTTPS);

			protocolStr = "ftp";
			REQUIRE(GetProtocol(protocolStr) == Protocol::FTP);
		}
	}
}

SCENARIO("Test get default port") // 2 scenario
{
	GIVEN("Protocol")
	{
		Protocol protocol;

		WHEN("Incorrect Value") // 1 case
		{
			protocol = Protocol::NOT_SET;
			REQUIRE(GetDefaultPort(protocol) == NOT_SET_PORT);
		}

		WHEN("Correct Value") // 2 case
		{
			protocol = Protocol::HTTP;
			REQUIRE(GetDefaultPort(protocol) == DEFAULT_HTTP_PORT);

			protocol = Protocol::HTTPS;
			REQUIRE(GetDefaultPort(protocol) == DEFAULT_HTTPS_PORT);

			protocol = Protocol::FTP;
			REQUIRE(GetDefaultPort(protocol) == DEFAULT_FTP_PORT);
		}
	}
}

SCENARIO("Test Get port") // 3 scenario
{
	GIVEN("String and Protocol")
	{
		std::string portStr;
		Protocol protocol;

		WHEN("Incorrect Value") // 1 case
		{
			portStr = "";
			protocol = Protocol::NOT_SET;
			REQUIRE(GetPort(portStr, protocol) == NOT_SET_PORT);

			portStr = "@@";
			protocol = Protocol::NOT_SET;
			REQUIRE(GetPort(portStr, protocol) == NOT_SET_PORT);
		}

		WHEN("Correct Value") // 2 case
		{
			portStr = "http";
			protocol = Protocol::HTTP;
			REQUIRE(GetPort(portStr, protocol) == DEFAULT_HTTP_PORT);

			portStr = "https";
			protocol = Protocol::HTTPS;
			REQUIRE(GetPort(portStr, protocol) == DEFAULT_HTTPS_PORT);

			portStr = "ftp";
			protocol = Protocol::FTP;
			REQUIRE(GetPort(portStr, protocol) == DEFAULT_FTP_PORT);
		}
	}
}

SCENARIO("Test ParseURL") // 4 scenario
{
	GIVEN("UserURL String and ParsedURL")
	{
		std::string userURL;
		ParsedURL url;
		ParsedURL expectedURL;

		WHEN("Incorrect Value") // 1 case
		{
			userURL = "";
			REQUIRE(ParseURL(userURL, url) == false);

			userURL = "http://";
			REQUIRE(ParseURL(userURL, url) == false);
		}

		WHEN("Correct Value without port and document") // 2 case
		{
			userURL = "http://test.com";
			expectedURL = { Protocol::HTTP, "test.com", DEFAULT_HTTP_PORT, "" };
			REQUIRE(ParseURL(userURL, url) == true);
			REQUIRE(IsEqualURLs(url, expectedURL) == true);

			userURL = "https://test.com";
			expectedURL = { Protocol::HTTPS, "test.com", DEFAULT_HTTPS_PORT, "" };
			REQUIRE(ParseURL(userURL, url) == true);
			REQUIRE(IsEqualURLs(url, expectedURL) == true);

			userURL = "ftp://test.com";
			expectedURL = { Protocol::FTP, "test.com", DEFAULT_FTP_PORT, "" };
			REQUIRE(ParseURL(userURL, url) == true);
			REQUIRE(IsEqualURLs(url, expectedURL) == true);
		}

		WHEN("Correct Value with incorrect port and without document") // 3 case
		{
			userURL = "http://test.com:2000000000000";
			expectedURL = { Protocol::HTTP, "test.com", DEFAULT_HTTP_PORT, "" };
			REQUIRE(ParseURL(userURL, url) == true);
			REQUIRE(IsEqualURLs(url, expectedURL) == true);

			userURL = "https://test.com:2000000000000";
			expectedURL = { Protocol::HTTPS, "test.com", DEFAULT_HTTPS_PORT, "" };
			REQUIRE(ParseURL(userURL, url) == true);
			REQUIRE(IsEqualURLs(url, expectedURL) == true);

			userURL = "ftp://test.com:2000000000000";
			expectedURL = { Protocol::FTP, "test.com", DEFAULT_FTP_PORT, "" };
			REQUIRE(ParseURL(userURL, url) == true);
			REQUIRE(IsEqualURLs(url, expectedURL) == true);
		}

		WHEN("Correct Value with incorrect port and with document") // 4 case
		{
			userURL = "http://test.com:2000000000000/text/test.txt";
			expectedURL = { Protocol::HTTP, "test.com", DEFAULT_HTTP_PORT, "/text/test.txt" };
			REQUIRE(ParseURL(userURL, url) == true);
			REQUIRE(IsEqualURLs(url, expectedURL) == true);

			userURL = "https://test.com:2000000000000/text/test.txt";
			expectedURL = { Protocol::HTTPS, "test.com", DEFAULT_HTTPS_PORT, "/text/test.txt" };
			REQUIRE(ParseURL(userURL, url) == true);
			REQUIRE(IsEqualURLs(url, expectedURL) == true);

			userURL = "ftp://test.com:2000000000000/text/test.txt";
			expectedURL = { Protocol::FTP, "test.com", DEFAULT_FTP_PORT, "/text/test.txt" };
			REQUIRE(ParseURL(userURL, url) == true);
			REQUIRE(IsEqualURLs(url, expectedURL) == true);
		}

		WHEN("Correct Value with correct port and with document") // 5 case
		{
			userURL = "http://test.com:20/text/test.txt";
			expectedURL = { Protocol::HTTP, "test.com", 20, "/text/test.txt" };
			REQUIRE(ParseURL(userURL, url) == true);
			REQUIRE(IsEqualURLs(url, expectedURL) == true);

			userURL = "https://test.com:20/text/test.txt";
			expectedURL = { Protocol::HTTPS, "test.com", 20, "/text/test.txt" };
			REQUIRE(ParseURL(userURL, url) == true);
			REQUIRE(IsEqualURLs(url, expectedURL) == true);

			userURL = "ftp://test.com:20/text/test.txt";
			expectedURL = { Protocol::FTP, "test.com", 20, "/text/test.txt" };
			REQUIRE(ParseURL(userURL, url) == true);
			REQUIRE(IsEqualURLs(url, expectedURL) == true);
		}
	}
}