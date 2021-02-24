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

double** InitializeMatrix()
{
	double** matrix = new double*[MATRIX_SIZE];
	for (int i = 0; i < MATRIX_SIZE; i++)
		matrix[i] = new double[MATRIX_SIZE];

	return matrix;
}

double** InitializeMinor()
{
	double** matrix = new double*[MATRIX_SIZE];
	for (int i = 0; i < MATRIX_SIZE; i++)
		matrix[i] = new double[MATRIX_SIZE];

	return matrix;
}

double** ReadInputDataToMatrix(std::ifstream& input, Error& error)
{
	double** matrix = InitializeMatrix();

	std::string line;
	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		for (int j = 0; j < MATRIX_SIZE; j++)
		{
			if (!(input >> matrix[i][j]))
			{
				error.wasError = true;
				error.message = (std::string) "Error, while read <matrix file1> \nThe dimension of the matrix must be 3 by 3." + "\n"
					+ (std::string) "Symbols must be numbers and be only digits from 0 to 9.\n";
				break;
			}
		}
		std::getline(input, line);
	}

	return matrix;
}

double CalculateDeterminantMatrixTwoOnTwo(double**& matrix)
{
	return ((matrix[0][0] * matrix[1][1]) - (matrix[1][0] * matrix[0][1]));
}

int CalculateDeterminantMatrixThreeOnThree(const double**& matrix)
{
	int firstTriangle = (matrix[0][0] * matrix[1][1] * matrix[2][2])
		+ (matrix[2][0] * matrix[0][1] * matrix[1][2])
		+ (matrix[1][0] * matrix[2][1] * matrix[0][2]);

	int secondTriangle = (matrix[2][0] * matrix[1][1] * matrix[0][2])
		+ (matrix[1][0] * matrix[0][1] * matrix[2][2])
		+ (matrix[0][0] * matrix[2][1] * matrix[1][2]);

	return (firstTriangle - secondTriangle);
}

double** FindMinor(const int& exceptRow, const int& exceptColumn, const double**& matrix)
{
	double** minor = InitializeMatrix();

	int k = 0;
	int t = 0;
	for (size_t i = 0; i < MATRIX_SIZE; i++)
	{
		for (size_t j = 0; j < MATRIX_SIZE; j++)
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
	return minor;
}

double** TransposeMatrix(double**& matrix)
{
	double** transposeMatrix = InitializeMatrix();

	for (size_t i = 0; i < MATRIX_SIZE; i++)
	{
		for (size_t j = 0; j < MATRIX_SIZE; j++)
		{
			transposeMatrix[i][j] = matrix[j][i];
		}
	}

	return transposeMatrix;
}

double** CalculateComplementMatrix(const double**& matrix)
{
	double** complementMatrix = InitializeMatrix();

	for (size_t i = 0; i < MATRIX_SIZE; i++)
	{
		for (size_t j = 0; j < MATRIX_SIZE; j++)
		{
			double** minor = FindMinor(i, j, matrix);
			complementMatrix[i][j] = std::pow((-1), (i + j)) * CalculateDeterminantMatrixTwoOnTwo(minor);
		}
	}

	return complementMatrix;
}

double** CalculateInverseMatrix(const int& matrixDeterminant, double**& transposeMatrix)
{
	double** inverseMatrix = InitializeMatrix();

	double inverseDeterminant = (static_cast<double>(1) / matrixDeterminant);
	for (size_t i = 0; i < MATRIX_SIZE; i++)
	{
		for (size_t j = 0; j < MATRIX_SIZE; j++)
		{
			inverseMatrix[i][j] = std::round((inverseDeterminant * transposeMatrix[i][j]) * 1000) / 1000;
		}
	}

	return inverseMatrix;
}

double** InvertMatrix(const double**& matrix, Error& error)
{
	double** result = InitializeMatrix();

	int matrixDeterminant = CalculateDeterminantMatrixThreeOnThree(matrix);
	if (matrixDeterminant == 0)
	{
		error.message = "Determinant = 0, then inverse matrix doesn't exist. \nPlease try again. \n";
		error.wasError = true;
	}
	else
	{
		double** tempMatrix = CalculateComplementMatrix(matrix);
		tempMatrix = TransposeMatrix(tempMatrix);

		result = CalculateInverseMatrix(matrixDeterminant, tempMatrix);
	}

	return result;
}

Error PrintMatrixToOutput(std::ofstream& output, const double**& matrix, Error& error)
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

void PrintMessageToOutput(std::ofstream& output, Error& error)
{
	if (!(output << error.message))
	{
		std::cout << "Error, while write to output file.\n";
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

	const double** inputMatrix = const_cast<const double**>(ReadInputDataToMatrix(input, error));
	if (error.wasError)
	{
		PrintMessageToOutput(output, error);
		return 1;
	}

	const double** invertMatrix = const_cast<const double**>(InvertMatrix(inputMatrix, error));
	if (error.wasError)
	{
		PrintMessageToOutput(output, error);
		return 1;
	}

	PrintMatrixToOutput(output, invertMatrix, error);
	if (error.wasError)
	{
		PrintMessageToOutput(output, error);
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
