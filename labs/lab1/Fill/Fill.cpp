// Fill.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <fstream>
#include <iostream>
#include <optional>
#include <queue>
#include <string>
#include <tuple>

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
const int COUNT_CELLS = FIELD_SIZE * FIELD_SIZE;

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
	Field field[FIELD_SIZE][FIELD_SIZE]{NO_DATA};
};

struct Tuple
{
	WrappedField wrappedField;
	Cell* startCells;
	int countStarts;
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

void PrintMessageToOutput(std::ofstream& output, const Error& error)
{
	if (!(output << error.message))
	{
		std::cout << "Error, while write to output file.\n";
	}
}
//
//WrappedPath FillMatrixByEmptyData()
//{
//	WrappedPath wrappedPath{};
//
//	for (int i = 0; i < FIELD_SIZE; ++i)
//	{
//		for (int j = 0; j < FIELD_SIZE; ++j)
//		{
//			wrappedPath.path[i][j] = NO_DATA;
//		}
//	}
//
//	return wrappedPath;
//}
//
//bool IsLessCharInLineThenNeed(const int & postition, const int & lineLength)
//{
//	return (postition == (lineLength - 1)) && (postition < FIELD_SIZE);
//}
//
//
//
//bool IsNotCellStart(const int& currentRow, const int& currentColumn, const int& startRow, const int& startColumn)
//{
//	return (currentRow != startRow) && (currentColumn != startColumn);
//}
//
//bool IsAbleGoTop(const int& row, const int& column, const Path& field)
//{
//	if ((row != 0) && (field[row - 1][column] == EMPTY))
//	{
//		return true;
//	}
//	return false;
//}
//
//bool IsAbleGoBottom(const int& row, const int& column, const Path& field)
//{
//	if ((row != FIELD_SIZE) && (field[row + 1][column] == EMPTY))
//	{
//		return true;
//	}
//	return false;
//}
//
//

void PrintField(const WrappedField& wrappedField)
{
	for (size_t i = 0; i < FIELD_SIZE; i++)
	{
		for (size_t j = 0; j < FIELD_SIZE; j++)
		{
			std::cout << wrappedField.field[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

//WrappedField InitializeFieldByNoData()
//{
//	WrappedField wrappedField{};
//	for (size_t i = 0; i < FIELD_SIZE; i++)
//	{
//		for (size_t j = 0; j < FIELD_SIZE; j++)
//		{
//			wrappedField.field[i][j] = NO_DATA;
//		}
//	}
//	return wrappedField;
//}

Tuple ReadMatrixFromInputFile(std::ifstream& input, Error& error)
{
	WrappedField wrappedResult{};
	Cell startCells[COUNT_CELLS]{};
	int countStarts = 0;

	std::string line;
	int row = 0;
	while (std::getline(input, line))
	{
		for (int column = 0; column < line.length(); column++)
		{
			if ((row == FIELD_SIZE) && (column == FIELD_SIZE))
			{
				return { wrappedResult, startCells, countStarts };
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
				startCells[countStarts] = { row, column };
				countStarts++;
				wrappedResult.field[row][column] = START;
			}
			else
			{
				wrappedResult.field[row][column] = EMPTY;
			}
		}
		row++;
	}

	return { wrappedResult, startCells, countStarts };
}

WrappedField CrawlingTheArea(const WrappedField& wrappedField, const int& row, const int& column)
{
	WrappedField area{};

	std::queue<Cell> queue;
	queue.push(Cell{ row, column });

	while (!queue.empty())
	{
		Cell currentCell = queue.front();
		queue.pop();

		int curRow = currentCell.row;
		int curCol = currentCell.column;

		/*if (IsNotCellStart(curRow, curCol, row, column))
		{
			area.field[curRow][curCol] = FILL;
		}

		if (IsAbleGoTop(curRow, curCol, area.field))
		{
			queue.field({ curRow - 1, curCol });
		}

		if (IsAbleGoBottom(curRow, curCol, area.field))
		{
			queue.push({ curRow + 1, curCol });
		}*/
	}
	return CrawlingTheArea
}

WrappedField FillField(const WrappedField& wrappedField, Cell* starts, const int & countStarts)
{
	WrappedField fillField{};
	for (size_t i = 0; i < countStarts; i++)
	{
		fillField = CrawlingTheArea(wrappedField, starts[countStarts].row, starts[countStarts].column);
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

	auto [field, starts, countStarts] = ReadMatrixFromInputFile(input, error);

	if (error.wasError)
	{
		PrintMessageToOutput(output, error);
		return 1;
	}

	//field = FillField(field, starts, countStarts);

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
