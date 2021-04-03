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

/* print <name> */
string CCalculator::GetEntityValue(const string& name) const
{
	if (IsVariableExist(name))
	{
		auto val = GetVariableValue(name);
		if (val.has_value())
		{
			return ValueToString(val.value());
		}
	}

	if (IsFunctionExist(name))
	{
		try
		{
			return ValueToString(CalculateFunction(name));
		}
		catch (const exception& e)
		{
			throw e;
		}
	}

	throw runtime_error(name + " does not exist");
}

/*printvars*/
string CCalculator::GetVariables() const
{
	string res;
	for (auto& variable : m_existingVariables)
	{
		res += (variable.first + ":" + GetEntityValue(variable.first) + "\n");
	}
	return res;
}

/* printfns */
string CCalculator::GetFunctions() const
{
	string res;
	for (auto& function : m_existingFunctions)
	{
		res += (function.first + ":" + GetEntityValue(function.first) + "\n");
	}
	return res;
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

	try
	{
		auto calculatedNodes = GetEmptyVisitedNodes();
		return ExecuteSequenceCalculate(name, calculatedNodes);
	}
	catch (const exception& e)
	{
		throw e;
	}
}

double CCalculator::ExecuteSequenceCalculate(const string& startName, map<string, optional<double>>& calculatedNodes) const
{
	stack<string> st;
	st.push(startName);

	while (!st.empty())
	{
		string currName = st.top();
		if (calculatedNodes.at(currName).has_value())
		{
			st.pop();
			continue;
		}

		optional<double> tempRes;
		if (IsFunctionExist(currName))
		{
			auto currFunc = m_existingFunctions.at(currName);
			
			auto firstVal = calculatedNodes.at(currFunc.first);
			if (!firstVal.has_value())
			{
				st.push(currFunc.first);
			}

			if (currFunc.action.has_value())
			{
				auto secondVal = calculatedNodes.at(currFunc.second.value());
				if (!secondVal.has_value())
				{
					st.push(currFunc.second.value());
				}

				if (firstVal.has_value() && secondVal.has_value())
				{
					tempRes = optional(HandleAction(firstVal.value(), currFunc.action.value(), secondVal.value()));
				}
			}
			else if(firstVal.has_value())
			{
				tempRes = firstVal;
			}
		}
		else if (IsVariableExist(currName))
		{
			tempRes = GetVariableValue(currName);
		}

		if (tempRes.has_value())
		{
			if (isnan(tempRes.value()))
				return NAN;

			calculatedNodes.at(currName) = tempRes.value();
			st.pop();
		}
	}

	auto res = calculatedNodes.at(startName);
	if (res.has_value())
	{
		return res.value();
	}
	return NAN;
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
	throw runtime_error("Not correct action: " + action);
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
		if (second == 0)
		{
			throw invalid_argument("Division by 0");
		}
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
