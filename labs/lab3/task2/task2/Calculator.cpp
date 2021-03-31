#include "stdafx.h"
#include "Calculator.h"

using namespace std;

const int MAX_PRECISION = 2;

/* Public methods*/
CCalculator::CCalculator()
	: m_operationByChar{ 
		{ '+', CCalculator::Operation::ADD },
		{ '-', CCalculator::Operation::SUBTRACT },
		{ '*', CCalculator::Operation::MULTIPLICATION },
		{ '/', CCalculator::Operation::DIVISION },
	}
{
}

CCalculator::~CCalculator()
{
}



/* Variables */

bool CCalculator::DeclareVariable(const string& variableName)
{
	if (!IsVariableUse(variableName) && !variableName.empty())
	{
		m_usedVariables.insert(make_pair(variableName, NAN));
		return true;
	}
	return false;
}

bool CCalculator::InitializeVariable(const std::string& variableName, const std::string& value)
{
	if (value.empty())
		return false;

	double variableValue = ConvertVariableValue(value);
	if (IsVariableUse(variableName))
	{
		return UpdateVariable(variableName, variableValue);
	}
	m_usedVariables.insert(make_pair(variableName, variableValue));

	return true;
}

double CCalculator::GetVariableValue(const string& variableName) const
{
	auto it = m_usedVariables.find(variableName);
	if (it != m_usedVariables.end())
	{
		return it->second;
	}
	return NAN;
}

string CCalculator::GetVariables() const 
{
	string res;
	for (auto& variable : m_usedVariables)
	{
		res += (variable.first + ":" + ValueToString(variable.second, MAX_PRECISION) + "\n");
	}
	return res;
};

/* Functions */

bool CCalculator::InitializeFunction(const std::string& first, const std::string& operation, const std::string& second)
{
}



/* Private methods */


/* Variables */
bool CCalculator::IsVariableUse(const string& variable) const 
{
	auto it = m_usedVariables.find(variable);
	return it != m_usedVariables.end();
}

bool CCalculator::UpdateVariable(const string& variableName, const double variableValue)
{
	try
	{
		m_usedVariables.at(variableName) = variableValue;
		return true;
	}
	catch (const out_of_range&)
	{
		return false;
	}
}

double CCalculator::ConvertVariableValue(const string& value) const
{
	try
	{
		return boost::lexical_cast<double>(value);
	}
	catch (const bad_cast&)
	{
		return IsVariableUse(value) ? GetVariableValue(value) : NAN;
	}
}

string CCalculator::ValueToString(const double value, const int precision) const
{
	ostringstream stream;
	stream << fixed << setprecision(precision) << value;
	return stream.str();
}



/* Functions */

optional<CCalculator::Operation> CCalculator::GetOperation(const char request) const
{
	try
	{
		return m_operationByChar.at(request);
	}
	catch (const out_of_range&)
	{
		return nullopt;
	}
}