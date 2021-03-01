// Fill.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <fstream>
#include <iostream>
#include <optional>
#include <queue>
#include <string>
#include <vector>

struct Args
{
	std::string inputFileName;
	std::string outputFileName;
};

struct Cell
{
	int row;
	int column;
};

const int FIELD_SIZE = 100;

enum CharTypes
{
	EMPTY = ' ',
	WALL = '#',
	FILL = '.',
	START = 'O',
};

typedef char Field[FIELD_SIZE][FIELD_SIZE];

struct WrappedField
{
	Field items;
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

void PrintField(const WrappedField& wrappedField, std::ofstream& output)
{
	for (size_t i = 0; i < FIELD_SIZE; i++)
	{
		for (size_t j = 0; j < FIELD_SIZE; j++)
		{
			output << (char)wrappedField.items[i][j];
		}
		output << std::endl;
	}
}

Tuple ReadMatrixFromInputFile(std::ifstream& input)
{
	WrappedField wrappedResult{};
	std::vector<Cell> startCells;

	std::string line;
	for (int row = 0; row < FIELD_SIZE; row++)
	{
		if (std::getline(input, line))
		{
			for (int column = 0; column < FIELD_SIZE; column++)
			{
				if (column == FIELD_SIZE)
				{
					break;
				}
				
				if (column < line.length())
				{
					if (line[column] == CharTypes::WALL)
					{
						wrappedResult.items[row][column] = CharTypes::WALL;
					}
					else if (line[column] == CharTypes::START)
					{
						startCells.push_back({ row, column });
						wrappedResult.items[row][column] = CharTypes::START;
					}
					else
					{
						wrappedResult.items[row][column] = CharTypes::EMPTY;
					}
				}
				else
				{
					wrappedResult.items[row][column] = CharTypes::EMPTY;
				}
			}
		}
		else
		{
			for (int column = 0; column < FIELD_SIZE; column++)
			{
				wrappedResult.items[row][column] = CharTypes::EMPTY;
			}
		}
	}

	return { wrappedResult, startCells };
}

bool IsEmptyCell(const int row, const int column, const WrappedField& wrappedField)
{
	return ((0 <= row) && (row < FIELD_SIZE) && (0 <= column) && (column < FIELD_SIZE) && (wrappedField.items[row][column] == CharTypes::EMPTY));
}

std::optional<Cell> FillCell(const int curRow, const int curCol, WrappedField& wrappedField, std::queue<Cell>& queue)
{
	if (IsEmptyCell(curRow, curCol, wrappedField))
	{
		wrappedField.items[curRow][curCol] = CharTypes::FILL;
		return Cell{ curRow, curCol };
	}
	return std::nullopt;
}

void CrawlingTheArea(WrappedField& wrappedField, const int rowStart, const int columnStart)
{
	std::queue<Cell> queue;
	queue.push(Cell{ rowStart, columnStart });

	while (!queue.empty())
	{
		Cell currentCell = queue.front();
		queue.pop();

		int curRow = currentCell.row;
		int curCol = currentCell.column;


		if (FillCell(curRow - 1, curCol, wrappedField, queue))
		{
			queue.push({ curRow - 1, curCol });
		}
		if (FillCell(curRow + 1, curCol, wrappedField, queue))
		{
			queue.push({ curRow + 1, curCol });
		}
		if (FillCell(curRow, curCol - 1, wrappedField, queue))
		{
			queue.push({ curRow, curCol - 1 });
		}
		if (FillCell(curRow, curCol + 1, wrappedField, queue))
		{
			queue.push({ curRow, curCol + 1 });
		}
	}
}

void FillField(WrappedField& wrappedField, const std::vector<Cell>& starts)
{
	for (size_t i = 0; i < starts.size(); i++)
	{
		CrawlingTheArea(wrappedField, starts[i].row, starts[i].column);
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

	FillField(field, starts);

	PrintField(field, output);

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
