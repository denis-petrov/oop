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

typedef double Matrix3x3[MATRIX_SIZE][MATRIX_SIZE];
typedef double Matrix2x2[MINOR_SIZE][MINOR_SIZE];

struct WrappedMatrix3x3
{
	Matrix3x3 items;
};

struct WrappedMatrix2x2
{
	Matrix2x2 items;
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

WrappedMatrix3x3 ReadInputDataToMatrix(std::ifstream& input, Error& error)
{
	WrappedMatrix3x3 wrappedMatrix3x3{};

	std::string line;
	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		for (int j = 0; j < MATRIX_SIZE; j++)
		{
			if (!(input >> wrappedMatrix3x3.items[i][j]))
			{
				error.wasError = true;
				error.message = (std::string) "Error, while read <matrix file1> \nThe dimension of the matrix must be 3 by 3." + "\n"
					+ (std::string) "Symbols must be numbers and be only digits from 0 to 9.\n";
				return wrappedMatrix3x3;
			}
		}
		if (!(std::getline(input, line)))
		{
			return wrappedMatrix3x3;
		}
	}

	return wrappedMatrix3x3;
}

double CalculateDeterminantMatrix2x2(const Matrix2x2& minor)
{
	return ((minor[0][0] * minor[1][1]) - (minor[1][0] * minor[0][1]));
}

int CalculateDeterminantMatrix3x3(const Matrix3x3& matrix)
{
	int firstTriangle = (matrix[0][0] * matrix[1][1] * matrix[2][2])
		+ (matrix[2][0] * matrix[0][1] * matrix[1][2])
		+ (matrix[1][0] * matrix[2][1] * matrix[0][2]);

	int secondTriangle = (matrix[2][0] * matrix[1][1] * matrix[0][2])
		+ (matrix[1][0] * matrix[0][1] * matrix[2][2])
		+ (matrix[0][0] * matrix[2][1] * matrix[1][2]);

	return (firstTriangle - secondTriangle);
}

WrappedMatrix2x2 FindMinor(const int& exceptRow, const int& exceptColumn, const Matrix3x3& matrix)
{
	WrappedMatrix2x2 wrappedMatrix2x2{};

	int k = 0;
	int t = 0;
	for (size_t i = 0; i < MATRIX_SIZE; i++)
	{
		for (size_t j = 0; j < MATRIX_SIZE; j++)
		{
			if ((i != exceptRow) && (j != exceptColumn))
			{
				wrappedMatrix2x2.items[t][k] = matrix[i][j];
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
	return wrappedMatrix2x2;
}

WrappedMatrix3x3 TransposeMatrix(const Matrix3x3& matrix)
{
	WrappedMatrix3x3 wrappedTronspesedMatrix{};

	for (size_t i = 0; i < MATRIX_SIZE; i++)
	{
		for (size_t j = 0; j < MATRIX_SIZE; j++)
		{
			wrappedTronspesedMatrix.items[i][j] = matrix[j][i];
		}
	}

	return wrappedTronspesedMatrix;
}

WrappedMatrix3x3 CalculateComplementMatrix(const Matrix3x3& matrix)
{
	WrappedMatrix3x3 wrappedComplementMatrix{};

	for (size_t i = 0; i < MATRIX_SIZE; i++)
	{
		for (size_t j = 0; j < MATRIX_SIZE; j++)
		{
			wrappedComplementMatrix.items[i][j] = std::pow((-1), (i + j)) * CalculateDeterminantMatrix2x2(FindMinor(i, j, matrix).items);
		}
	}

	return wrappedComplementMatrix;
}

WrappedMatrix3x3 CalculateInverseMatrix(const int& matrixDeterminant, const Matrix3x3& transposeMatrix)
{
	WrappedMatrix3x3 wrappedInverseMatrix{};

	double inverseDeterminant = (static_cast<double>(1) / matrixDeterminant);
	for (size_t i = 0; i < MATRIX_SIZE; i++)
	{
		for (size_t j = 0; j < MATRIX_SIZE; j++)
		{
			wrappedInverseMatrix.items[i][j] = std::round((inverseDeterminant * transposeMatrix[i][j]) * 1000) / 1000;
		}
	}

	return wrappedInverseMatrix;
}

WrappedMatrix3x3 InvertMatrix(const Matrix3x3& matrix, Error& error)
{
	int matrixDeterminant = CalculateDeterminantMatrix3x3(matrix);
	if (matrixDeterminant == 0)
	{
		error.message = "Determinant = 0, then inverse matrix doesn't exist. \nPlease try again. \n";
		error.wasError = true;
		return WrappedMatrix3x3{};
	}

	WrappedMatrix3x3 complemntMatrix = CalculateComplementMatrix(matrix);
	WrappedMatrix3x3 transposedComplementMatrix = TransposeMatrix(complemntMatrix.items);

	return CalculateInverseMatrix(matrixDeterminant, transposedComplementMatrix.items);
}

Error PrintMatrixToOutputReturnError(std::ofstream& output, const Matrix3x3& matrix, Error& error)
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

	WrappedMatrix3x3 inputMatrix = ReadInputDataToMatrix(input, error);
	if (error.wasError)
	{
		PrintMessageToOutput(output, error);
		return 1;
	}

	WrappedMatrix3x3 invertMatrix = InvertMatrix(inputMatrix.items, error);
	if (error.wasError)
	{
		PrintMessageToOutput(output, error);
		return 1;
	}

	if (PrintMatrixToOutputReturnError(output, invertMatrix.items, error).wasError)
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
