// Radix.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <fstream>
#include <iostream>
#include <optional>
#include <string>
#include <cmath>

struct Args
{
	std::string sourceNotation;
	std::string destinationNotation;
	std::string value;
	std::string outputFileName;
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
	if (argc != 5)
	{
		std::cout << "Invalid argument count.\n";
		std::cout << "Usage: CopyFile.exe <source notation> <destination notation> <value> <output file>.\n";
		return std::nullopt;
	}
	Args args;
	args.sourceNotation = argv[1];
	args.destinationNotation = argv[2];
	args.value = argv[3];
	args.outputFileName = argv[4];

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
	if (symbolCode == ASCII_MINUS) // -
	{
		return ASCII_MINUS;
	}
	else if ((ASCII_ZERO <= symbolCode) && (symbolCode <= ASCII_NINE)) // 0..9
	{
		return (symbolCode - ASCII_ZERO);
	}
	else if ((ASCII_A <= symbolCode) && (symbolCode <= ASCII_Z)) // A..Z
	{
		return (symbolCode - COEF_FOR_CONVERT_LETTER);
	}
	else // не корректный символ
	{
		return INCORRECT_SYMBOL;
	}
}


int StringToInt(const std::string& str, const int radix, Error& error)
{
	bool isMinusMet = false;
	int result = 0;
	int power = 0;
	for (size_t i = 0; i < str.length(); i++)
	{
		int symbolInt = SymbolToInt(str[i]);
		power = str.length() - (i + 1);
		if ((symbolInt == ASCII_MINUS) && (!isMinusMet))
		{
			if (i == 0) // correct minus position
			{
				isMinusMet = true;
				power--;
			}
			else
			{
				error.message = "Position of minus is incorrect. \n";
				error.wasError = true;
				break;
			}
		}
		else if ((symbolInt >= radix) || (symbolInt == INCORRECT_SYMBOL))
		{
			std::string symbol{ str[i] };
			error.message = "Symbol " + symbol + std::string(" is incorrect in ") + std::to_string(radix) + " notation. \n";
			error.wasError = true;
			break;
		}
		else 
		{
			result = result + (symbolInt * std::pow(radix, power));
		 
			if (result < 0)
			{
				error.wasError = true;
				error.message = "Overflow integer value. \n";
				break;
			}
		}
	}

	if (isMinusMet)
	{
		return (result * (-1));
	}
	return result;
}

std::string IntToString(int n, const int radix)
{
	std::string result;
	std::string temp;

	bool isMinusMet = false;
	int remainder;
	int i = 0;
	if (n < 0)
	{
		isMinusMet = true;
		n = n * (-1);
	}

	while (n >= radix)
	{
		remainder = n % radix;
		n /= radix;
		std::string append(1, IntToSymbol(remainder));
		result.insert(0, append);
	}
	if (0 < n < radix)
	{
		std::string appendLast(1, IntToSymbol(n));
		result.insert(0, appendLast);
	}

	if (isMinusMet)
	{
		result.insert(0, "-");
	}
	return result;
}


int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	// Проверка правильности аргуметов командной строки
	if (!args)
	{
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

	// Валидация аргументов командной строки при конвертации к int
	int radix;
	try
	{
		radix = std::stoi(args->sourceNotation);
	}
	catch (std::invalid_argument& e)
	{
		std::cout << "Invalid <source notation> value.\n";
		return 1;
	}

	int destinationNotation;
	try
	{
		destinationNotation = std::stoi(args->destinationNotation);
	}
	catch (std::invalid_argument& e)
	{
		std::cout << "Invalid <destination notation> value.\n";
		return 1;
	}
	// Валидация аргументов командной строки в допустимых границах
	if (!(radix >= 2 && radix <= 36))
	{
		std::cout << "Value of <source notation> isn't more than 2 and less then 36. \n";
		return 1;
	}
	if (!(destinationNotation >= 2 && destinationNotation <= 36))
	{
		std::cout << "Value of <destination notation> isn't more than 2 and less then 36. \n";
		return 1;
	}


	if (args->value == "0")
	{
		output << "Value in " << args->sourceNotation << " notation = " << args->value << "\n";
		output << "Value in " << args->destinationNotation << " noation = " << 0 << "\n";
	}
	else
	{
		Error error;
		error.wasError = false;

		int valueInTenNotation = StringToInt(args->value, radix, error);
		std::string valueInRadixNotation; 
		if (!error.wasError)
		{
			valueInRadixNotation = IntToString(valueInTenNotation, destinationNotation);
		}

		if (error.wasError)
		{
			error.message += "Please try again.\n"; 
			output << error.message;
			return 1;
		}
		else
		{
			if (radix != 10)
			{
				output << "Value in " << args->sourceNotation << " notation = " << args->value << "\n";
				output << "Value in 10 notation = " << std::to_string(valueInTenNotation) << "\n";
				output << "Value in " << args->destinationNotation << " noation = " << valueInRadixNotation << "\n";
			} 
			else
			{
				output << "Value in 10 notation = " << std::to_string(valueInTenNotation) << "\n";
				output << "Value in " << args->destinationNotation << " noation = " << valueInRadixNotation << "\n";
			}
		}
	}

	if (!output.flush())
	{
		std::cout << "Failed to write data to output.\n";
		return 1;
	}

	return 0;
}
