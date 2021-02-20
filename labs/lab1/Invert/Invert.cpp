// Invert.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <cmath>
#include <fstream>
#include <iostream>
#include <math.h>
#include <optional>
#include <string>

struct Args
{
	std::string inputFileName;
	std::string outputFileName;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 3)
	{
		std::cout << "Invalid argument count.\n";
		std::cout << "Usage: Invert.exe <matrix file1> <output file name>.\n";
		return std::nullopt;
	}
	Args args;
	args.inputFileName = argv[1];
	args.outputFileName = argv[2];

	return args;
}

int CalculateDeterminantTwoOnTwo(const int (&matrix)[2][2])
{
	return ((matrix[0][0] * matrix[1][1]) - (matrix[1][0] * matrix[0][1]));
}

int CalculateDeterminantThreeOnThree(const int (&matrix)[3][3])
{
	int firstTriangle = (matrix[0][0] * matrix[1][1] * matrix[2][2])
		+ (matrix[2][0] * matrix[0][1] * matrix[1][2])
		+ (matrix[1][0] * matrix[2][1] * matrix[0][2]);

	int secondTriangle = (matrix[2][0] * matrix[1][1] * matrix[0][2])
		+ (matrix[1][0] * matrix[0][1] * matrix[2][2])
		+ (matrix[0][0] * matrix[2][1] * matrix[1][2]);

	return (firstTriangle - secondTriangle);
}

void FindMinor(const int& exceptRow, const int& exceptColumn, const int (&matrix)[3][3], int (&minor)[2][2])
{
	int k = 0;
	int t = 0;
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			if ((i != exceptRow) && (j != exceptColumn))
			{
				minor[t][k] = matrix[i][j];
				if ((k == 1) && (t == 0))
				{
					t = 1;
					k = 0;
				}
				else
				{
					k++;
				}
			}
		}
	}
}

void TransposeMatrix(int (&transposeMatrix)[3][3])
{
	int tempMatrix[3][3]{};

	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			tempMatrix[i][j] = transposeMatrix[j][i];
		}
	}
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			transposeMatrix[i][j] = tempMatrix[i][j];
		}
	}
}

void CalculateComplementMatrix(const int (&matrix)[3][3], int (&complementMatrix)[3][3])
{
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			int minor[2][2];
			FindMinor(i, j, matrix, minor);
			complementMatrix[i][j] = std::pow((-1), (i + j)) * CalculateDeterminantTwoOnTwo(minor);
		}
	}
}

void CalculateInverseMatrix(const int& matrixDeterminant, const int (&tempMatrix)[3][3], double (&result)[3][3])
{
	double inverseDeterminant = (static_cast<double>(1) / matrixDeterminant);
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			result[i][j] = std::round((inverseDeterminant * tempMatrix[i][j]) * 1000) / 1000;
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

	// инициализация массива
	int matrix[3][3]{};

	std::string line;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (!(input >> matrix[i][j]))
			{
				std::cout << "Error, while read " << args->inputFileName << "\n";
				std::cout << "The dimension of the matrix must be 3 by 3" << "\n";
				return 1;
			}
		}
		std::getline(input, line);
	}
	std::cout << "\n\n";

	int matrixDeterminant = CalculateDeterminantThreeOnThree(matrix);
	if (matrixDeterminant == 0)
	{
		std::cout << "Determinant = 0, then inverse matrix doesn't exist. \nPlease try again. \n";
		return 1;
	}
	else
	{
		int tempMatrix[3][3];
		CalculateComplementMatrix(matrix, tempMatrix);
		TransposeMatrix(tempMatrix);

		double result[3][3];
		CalculateInverseMatrix(matrixDeterminant, tempMatrix, result);

		for (size_t i = 0; i < 3; i++)
		{
			for (size_t j = 0; j < 3; j++)
			{
				std::cout << result[i][j] << " ";
			}
			std::cout << "\n";
		}
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
