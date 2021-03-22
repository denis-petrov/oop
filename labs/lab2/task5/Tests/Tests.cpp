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
		WHEN("Incorrect Value") // 1 case
		{
			REQUIRE(GetProtocol("test@@") == std::nullopt);

			REQUIRE(GetProtocol("") == std::nullopt);
		}

		WHEN("Correct Value") // 2 case
		{
			REQUIRE(GetProtocol("http") == Protocol::HTTP);

			REQUIRE(GetProtocol("https") == Protocol::HTTPS);

			REQUIRE(GetProtocol("ftp") == Protocol::FTP);
		}
	}
}

SCENARIO("Validate port") // 2 scenario
{
	GIVEN("Int")
	{
		WHEN("Value around border and correct") // 1 case
		{
			REQUIRE(ValidatePort(1) == true);

			REQUIRE(ValidatePort(65535) == true);
		}

		WHEN("Value around border and in correct") // 2 case
		{
			REQUIRE(ValidatePort(0) == false);

			REQUIRE(ValidatePort(65536) == false);
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
			REQUIRE(GetPort("", Protocol::HTTP) == DEFAULT_HTTP_PORT);

			REQUIRE(GetPort("@@", Protocol::HTTPS) == DEFAULT_HTTPS_PORT);
		}

		WHEN("Correct Value") // 2 case
		{
			REQUIRE(GetPort("10", Protocol::HTTP) == 10);

			REQUIRE(GetPort("10", Protocol::HTTPS) == 10);

			REQUIRE(GetPort("10", Protocol::FTP) == 10);
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
			REQUIRE(ParseURL("", url) == false);

			REQUIRE(ParseURL("http://", url) == false);
		}

		WHEN("Correct Value without port and document") // 2 case
		{
			expectedURL = { Protocol::HTTP, "test.com", DEFAULT_HTTP_PORT, "" };
			REQUIRE(ParseURL("http://test.com", url) == true);
			REQUIRE(IsEqualURLs(url, expectedURL) == true);

			expectedURL = { Protocol::HTTPS, "test.com", DEFAULT_HTTPS_PORT, "" };
			REQUIRE(ParseURL("https://test.com", url) == true);
			REQUIRE(IsEqualURLs(url, expectedURL) == true);

			expectedURL = { Protocol::FTP, "test.com", DEFAULT_FTP_PORT, "" };
			REQUIRE(ParseURL("ftp://test.com", url) == true);
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