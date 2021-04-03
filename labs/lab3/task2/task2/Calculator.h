#pragma once
#include "stdafx.h"

class CCalculator
{
	struct Func
	{
		std::string first;
		std::optional<char> action;
		std::optional<std::string> second;
	};

public:
	CCalculator();
	~CCalculator();

	/* print <name> */
	std::string GetEntityValue(const std::string& name) const;
	/* printvars */
	std::string GetVariables() const;
	/* printfns */
	std::string GetFunctions() const;


	/* Variables */
	bool DeclareVariable(const std::string& name);
	bool InitializeVariable(const std::string& name, const std::string& identifier);

	/* Functions */
	bool InitializeFunction(const std::string& name, const std::string& first);
	bool InitializeFunction(const std::string& name, const std::string& first, const char action, const std::string& second);

private:
	/* Operation */
	using Handler = std::function<double(const double, const double)>;
	using ActionMap = std::map<char, Handler>;

	const ActionMap m_actionMap;

	double CalculateSum(const double first, const double second) const;
	double CalculateSubtract(const double first, const double second) const;
	double CalculateMultiplication(const double first, const double second) const;
	double CalculateDivision(const double first, const double second) const;

	double HandleAction(const double first, const char action, const double second) const;
	bool IsActionCorrect(const char action) const;


	/* Variables */
	std::map<std::string, double> m_existingVariables;

	bool IsVariableExist(const std::string& name) const;
	bool UpdateVariable(const std::string& name, const double value);
	bool UpdateVariable(const std::string& name, const std::string& anotherVar);

	std::optional<double> GetVariableValue(const std::string& name) const;
	std::string ValueToString(const double value) const;


	/* Functions */
	std::map<std::string, Func> m_existingFunctions;

	bool IsFunctionExist(const std::string& name) const;
	bool IsFullFunctionCorrect(const std::string& name, const std::string& first, const std::string& second) const;
	bool IsShortFunctionCorrect(const std::string& name, const std::string& first) const;



	/* Calcualtion */
	double CalculateFunction(const std::string& name) const;
	double ExecuteSequenceCalculate(const std::string& startName, std::map<std::string, std::optional<double>>& calculatedNodes) const;

	std::map<std::string, std::optional<double>> GetEmptyVisitedNodes() const;

};
