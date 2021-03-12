#define CATCH_CONFIG_MAIN
#include "../../../../catch2/catch.hpp"
#include "../HTMLDecode/HtmlDecode.h"


SCENARIO("HTML String Decode with a string gives decode string")
{
	GIVEN("A string") 
	{
		std::string html;
		std::string expectedResult;

		WHEN("A string is empty")
		{
			html = "";
			REQUIRE(DecodeHtmlString(html).size() == 0);
		}

		WHEN("A string not contains html code")
		{
			html = "A string not contains html code";
			REQUIRE(DecodeHtmlString(html) == html);

			html = "nice string";
			REQUIRE(DecodeHtmlString(html) == html);
		}

		WHEN("A string contains html code")
		{
			html = "&lt; br &gt;";
			expectedResult = "< br >";
			REQUIRE(DecodeHtmlString(html) == expectedResult);

			html = "&lt; br &gt; &apos; &amp;   &qout;";
			expectedResult = "< br > ' &   \"";
			REQUIRE(DecodeHtmlString(html) == expectedResult);

			html = "&lt; text";
			expectedResult = "< text";
			REQUIRE(DecodeHtmlString(html) == expectedResult);

			html = "text &amp;";
			expectedResult = "text &";
			REQUIRE(DecodeHtmlString(html) == expectedResult);
		}

		WHEN("A string contains nested html code")
		{
			html = "&&&&lt;;;; br &g;&gt;&t;;";
			expectedResult = "&&&<;;; br &g;>&t;;";
			REQUIRE(DecodeHtmlString(html) == expectedResult);

			html = "123 < &am&qout;p; > @ &&apos;&;;&";
			expectedResult = "123 < &am\"p; > @ &'&;;&";
			REQUIRE(DecodeHtmlString(html) == expectedResult);

			html = "&&&&lt;;;;";
			expectedResult = "&&&<;;;";
			REQUIRE(DecodeHtmlString(html) == expectedResult);
		}
	}
}