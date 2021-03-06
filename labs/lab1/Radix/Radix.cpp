// Radix.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Radix.h"
#include <cmath>
#include <iostream>
#include <optional>
#include <string>

struct Args
{
	std::string sourceNotation;
	std::string destinationNotation;
	std::string value;
};

struct Error
{
	bool wasError;
	std::string message;
};

const int ASCII_MINUS = 45;
const int ASCII_ZERO = 48;
const int ASCII_NINE = 57;
const int ASCII_A = 65;
const int ASCII_Z = 90;
const int COEF_FOR_CONVERT_LETTER = 55;
const int INCORRECT_SYMBOL = -1;

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

char IntToSymbol(const int value)
{
	char convert[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
		'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
	return convert[value];
}

int SymbolToInt(const char symbol)
{
	int symbolCode = symbol;
	if (symbolCode == ASCII_MINUS)
	{
		return ASCII_MINUS;
	}
	else if ((ASCII_ZERO <= symbolCode) && (symbolCode <= ASCII_NINE))
	{
		return (symbolCode - ASCII_ZERO);
	}
	else if ((ASCII_A <= symbolCode) && (symbolCode <= ASCII_Z))
	{
		return (symbolCode - COEF_FOR_CONVERT_LETTER);
	}
	else
	{
		return INCORRECT_SYMBOL;
	}
}

bool IsFoundFirstMinusInString(const int symbolInt, const bool& isMinusMet)
{
	return (symbolInt == ASCII_MINUS) && (!isMinusMet);
}

void ValidateFirstMetMinusInString(const int symbolInt, bool& isMinusMet, const size_t& position, int& power, Error& error)
{
	if (IsFoundFirstMinusInString(symbolInt, isMinusMet))
	{
		if (position == 0)
		{
			isMinusMet = true;
			power--;
		}
		else
		{
			error.message = "Position of minus is incorrect. \n";
			error.wasError = true;
		}
	}
}

bool IsSymbolIncorrectInNotation(const int symbolInt, const int radix)
{
	return ((symbolInt >= radix) || (symbolInt == INCORRECT_SYMBOL));
}

bool IsCurrentIsNotMinus(const bool& isMinusMet, const size_t& position)
{
	return ((isMinusMet) && (position != 0)) || (!isMinusMet);
}

void ValidateSymbolLessMaxInNotation(const int symbolInt, const bool& isMinusMet, const int radix, const std::string& value, const size_t& position, Error& error)
{
	if (IsSymbolIncorrectInNotation(symbolInt, radix) && IsCurrentIsNotMinus(isMinusMet, position))
	{
		std::string symbol(1, value[position]);
		error.message = "Symbol " + symbol + std::string(" is incorrect in ") + std::to_string(radix) + " notation. \n";
		error.wasError = true;
	}
}

bool IsOverflow(const int number, const int digit, const int radix, const bool& isMinusMet)
{
	if (!isMinusMet)
	{
		return ((number >= (INT_MAX / radix)) && (abs(digit) > (INT_MAX % radix))) || (number < 0);
	}
	else
	{
		return ((number <= (INT_MIN / radix)) && (abs(digit) > abs(INT_MIN % radix)));
	}
}

int StringToInt(const std::string& value, const int radix, Error& error)
{
	bool isMinusMet = false;
	int result = 0;
	for (size_t i = 0; i < value.length(); i++)
	{
		int currentDigit = SymbolToInt(value[i]);
		int power = value.length() - (i + 1);

		if (!isMinusMet)
		{
			ValidateFirstMetMinusInString(currentDigit, isMinusMet, i, power, error);
		}

		ValidateSymbolLessMaxInNotation(currentDigit, isMinusMet, radix, value, i, error);

		if (IsOverflow(result, currentDigit, radix, isMinusMet))
		{
			error.wasError = true;
			error.message = "Overflow integer value. \n";
		}

		if (error.wasError)
		{
			break;
		}

		if (IsCurrentIsNotMinus(isMinusMet, i))
		{
			if (isMinusMet)
			{
				result = result * radix - currentDigit;
			}
			else
			{
				result = result * radix + currentDigit;
			}
		}
	}

	return result;
}

std::string IntToString(int number, const int radix)
{
	std::string result;

	bool isNegative = (number < 0);

	int remainder;
	while (number != 0)
	{
		remainder = abs(number % radix);
		number /= radix;
		result = IntToSymbol(remainder) + result;
	}

	if (isNegative)
	{
		result.insert(0, "-");
	}
	return result;
}

std::string ConvertValueToDestinationNotation(const int sourceNotation, const int destinationNotation, const std::string& value, Error& error)
{
	if (value == "0")
	{
		return std::to_string(0);
	}

	int valueInTenNotation = StringToInt(value, sourceNotation, error);

	if (!error.wasError)
	{
		return IntToString(valueInTenNotation, destinationNotation);
	}
	return "";
}

bool IsNotationNotCorrect(const int notation) 
{
	return !(notation >= 2 && notation <= 36);
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	if (!args)
	{
		return 1;
	}

	int sourceNotation = 0;
	int destinationNotation = 0;
	try
	{
		sourceNotation = std::stoi(args->sourceNotation);
		destinationNotation = std::stoi(args->destinationNotation);

		if (IsNotationNotCorrect(sourceNotation))
		{
			throw std::invalid_argument("Invalid <" + args->sourceNotation + "> notation value.\n");
		}
		if (IsNotationNotCorrect(destinationNotation))
		{
			throw std::invalid_argument("Invalid <" + args->destinationNotation + "> notation value.\n");
		}
	}	
	catch (std::out_of_range& e)
	{
		std::cout << "Value of <notation> is not in range from 2 to 36";
		return 1;
	}
	catch (std::invalid_argument& e)
	{
		std::cout << e.what();
		return 1;
	}
	catch (std::exception& e)
	{
		std::cout << e.what();
		return 1;
	}

	Error error;
	error.wasError = false;

	std::string valueInRadixNotation = ConvertValueToDestinationNotation(sourceNotation, destinationNotation, args->value, error);

	if (error.wasError)
	{
		error.message += "Please try again.\n";
		std::cout << error.message;
		return 1;
	}
	else
	{
		std::cout << "Value in " << args->sourceNotation << " notation = " << args->value << "\n"
				  << "Value in " << args->destinationNotation << " noation = " << valueInRadixNotation << "\n";
	}

	return 0;
}
