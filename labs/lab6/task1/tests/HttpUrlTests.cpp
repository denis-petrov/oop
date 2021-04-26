#include "stdafx.h"
#include "../url/HttpUrl.h"
#include "../url/UrlParsingError.h"

struct HttpUrl_
{
};

BOOST_FIXTURE_TEST_SUITE(HttpUrl_tests, HttpUrl_)

	BOOST_AUTO_TEST_CASE(throw_url_parsing_error_if_user_string_is_empty)
	{
		BOOST_CHECK_THROW(CHttpUrl(""), CUrlParsingError);
	}

	BOOST_AUTO_TEST_CASE(throw_url_parsing_error_if_full_user_string_is_incorrect)
	{
		BOOST_CHECK_THROW(CHttpUrl("lol://test.com/12"), CUrlParsingError);
		BOOST_CHECK_THROW(CHttpUrl("lol2://t.ru/12"), CUrlParsingError);
	}

	BOOST_AUTO_TEST_CASE(throw_url_parsing_error_if_m_portis_incorrect)
	{
		BOOST_CHECK_THROW(CHttpUrl("http://test.com:65536/12"), CUrlParsingError);
		BOOST_CHECK_THROW(CHttpUrl("https://t.ru:-1/12"), CUrlParsingError);
		BOOST_CHECK_THROW(CHttpUrl("https://t.ru:/12"), CUrlParsingError);
		BOOST_CHECK_THROW(CHttpUrl("https://t.ru:65537/12"), CUrlParsingError);
		BOOST_CHECK_THROW(CHttpUrl("https://t.ru:0/12"), CUrlParsingError);
	}

	BOOST_AUTO_TEST_CASE(throw_url_parsing_error_if_user_string_with_side_date_in_query)
	{
		BOOST_CHECK_THROW(CHttpUrl("https://vk.com/audio?block=weekly2recoms"), CUrlParsingError);
	}

	BOOST_AUTO_TEST_CASE(able_initialize_instance_by_string)
	{
		const std::string httpStr = "http://vk.com/"; 
		const std::string httpsStr = "https://google.com/"; 
		CHttpUrl httpUrl(httpStr);
		CHttpUrl httpsUrl(httpsStr);

		BOOST_CHECK(httpUrl.GetDocument() == "/");
		BOOST_CHECK(httpUrl.GetDomain() == "vk.com");
		BOOST_CHECK(httpUrl.GetPort() == 80);
		BOOST_CHECK(httpUrl.GetProtocol() == CHttpUrl::Protocol::HTTP);

		BOOST_CHECK(httpsUrl.GetDocument() == "/");
		BOOST_CHECK(httpsUrl.GetDomain() == "google.com");
		BOOST_CHECK(httpsUrl.GetPort() == 443);
		BOOST_CHECK(httpsUrl.GetProtocol() == CHttpUrl::Protocol::HTTPS);
	}

	BOOST_AUTO_TEST_CASE(able_initialize_instance_by_m_domainand_m_documentor_protocol)
	{
		CHttpUrl httpUrl("vk.com", "test");
		CHttpUrl httpUrlFull("vk.com", "test", CHttpUrl::Protocol::HTTP);
		CHttpUrl httpsUrlFull("google.com", "test", CHttpUrl::Protocol::HTTPS);

		BOOST_CHECK(httpUrl.GetDocument() == "/test");
		BOOST_CHECK(httpUrl.GetDomain() == "vk.com");
		BOOST_CHECK(httpUrl.GetPort() == 80);
		BOOST_CHECK(httpUrl.GetProtocol() == CHttpUrl::Protocol::HTTP);

		BOOST_CHECK(httpUrlFull.GetDocument() == "/test");
		BOOST_CHECK(httpUrlFull.GetDomain() == "vk.com");
		BOOST_CHECK(httpUrlFull.GetPort() == 80);
		BOOST_CHECK(httpUrlFull.GetProtocol() == CHttpUrl::Protocol::HTTP);

		BOOST_CHECK(httpsUrlFull.GetDocument() == "/test");
		BOOST_CHECK(httpsUrlFull.GetDomain() == "google.com");
		BOOST_CHECK(httpsUrlFull.GetPort() == 443);
		BOOST_CHECK(httpsUrlFull.GetProtocol() == CHttpUrl::Protocol::HTTPS);
	}

	BOOST_AUTO_TEST_CASE(able_initialize_instance_by_all_params)
	{
		CHttpUrl httpUrl("google.com", "test", CHttpUrl::Protocol::HTTP, 80);
		CHttpUrl httpsUrl("google.com", "test", CHttpUrl::Protocol::HTTPS, 90);

		BOOST_CHECK(httpUrl.GetDocument() == "/test");
		BOOST_CHECK(httpUrl.GetDomain() == "google.com");
		BOOST_CHECK(httpUrl.GetPort() == 80);
		BOOST_CHECK(httpUrl.GetProtocol() == CHttpUrl::Protocol::HTTP);

		BOOST_CHECK(httpsUrl.GetDocument() == "/test");
		BOOST_CHECK(httpsUrl.GetDomain() == "google.com");
		BOOST_CHECK(httpsUrl.GetPort() == 90);
		BOOST_CHECK(httpsUrl.GetProtocol() == CHttpUrl::Protocol::HTTPS);
	}

	BOOST_AUTO_TEST_CASE(able_get_url_without_port)
	{
		CHttpUrl httpUrl("google.com", "test", CHttpUrl::Protocol::HTTP, 80);
		CHttpUrl httpsUrl("google.com", "test", CHttpUrl::Protocol::HTTPS, 90);

		BOOST_CHECK(httpUrl.GetURL() == "http://google.com/test");
		BOOST_CHECK(httpUrl.GetDomain() == "google.com");
		BOOST_CHECK(httpUrl.GetPort() == 80);
		BOOST_CHECK(httpUrl.GetProtocol() == CHttpUrl::Protocol::HTTP);

		BOOST_CHECK(httpsUrl.GetURL() == "https://google.com:90/test");
		BOOST_CHECK(httpsUrl.GetDomain() == "google.com");
		BOOST_CHECK(httpsUrl.GetPort() == 90);
		BOOST_CHECK(httpsUrl.GetProtocol() == CHttpUrl::Protocol::HTTPS);
	}

	BOOST_AUTO_TEST_CASE(able_get_url_with_default_port)
	{
		CHttpUrl httpUrl("http://google.com/test");
		CHttpUrl httpsUrl("https://google.com/test");

		BOOST_CHECK(httpUrl.GetURL() == "http://google.com/test");
		BOOST_CHECK(httpUrl.GetDomain() == "google.com");
		BOOST_CHECK(httpUrl.GetPort() == 80);
		BOOST_CHECK(httpUrl.GetProtocol() == CHttpUrl::Protocol::HTTP);

		BOOST_CHECK(httpsUrl.GetURL() == "https://google.com/test");
		BOOST_CHECK(httpsUrl.GetDomain() == "google.com");
		BOOST_CHECK(httpsUrl.GetPort() == 443);
		BOOST_CHECK(httpsUrl.GetProtocol() == CHttpUrl::Protocol::HTTPS);
	}

	BOOST_AUTO_TEST_CASE(able_get_url_with_not_default_port)
	{
		CHttpUrl httpUrl("http://google.com:111/test");
		CHttpUrl httpsUrl("https://google.com:2222/test");

		BOOST_CHECK(httpUrl.GetURL() == "http://google.com:111/test");
		BOOST_CHECK(httpUrl.GetDomain() == "google.com");
		BOOST_CHECK(httpUrl.GetPort() == 111);
		BOOST_CHECK(httpUrl.GetProtocol() == CHttpUrl::Protocol::HTTP);

		BOOST_CHECK(httpsUrl.GetURL() == "https://google.com:2222/test");
		BOOST_CHECK(httpsUrl.GetDomain() == "google.com");
		BOOST_CHECK(httpsUrl.GetPort() == 2222);
		BOOST_CHECK(httpsUrl.GetProtocol() == CHttpUrl::Protocol::HTTPS);
	}

	BOOST_AUTO_TEST_CASE(able_get_domain)
	{
		CHttpUrl httpUrl("http://google.com/test");
		CHttpUrl httpsUrl("https://google.com/test");

		BOOST_CHECK(httpUrl.GetDomain() == "google.com");
		BOOST_CHECK(httpUrl.GetPort() == 80);
		BOOST_CHECK(httpUrl.GetProtocol() == CHttpUrl::Protocol::HTTP);

		BOOST_CHECK(httpsUrl.GetDomain() == "google.com");
		BOOST_CHECK(httpsUrl.GetPort() == 443);
		BOOST_CHECK(httpsUrl.GetProtocol() == CHttpUrl::Protocol::HTTPS);
	}

	BOOST_AUTO_TEST_CASE(able_get_document)
	{
		CHttpUrl httpUrl("http://google.com:80/test");
		CHttpUrl httpsUrl("https://google.com:90/test");

		BOOST_CHECK(httpUrl.GetDocument() == "/test");
		BOOST_CHECK(httpUrl.GetDomain() == "google.com");
		BOOST_CHECK(httpUrl.GetPort() == 80);
		BOOST_CHECK(httpUrl.GetProtocol() == CHttpUrl::Protocol::HTTP);

		BOOST_CHECK(httpsUrl.GetDocument() == "/test");
		BOOST_CHECK(httpsUrl.GetDomain() == "google.com");
		BOOST_CHECK(httpsUrl.GetPort() == 90);
		BOOST_CHECK(httpsUrl.GetProtocol() == CHttpUrl::Protocol::HTTPS);
	}

	BOOST_AUTO_TEST_CASE(able_get_port)
	{
		CHttpUrl httpUrl1("http://google.com:70/test");
		CHttpUrl httpUrl2("http://google.com/test");
		CHttpUrl httpsUrl1("https://google.com:20/test");
		CHttpUrl httpsUrl2("https://google.com/test");

		BOOST_CHECK(httpUrl1.GetPort() == 70);
		BOOST_CHECK(httpUrl2.GetPort() == 80);
		BOOST_CHECK(httpsUrl1.GetPort() == 20);
		BOOST_CHECK(httpsUrl2.GetPort() == 443);
	}

	BOOST_AUTO_TEST_CASE(able_get_protocol)
	{
		CHttpUrl httpUrl("http://google.com/test");
		CHttpUrl httpsUrl("https://google.com/test");

		BOOST_CHECK(httpUrl.GetProtocol() == CHttpUrl::Protocol::HTTP);
		BOOST_CHECK(httpsUrl.GetProtocol() == CHttpUrl::Protocol::HTTPS);
	}

	BOOST_AUTO_TEST_CASE(able_use_any_case)
	{
		CHttpUrl httpUrl("hTtP://google.com/test");
		CHttpUrl httpsUrl("HtTPs://google.com/test");

		BOOST_CHECK(httpUrl.GetProtocol() == CHttpUrl::Protocol::HTTP);
		BOOST_CHECK(httpsUrl.GetProtocol() == CHttpUrl::Protocol::HTTPS);
	}

BOOST_AUTO_TEST_SUITE_END()