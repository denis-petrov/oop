// Fill.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <fstream>
#include <iostream>
#include <optional>
#include <queue>
#include <string>
#include <vector>
#include "Fill.h"

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

enum Field
{
	EMPTY,
	WALL = '#',
	FILL = '.',
	START = 'O',
};

struct WrappedField
{
	Field field[FIELD_SIZE][FIELD_SIZE]{};
};

struct Tuple
{
	WrappedField wrappedField;
	std::vector<Cell> startCells;
};

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

void PrintField(const WrappedField& wrappedField, std::ofstream& output, Error& error)
{
	for (size_t i = 0; i < FIELD_SIZE; i++)
	{
		for (size_t j = 0; j < FIELD_SIZE; j++)
		{
			if (!(output << (char)wrappedField.field[i][j]))
			{
				error.message = "Unable write to output file.\n";
				error.wasError = 1;
			}
		}
		output << std::endl;
	}
}

Tuple ReadMatrixFromInputFile(std::ifstream& input)
{
	WrappedField wrappedResult{};
	std::vector<Cell> startCells;

	std::string line;
	int row = 0;
	while (std::getline(input, line) && (row != FIELD_SIZE))
	{
		for (int column = 0; column < line.length(); column++)
		{
			if (column == FIELD_SIZE)
			{
				break;
			}

			if (line[column] == Field::WALL)
			{
				wrappedResult.field[row][column] = Field::WALL;
			}
			else if (line[column] == Field::START)
			{
				startCells.push_back({ row, column });
				wrappedResult.field[row][column] = Field::START;
			}
			else
			{
				wrappedResult.field[row][column] = Field::EMPTY;
			}
		}
		row++;
	}

	return { wrappedResult, startCells };
}

bool IsEmptyCell(const int& row, const int& column, const WrappedField& wrappedField)
{
	return ((0 <= row) && (row < FIELD_SIZE) && (0 <= column) && (column < FIELD_SIZE) && (wrappedField.field[row][column] == Field::EMPTY));
}

void GoToNextCellIfEmptyAndPushToQueue(const int& curRow, const int& curCol, WrappedField& wrappedField, std::queue<Cell>& queue)
{
	if (IsEmptyCell(curRow, curCol, wrappedField))
	{
		wrappedField.field[curRow][curCol] = Field::FILL;
		queue.push({ curRow, curCol });
	}
}

void CrawlingTheArea(WrappedField& wrappedField, const int& rowStart, const int& columnStart)
{
	std::queue<Cell> queue;
	wrappedField.field[rowStart][columnStart] = Field::FILL;
	queue.push(Cell{ rowStart, columnStart });

	while (!queue.empty())
	{
		Cell currentCell = queue.front();
		queue.pop();

		int curRow = currentCell.row;
		int curCol = currentCell.column;

		GoToNextCellIfEmptyAndPushToQueue(curRow - 1, curCol, wrappedField, queue);
		GoToNextCellIfEmptyAndPushToQueue(curRow + 1, curCol, wrappedField, queue);
		GoToNextCellIfEmptyAndPushToQueue(curRow, curCol - 1, wrappedField, queue);
		GoToNextCellIfEmptyAndPushToQueue(curRow, curCol + 1, wrappedField, queue);
	}
}

void FillField(WrappedField& wrappedField, const std::vector<Cell> (&starts))
{
	for (size_t i = 0; i < starts.size(); i++)
	{
		CrawlingTheArea(wrappedField, starts[i].row, starts[i].column);
		wrappedField.field[starts[i].row][starts[i].column] = Field::START;
	}
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

	auto [field, starts] = ReadMatrixFromInputFile(input);

	Error error;
	error.wasError = false;

	FillField(field, starts);

	PrintField(field, output, error);

	if (error.wasError)
	{
		std::cout << error.message << std::endl;
		return 1;
	}

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
