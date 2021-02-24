// Fill.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <fstream>
#include <iostream>
#include <optional>
#include <string>

struct Args
{
	std::string inputFileName;
	std::string outputFileName;
};

struct Error
{
	bool wasError;
	std::string message;
};

struct Cell
{
	int row;
	int column;
};

const int FIELD_SIZE = 100;
const int QUEUE_SIZE = 10000;
const int EMPTY = ' ';
const int WALL = '#';
const int FILL = '.';
const int START = 'O';

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 3)
	{
		std::cout << "Invalid argument count.\n";
		std::cout << "Usage: Invert.exe <input file> <output file>.\n";
		return std::nullopt;
	}
	Args args;
	args.inputFileName = argv[1];
	args.outputFileName = argv[2];

	return args;
}

void PrintMessageToOutput(std::ofstream& output, const Error& error)
{
	if (!(output << error.message))
	{
		std::cout << "Error, while write to output file.\n";
	}
}

char** InitializeMatrix()
{
	char** matrix = new char*[FIELD_SIZE];
	for (int i = 0; i < FIELD_SIZE; i++)
		matrix[i] = new char[FIELD_SIZE];

	return matrix;
}

char** FillMatrixByEmptyData()
{
	char** result = InitializeMatrix();

	for (int i = 0; i < FIELD_SIZE; ++i)
	{
		for (int j = 0; j < FIELD_SIZE; ++j)
		{
			result[i][j] = EMPTY;
		}
	}

	return result;
}

bool IsLessCharInLineThenNeed(const int & postition, const int & lineLength) 
{
	return (postition == (lineLength - 1)) && (postition < FIELD_SIZE);
}

char** ReadMatrixFromInputFile(std::ifstream& input, Error & error) 
{
	char** result = FillMatrixByEmptyData();

	std::string line;
	size_t row = 0;
	while (std::getline(input, line))
	{
		if (row == FIELD_SIZE)
		{
			return result;
		}
		for (size_t i = 0; i < line.length(); i++)
		{	
			if (i == FIELD_SIZE)
			{
				break;
			}
			if (IsLessCharInLineThenNeed(i, line.length()))
			{
				error.wasError = true;
				error.message = "Field must need to be 100 by 100.\n";
				break;
			}
			if (line[i] == WALL)
			{
				result[row][i] = WALL;
			}
			if (line[i] == START)
			{
				result[row][i] = START;
			}
		}
		row++;
	}

	return result;
}

void PrintMatrix(char**& matrix)
{
	for (size_t i = 0; i < FIELD_SIZE; i++)
	{
		for (size_t j = 0; j < FIELD_SIZE; j++)
		{
			std::cout << matrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

bool IsNotCellStart(const int& currentRow, const int& currentColumn, const int& startRow, const int& startColumn)
{
	return (currentRow != startRow) && (currentColumn != startColumn);
}

char** CrawlingTheArea(char**& field, const int & row, const int & column, Error & error)
{
	Cell queue[QUEUE_SIZE];
	int indexQueue;
	queue[indexQueue] = Cell{ row, column };
	indexQueue++;

	while (indexQueue != 0)
	{
		Cell currentCell = queue[0];
		indexQueue--;

		if (indexQueue == (QUEUE_SIZE - 1))
		{
			error.wasError = true;
			error.message = "Overflow queue.\n";
		}

		if (IsNotCellStart(currentCell.row, currentCell.column, row, column))
		{
			field[currentCell.row][currentCell.column] = FILL;
		}

		if (field[]) // проверить на граничные значение и уйти в заполнение
		{
		}
	}
}

char** FillAllArea(char** & field) 
{
	char** fillField = FillMatrixByEmptyData();

	for (size_t i = 0; i < FIELD_SIZE; i++)
	{
		for (size_t j = 0; j < FIELD_SIZE; j++)
		{
			if (field[i][j] == START)
			{
				fillField = CrawlingTheArea(field, i, j);
			}
		}
	}
	return fillField;
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	if (!args)
	{
		return 1;
	}

	std::ifstream input;
	input.open(args->inputFileName);
	if (!input.is_open())
	{
		std::cout << "Failed to open '" << args->inputFileName << "' for reading.\n";
		return 1;
	}

	std::ofstream output;
	output.open(args->outputFileName);
	if (!output.is_open())
	{
		std::cout << "Failed to open '" << args->outputFileName << "' for reading.\n";
		return 1;
	}

	Error error;
	error.wasError = false;

	char** inputMatrix = ReadMatrixFromInputFile(input, error);

	if (error.wasError)
	{
		PrintMessageToOutput(output, error);
		return 1;
	}

	char** fillField = FillAllArea(inputMatrix);

	PrintMatrix(inputMatrix);
	
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
