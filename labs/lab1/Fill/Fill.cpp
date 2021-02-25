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

enum Field
{
	NO_DATA,
	EMPTY,
	WALL = '#',
	FILL = '.',
	START = 'O',
};

struct WrappedField
{
	Field field[FIELD_SIZE][FIELD_SIZE]{ NO_DATA };
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

WrappedField CopyField(const WrappedField& wrappedField)
{
	WrappedField copy{};

	for (size_t i = 0; i < FIELD_SIZE; i++)
	{
		for (size_t j = 0; j < FIELD_SIZE; j++)
		{
			copy.field[i][j] = wrappedField.field[i][j];
		}
	}
	return copy;
}

void PrintField(const WrappedField& wrappedField)
{
	for (size_t i = 0; i < FIELD_SIZE; i++)
	{
		for (size_t j = 0; j < FIELD_SIZE; j++)
		{
			if (wrappedField.field[i][j] == WALL)
			{
				std::cout << '#';
			}
			else if (wrappedField.field[i][j] == START)
			{
				std::cout << 'O';
			}
			else if (wrappedField.field[i][j] == FILL)
			{
				std::cout << '.';
			}
			else
			{
				std::cout << ' ';
			}
		}
		std::cout << std::endl;
	}
}

Tuple ReadMatrixFromInputFile(std::ifstream& input)
{
	WrappedField wrappedResult{};
	std::vector<Cell> startCells;

	std::string line;
	int row = 0;
	while (std::getline(input, line))
	{
		for (int column = 0; column < line.length(); column++)
		{
			if ((row == FIELD_SIZE) && (column == FIELD_SIZE))
			{
				return { wrappedResult, startCells };
			}
			if (column == FIELD_SIZE)
			{
				break;
			}

			if (line[column] == WALL)
			{
				wrappedResult.field[row][column] = WALL;
			}
			else if (line[column] == START)
			{
				startCells.push_back({ row, column });
				wrappedResult.field[row][column] = START;
			}
			else
			{
				wrappedResult.field[row][column] = EMPTY;
			}
		}
		row++;
	}

	return { wrappedResult, startCells };
}

bool IsNotCellStart(const int& currentRow, const int& currentColumn, const int& startRow, const int& startColumn)
{
	return (currentRow != startRow) && (currentColumn != startColumn);
}

bool IsAbleGoTop(const int& row, const int& column, const WrappedField& wrappedField)
{
	if ((0 < row) && (wrappedField.field[row - 1][column] == EMPTY))
	{
		return true;
	}
	return false;
}

bool IsAbleGoBottom(const int& row, const int& column, const WrappedField& wrappedField)
{
	if ((0 < row < FIELD_SIZE) && (wrappedField.field[row + 1][column] == EMPTY))
	{
		return true;
	}
	return false;
}

bool IsAbleGoLeft(const int& row, const int& column, const WrappedField& wrappedField)
{
	if ((0 < column) && (wrappedField.field[row][column - 1] == EMPTY))
	{
		return true;
	}
	return false;
}

bool IsAbleGoRight(const int& row, const int& column, const WrappedField& wrappedField)
{
	if ((column < FIELD_SIZE) && (wrappedField.field[row][column + 1] == EMPTY))
	{
		return true;
	}
	return false;
}

WrappedField CrawlingTheArea(const WrappedField& wrappedField, const int& rowStart, const int& columnStart)
{
	WrappedField area{ CopyField(wrappedField) };

	std::queue<Cell> queue;
	queue.push(Cell{ rowStart, columnStart });

	while (!queue.empty())
	{
		Cell currentCell = queue.front();
		queue.pop();

		int curRow = currentCell.row;
		int curCol = currentCell.column;

		if (IsNotCellStart(curRow, curCol, rowStart, columnStart))
			area.field[curRow][curCol] = FILL;

		if (IsAbleGoTop(curRow, curCol, area))
			queue.push({ curRow - 1, curCol });

		if (IsAbleGoBottom(curRow, curCol, area))
			queue.push({ curRow + 1, curCol });

		if (IsAbleGoLeft(curRow, curCol, area))
			queue.push({ curRow, curCol - 1 });

		if (IsAbleGoRight(curRow, curCol, area))
			queue.push({ curRow, curCol + 1 });
	}
	return area;
}

WrappedField FillField(const WrappedField& wrappedField, const std::vector<Cell> (&starts))
{
	WrappedField fillField{};
	for (size_t i = 0; i < starts.size(); i++)
	{
		fillField = CrawlingTheArea(wrappedField, starts[i].row, starts[i].column);
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

	auto [field, starts] = ReadMatrixFromInputFile(input);

	field = FillField(field, starts);

	PrintField(field);

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
