#pragma once
#include "stdafx.h"

class CCalculator
{
	enum class Operation
	{
		ADD,
		SUBTRACT,
		MULTIPLICATION,
		DIVISION
	};

	struct Func
	{
		std::string first;
		std::optional<Operation> operation;
		std::optional<std::string> second;
	};

public:
	CCalculator();
	~CCalculator();

	std::optional<std::string> GetEntityValue(const std::string& name) const;

	/* Variables */
	bool DeclareVariable(const std::string& name);
	bool InitializeVariable(const std::string& name, const std::string& identifier);

	std::string GetVariables() const;


	/* Functions */
	bool InitializeFunction(const std::string& name, const std::string& first);
	bool InitializeFunction(const std::string& name, const std::string& first, const char operation, const std::string& second);

private:
	/* Variables */
	std::map<std::string, double> m_existingVariables;

	bool IsVariableExist(const std::string& name) const;
	bool UpdateVariable(const std::string& name, const double value);

	double ConvertVariableValue(const std::string& value) const;
	std::optional<double> GetVariableValue(const std::string& name) const;
	std::string ValueToString(const double value) const;


	/* Functions */
	std::map<std::string, Func> m_existingFunctions;
	std::map<char, Operation> m_operationByChar;

	bool IsFunctionExist(const std::string& name) const;
	std::optional<CCalculator::Operation> GetOperationByChar(const char request) const;

	std::optional<double> CalculateFunction(const std::string& name) const;
};
