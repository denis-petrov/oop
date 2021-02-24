// Invert.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <cmath>
#include <fstream>
#include <iostream>
#include <math.h>
#include <optional>
#include <string>

const int MINOR_SIZE = 2;
const int MATRIX_SIZE = 3;

typedef double Matrix[MATRIX_SIZE][MATRIX_SIZE];
typedef double Minor[MINOR_SIZE][MINOR_SIZE];

struct WrappedMatrix
{
	Matrix matrix;
};

struct WrappedMinor
{
	Minor minor;
};

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

WrappedMatrix ReadInputDataToMatrix(std::ifstream& input, Error& error)
{
	WrappedMatrix wrappedMatrix{};

	std::string line;
	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		for (int j = 0; j < MATRIX_SIZE; j++)
		{
			if (!(input >> wrappedMatrix.matrix[i][j]))
			{
				error.wasError = true;
				error.message = (std::string) "Error, while read <matrix file1> \nThe dimension of the matrix must be 3 by 3." + "\n"
					+ (std::string) "Symbols must be numbers and be only digits from 0 to 9.\n";
				return wrappedMatrix;
			}
		}
		if (!(std::getline(input, line)))
		{
			return wrappedMatrix;
		}
	}

	return wrappedMatrix;
}

double CalculateDeterminantMinorTwoOnTwo(const Minor& minor)
{
	return ((minor[0][0] * minor[1][1]) - (minor[1][0] * minor[0][1]));
}

int CalculateDeterminantMatrixThreeOnThree(const Matrix& matrix)
{
	int firstTriangle = (matrix[0][0] * matrix[1][1] * matrix[2][2])
		+ (matrix[2][0] * matrix[0][1] * matrix[1][2])
		+ (matrix[1][0] * matrix[2][1] * matrix[0][2]);

	int secondTriangle = (matrix[2][0] * matrix[1][1] * matrix[0][2])
		+ (matrix[1][0] * matrix[0][1] * matrix[2][2])
		+ (matrix[0][0] * matrix[2][1] * matrix[1][2]);

	return (firstTriangle - secondTriangle);
}

WrappedMinor FindMinor(const int& exceptRow, const int& exceptColumn, const Matrix& matrix)
{
	WrappedMinor wrappedMinor{};

	int k = 0;
	int t = 0;
	for (size_t i = 0; i < MATRIX_SIZE; i++)
	{
		for (size_t j = 0; j < MATRIX_SIZE; j++)
		{
			if ((i != exceptRow) && (j != exceptColumn))
			{
				wrappedMinor.minor[t][k] = matrix[i][j];
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
	return wrappedMinor;
}

WrappedMatrix TransposeMatrix(const Matrix& matrix)
{
	WrappedMatrix wrappedTronspesedMatrix{};

	for (size_t i = 0; i < MATRIX_SIZE; i++)
	{
		for (size_t j = 0; j < MATRIX_SIZE; j++)
		{
			wrappedTronspesedMatrix.matrix[i][j] = matrix[j][i];
		}
	}

	return wrappedTronspesedMatrix;
}

WrappedMatrix CalculateComplementMatrix(const Matrix& matrix)
{
	WrappedMatrix wrappedComplementMatrix{};

	for (size_t i = 0; i < MATRIX_SIZE; i++)
	{
		for (size_t j = 0; j < MATRIX_SIZE; j++)
		{
			wrappedComplementMatrix.matrix[i][j] = std::pow((-1), (i + j)) * CalculateDeterminantMinorTwoOnTwo(FindMinor(i, j, matrix).minor);
		}
	}

	return wrappedComplementMatrix;
}

WrappedMatrix CalculateInverseMatrix(const int& matrixDeterminant, const Matrix& transposeMatrix)
{
	WrappedMatrix wrappedInverseMatrix{};

	double inverseDeterminant = (static_cast<double>(1) / matrixDeterminant);
	for (size_t i = 0; i < MATRIX_SIZE; i++)
	{
		for (size_t j = 0; j < MATRIX_SIZE; j++)
		{
			wrappedInverseMatrix.matrix[i][j] = std::round((inverseDeterminant * transposeMatrix[i][j]) * 1000) / 1000;
		}
	}

	return wrappedInverseMatrix;
}

WrappedMatrix InvertMatrix(const Matrix& matrix, Error& error)
{
	int matrixDeterminant = CalculateDeterminantMatrixThreeOnThree(matrix);
	if (matrixDeterminant == 0)
	{
		error.message = "Determinant = 0, then inverse matrix doesn't exist. \nPlease try again. \n";
		error.wasError = true;
		return {};
	}

	WrappedMatrix complemntMatrix = CalculateComplementMatrix(matrix);
	WrappedMatrix transposedComplementMatrix = TransposeMatrix(complemntMatrix.matrix);

	return CalculateInverseMatrix(matrixDeterminant, transposedComplementMatrix.matrix);
}

Error PrintMatrixToOutputReturnError(std::ofstream& output, const Matrix& matrix, Error& error)
{
	for (size_t i = 0; i < MATRIX_SIZE; i++)
	{
		for (size_t j = 0; j < MATRIX_SIZE; j++)
		{
			if (!(output << matrix[i][j] << " "))
			{
				error.message = "Error, while write to output file.\n";
				error.wasError = true;
				break;
			}
		}
		output << "\n";
	}

	return error;
}

void PrintWasWriteError()
{
	std::cout << "Failed to write data to output.\n";
}

void PrintMessageToOutput(std::ofstream& output, Error& error)
{
	if (!(output << error.message))
	{
		PrintWasWriteError();
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

	Error error;
	error.wasError = false;

	WrappedMatrix inputMatrix = ReadInputDataToMatrix(input, error);
	if (error.wasError)
	{
		PrintMessageToOutput(output, error);
		return 1;
	}

	WrappedMatrix invertMatrix = InvertMatrix(inputMatrix.matrix, error);
	if (error.wasError)
	{
		PrintMessageToOutput(output, error);
		return 1;
	}

	if (PrintMatrixToOutputReturnError(output, invertMatrix.matrix, error).wasError)
	{
		PrintWasWriteError();
		return 1;
	}

	if (!output.flush())
	{
		PrintWasWriteError();
		return 1;
	}

	return 0;
}
