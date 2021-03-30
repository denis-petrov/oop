#pragma once
#include "stdafx.h"

class CCalculator
{
public:
	CCalculator();
	~CCalculator();

	bool DeclareVariable(const std::string& variableName);
	bool InitializeVariable(const std::string& variableName, const std::string& identifier);

	struct Variable
	{
		bool isPointer;
		double argument;
		std::string pointer;
	};

private:
	std::map<std::string, Variable> m_usedVariables;

	bool IsVariableUse(const std::string& variable) const;
};
