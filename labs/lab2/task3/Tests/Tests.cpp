#define CATCH_CONFIG_MAIN
#include "../../../../catch2/catch.hpp"
#include "../MiniDictionary/DictionarySerialize.h"
#include "../MiniDictionary/Translator.h"


SCENARIO("Test serialization and deserialization") // 1 scenario
{
	GIVEN("Map") 
	{
		std::map<std::string, std::string> map;

		WHEN("Serialize not empty map into file") // 1 case
		{
			map = {
				{ "ok", "test Serialization" },
				{ "mama", "washed the window" }
			};

			SerializeDictionary("TestDictionaries/Dict1", map);
			REQUIRE(DeserializeDictionary("TestDictionaries/Dict1") == map);
		}

		WHEN("Serialize empty map into file") // 2 case
		{
			map = {};

			SerializeDictionary("TestDictionaries/Dict1", map);
			REQUIRE(DeserializeDictionary("TestDictionaries/Dict1") == map);
		}

		WHEN("Deserialize empty map from file") // 3 case
		{
			map = {};

			REQUIRE(DeserializeDictionary("TestDictionaries/Dict1") == map);
		}
	}
}

SCENARIO("Test save dictionary(map) into file") // 2 scenario
{
	GIVEN("Map")
	{
		std::map<std::string, std::string> mapFirst;
		std::map<std::string, std::string> mapSecond;

		std::ifstream input;

		WHEN("First map equals second") // 1 case
		{
			mapFirst = { { "1", "1" } };
			mapSecond = mapFirst;

			input.open("TestStreams/2Scenario/1CaseIn.txt");

			REQUIRE(IsUserChangeDictionary(mapFirst, mapSecond) == false);
			REQUIRE(SaveDictionary("TestDictionaries/Dict2", input, mapSecond) == true);
			REQUIRE(DeserializeDictionary("TestDictionaries/Dict2") == mapFirst);

			input.close();
		}

		WHEN("First map in not equals second and user answerd Yes") // 2 case
		{
			mapFirst = { { "1", "1" } };
			mapSecond = { { "1", "1" }, { "2", "2" } };

			input.open("TestStreams/2Scenario/2CaseIn.txt");

			REQUIRE(IsUserChangeDictionary(mapFirst, mapSecond) == true);
			REQUIRE(SaveDictionary("TestDictionaries/Dict2", input, mapSecond) == true);
			REQUIRE(DeserializeDictionary("TestDictionaries/Dict2") == mapSecond);
			
			input.close();
		}

		WHEN("First map in not equals second and answer use Not") // 3 case
		{
			mapFirst = { { "1", "1" } };
			mapSecond = { { "1", "1" }, { "2", "2" }, { "3", "3" } };

			input.open("TestStreams/2Scenario/3CaseIn.txt");

			REQUIRE(IsUserChangeDictionary(mapFirst, mapSecond) == true);
			REQUIRE(SaveDictionary("TestDictionaries/Dict2", input, mapSecond) == false);
			REQUIRE(DeserializeDictionary("TestDictionaries/Dict2") != mapSecond);

			input.close();
		}
	}
}

SCENARIO("Use Translator") // 3 scenario
{
	GIVEN("Map")
	{
		std::map<std::string, std::string> map;
		std::map<std::string, std::string> expectedMap;

		std::ifstream input;
		std::fstream output;

		WHEN("Map is empty and user type a new word") // 1 case
		{
			map = {};
			expectedMap = { { "dog", "sabaka" } };

			input.open("TestStreams/3Scenario/1CaseIn.txt");
			output.open("TestStreams/3Scenario/1CaseOut.txt");

			REQUIRE(UseTranslator(input, output, map) == expectedMap);

			input.close();
			output.close();
		}

		WHEN("User type a word that exist in dictionary") // 2 case
		{
			map = { { "dog", "sabaka" } };
			expectedMap = map;

			input.open("TestStreams/3Scenario/2CaseIn.txt");
			output.open("TestStreams/3Scenario/2CaseOut.txt");

			REQUIRE(UseTranslator(input, output, map) == expectedMap);

			input.close();
			output.close();
		}
	}
}