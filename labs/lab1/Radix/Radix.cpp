// Radix.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <fstream>
#include <iostream>
#include <map>
#include <optional>
#include <string>

struct Args
{
	std::string sourceNotation;
	std::string destinationNotation;
	std::string value;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 4)
	{
		std::cout << "Invalid argument count.\n";
		std::cout << "Usage: CopyFile.exe <source notation> <destination notation> <value>.\n";
		return std::nullopt;
	}
	Args args;
	args.sourceNotation = argv[1];
	args.destinationNotation = argv[2];
	args.value = argv[3];

	return args;
}

char intToChar(int integerValue)
{
	char convert[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
		'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
	return convert[integerValue];
}

int charlToInt(char symbol)
{
	std::map<std::string, int> convertMap {
		{ "0", 0 }, { "1", 1 }, { "2", 2 }, { "3", 3 }, { "4", 4 }, { "5", 5 }, { "6", 6 }, { "7", 7 }, { "8", 8 }, { "9", 9 },
		{ "A", 10 }, { "B", 11 }, { "C", 12 }, { "D", 13 }, { "E", 14 }, { "F", 15 }, { "G", 16 }, { "H", 17 },
		{ "I", 18 }, { "J", 19 }, { "K", 20 }, { "L", 21 }, { "M", 22 }, { "N", 23 }, { "O", 24 }, { "P", 25 },
		{ "Q", 26 }, { "R", 27 }, { "S", 28 }, { "T", 29 }, { "U", 30 }, { "V", 31 }, { "W", 32 }, { "X", 33 }, { "Y", 34 },
		{ "Z", 35 },
	};

	return convertMap[symbol];
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	// Проверка правильности аргуметов командной строки
	if (!args)
	{
		return 1;
	}

	std::cout << args->destinationNotation << args->sourceNotation << args->value << "\n";

	return 0;
}
