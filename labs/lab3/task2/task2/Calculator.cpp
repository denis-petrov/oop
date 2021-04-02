#include "stdafx.h"
#include "Calculator.h"

using namespace std;

const int MAX_PRECISION = 2;
const char ADD = '+';
const char SUBTRACT = '-';
const char MULTIPLICATION = '*';
const char DIVISION = '/';

/* Public methods*/
CCalculator::CCalculator()
	: m_actionMap({
		{ ADD, [this](const double first, const double second) {
			 return CalculateSum(first, second);
		 } },
		{ SUBTRACT, [this](const double first, const double second) {
			 return CalculateSubtract(first, second);
		 } },
		{ MULTIPLICATION, [this](const double first, const double second) {
			 return CalculateMultiplication(first, second);
		 } },
		{ DIVISION, [this](const double first, const double second) {
			 return CalculateDivision(first, second);
		 } },
	})
{
}

CCalculator::~CCalculator()
{
}

optional<string> CCalculator::GetEntityValue(const string& name) const
{
	if (IsVariableExist(name))
	{
		auto val = GetVariableValue(name);
		if (val.has_value())
		{
			return ValueToString(val.value());
		}
	}

	/* TODO */
	//if (IsFunctionExist(name))
	//{
		/*auto val = GetVariableValue(name);
		return val.has_value() ? val.value() : "";*/
	//}

	return nullopt;
}



/* Variables */

bool CCalculator::DeclareVariable(const string& name)
{
	if (!IsVariableExist(name) && !IsFunctionExist(name) && !name.empty())
	{
		m_existingVariables.insert(make_pair(name, NAN));
		return true;
	}
	return false;
}

bool CCalculator::InitializeVariable(const string& name, const string& value)
{
	if (value.empty() || IsFunctionExist(name))
		return false;

	try
	{
		auto tempValue = GetVariableValue(value);
		double variableValue = tempValue.has_value() ? tempValue.value() : boost::lexical_cast<double>(value);

		if (IsVariableExist(name))
		{
			return UpdateVariable(name, variableValue);
		}
		m_existingVariables.insert(make_pair(name, variableValue));
		return true;
	}
	catch (const exception& e)
	{
		throw e;
	}
}

string CCalculator::GetVariables() const
{
	string res;
	for (auto& variable : m_existingVariables)
	{
		res += (variable.first + ":" + ValueToString(variable.second) + "\n");
	}
	return res;
};

/* Functions */

bool CCalculator::InitializeFunction(const string& name, const string& first)
{
	if (!IsShortFunctionCorrect(name, first))
	{
		return false;
	}
	Func curFunc{ first, nullopt, nullopt };
	m_existingFunctions.insert(make_pair(name, curFunc));

	return true;
}

bool CCalculator::InitializeFunction(const string& name, const string& first, const char operation, const string& second)
{
	if (!(IsActionCorrect(operation) && IsFullFunctionCorrect(name, first, second)))
	{
		return false;
	}

	Func curFunc{ first, operation, second };
	m_existingFunctions.insert(make_pair(name, curFunc));

	return true;
}

/* Private methods */

/* Variables */
bool CCalculator::IsVariableExist(const string& name) const
{
	auto it = m_existingVariables.find(name);
	return it != m_existingVariables.end();
}

bool CCalculator::UpdateVariable(const string& name, const double value)
{
	try
	{
		m_existingVariables.at(name) = value;
		return true;
	}
	catch (const out_of_range&)
	{
		return false;
	}
}

bool CCalculator::UpdateVariable(const string& name, const string& anotherVar)
{
	try
	{
		auto value = GetVariableValue(anotherVar);
		if (value.has_value())
		{
			m_existingVariables.at(name) = value.value();
			return true;
		}
		return false;
	}
	catch (const out_of_range&)
	{
		return false;
	}
}

optional<double> CCalculator::GetVariableValue(const string& name) const
{
	auto it = m_existingVariables.find(name);
	if (it != m_existingVariables.end())
	{
		return it->second;
	}
	return nullopt;
}

