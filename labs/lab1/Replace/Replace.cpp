// Replace.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <optional>
#include <string>
#include "Replace.h"

struct Args
{
	std::string inputFileName;
	std::string outputFileName;
	std::string searchString;
	std::string replaceString;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 5)
	{
		std::cout << "Invalid argument count.\n";
		std::cout << "Usage: Replace.exe <input file name> <output file name> <search string> <replace string>.\n";
		return std::nullopt;
	}
	Args args;
	args.inputFileName = argv[1];
	args.outputFileName = argv[2];
	args.searchString = argv[3];
	args.replaceString = argv[4];

	return args;
}

std::string ReplaceString(const std::string& line, const std::string& searchString, const std::string& replacementString)
{
	size_t pos = 0;
	size_t foundPos = 0;
	size_t searchLength = searchString.length();
	std::string result;
	while (true)
	{
		foundPos = line.find(searchString, pos);
		result.append(line, pos, foundPos - pos);
		if (foundPos != std::string::npos)
		{
			result.append(replacementString);
			pos = foundPos + searchLength;
		}
		else
		{
			break;
		}
	}

	return result;
}

void CopyFileWithReplacedStrings(std::ifstream& input, std::ofstream& output,
	const std::string& searchString, const std::string& replacementString) {
	// Производим замену искомой строки на заменяемую
	std::string line;
	while (std::getline(input, line))
	{
		if (!(output << ReplaceString(line, searchString, replacementString) << "\n"))
		{
			break;
		}
	}
}

int main(int argc, char* argv[])
{
    auto args = ParseArgs(argc, argv);
	// Проверка правильности аргуметов командной строки
	if (!args)
	{
		return 1;
	}

	// Открываем входной файл
	std::ifstream input;
	input.open(args->inputFileName);
	if (!input.is_open())
	{
		std::cout << "Failed to open '" << args->inputFileName << "' for reading.\n";
		return 1;
	}

	// Открываем выходной файл
	std::ofstream output;
	output.open(args->outputFileName);
	if (!output.is_open())
	{
		std::cout << "Failed to open '" << args->outputFileName << "' for writing.\n";
		return 1;
	}

	CopyFileWithReplacedStrings(input, output, args->searchString, args->replaceString);

	if (input.bad())
	{
		std::cout << "Failed to read data from input file.\n";
		return 1;
	}

	if (!output.flush())
	{
		std::cout << "Failed to write data to output.\n";
		return 1;
	}

	return 0;
}
