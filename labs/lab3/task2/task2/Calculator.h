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

	struct Function
	{
		std::variant<double, std::string> first;
		Operation operation;
		std::variant<double, std::string> second;
	};

public:
	CCalculator();
	~CCalculator();

	/* Variables */
	bool DeclareVariable(const std::string& variableName);
	bool InitializeVariable(const std::string& variableName, const std::string& identifier);

	double GetVariableValue(const std::string& variableName) const;
	std::string GetVariables() const;


	/* Functions */
	bool InitializeFunction(const std::string& first, const std::string& operation, const std::string& second);

private:
	std::map<std::string, double> m_usedVariables;
	std::map<std::string, Function> m_usedFunctions;

	std::map<char, Operation> m_operationByChar;

	bool IsVariableUse(const std::string& variable) const;
	bool UpdateVariable(const std::string& variableName, const double variableValue);

	double ConvertVariableValue(const std::string& value) const;
	std::string ValueToString(const double value, const int precision) const;

	std::optional<CCalculator::Operation> GetOperation(const char request) const;
};