string CCalculator::ValueToString(const double value) const
{
	if (isnan(value))
	{
		return "nan";
	}

	ostringstream stream;
	stream << fixed << setprecision(MAX_PRECISION) << value;
	return stream.str();
}

/* Functions */

bool CCalculator::IsFunctionExist(const string& name) const
{
	auto it = m_existingFunctions.find(name);
	return it != m_existingFunctions.end();
}

bool CCalculator::IsShortFunctionCorrect(const string& name, const string& first) const
{
	return !IsFunctionExist(name) && !IsVariableExist(name) && (IsVariableExist(first) || IsFunctionExist(first));
}

bool CCalculator::IsFullFunctionCorrect(const string& name, const string& first, const string& second) const
{
	return !IsFunctionExist(name) && !IsVariableExist(name)
		&& (IsVariableExist(first) || IsFunctionExist(first))
		&& (IsVariableExist(second) || IsFunctionExist(second));
}

double CCalculator::CalculateFunction(const string& name) const
{
	if (!IsFunctionExist(name))
		throw runtime_error("Function: " + name + " does not exist");

	auto visitedNodes = GetEmptyVisitedNodes();
	try
	{
		return ExecuteSequenceCalculate(name, visitedNodes);
	}
	catch (const exception& e)
	{
		throw e;
	}
}

double CCalculator::ExecuteSequenceCalculate(const string& startName, map<string, optional<double>>& visitedNodes) const
{
	stack<string> st;
	st.push(startName);

	while (!st.empty())
	{
		string currName = st.top();
		if (visitedNodes.at(currName) != nullopt)
		{
			st.pop();
			continue;
		}

		auto currFunc = m_existingFunctions.at(currName);

		auto firstVal = visitedNodes.at(currFunc.first);
		if (firstVal == nullopt)
			st.push(currFunc.first);

		auto secondVal = visitedNodes.at(currFunc.second.value());
		try
		{
			double tempRes;
			if (currFunc.action.has_value()) 
			{
				if (secondVal == nullopt)
					st.push(currFunc.second.value());
				else
					tempRes = HandleAction(firstVal.value(), currFunc.action.value(), secondVal.value());
			}
			else
			{
				auto varValue = GetVariableValue(currName);
				if (isnan(varValue.value()))
					throw runtime_error("Met NaN in operand");

				tempRes = varValue.value();
			}
			visitedNodes.at(currName) = tempRes;
			st.pop();
		}
		catch (const exception& e)
		{
			throw e;
		}
	}

	return visitedNodes.at(startName).value();
}


map<string, optional<double>> CCalculator::GetEmptyVisitedNodes() const
{
	map<string, optional<double>> res;

	for (auto& value : m_existingVariables)
	{
		res.insert(make_pair(value.first, value.second));
	}

	for (auto& value : m_existingFunctions)
	{
		res.insert(make_pair(value.first, nullopt));
	}

	return res;
}

double CCalculator::HandleAction(const double first, const char action, const double second) const
{
	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		return it->second(first, second);
	}

	return NAN;
}

/* Operations */

double CCalculator::CalculateSum(const double first, const double second) const
{
	try
	{
		return first + second;
	}
	catch (const exception& e)
	{
		throw e;
	}
}

double CCalculator::CalculateSubtract(const double first, const double second) const
{
	try
	{
		return first - second;
	}
	catch (const exception& e)
	{
		throw e;
	}
}

double CCalculator::CalculateMultiplication(const double first, const double second) const
{
	try
	{
		return first * second;
	}
	catch (const exception& e)
	{
		throw e;
	}
}

double CCalculator::CalculateDivision(const double first, const double second) const
{
	try
	{
		return first / second;
	}
	catch (const exception& e)
	{
		throw e;
	}
}

bool CCalculator::IsActionCorrect(const char action) const
{
	return (action == ADD) || (action == SUBTRACT) || (action == MULTIPLICATION) || (action == DIVISION);
}
