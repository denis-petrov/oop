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

	if (IsFunctionExist(name))
	{
		/*auto val = GetVariableValue(name);
		return val.has_value() ? val.value() : "";*/
		/* TODO */
	}

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

bool CCalculator::InitializeVariable(const std::string& name, const std::string& value)
{
	if (value.empty() || IsFunctionExist(name))
		return false;

	auto variableValue = ConvertVariableValue(value);
	if (IsVariableExist(name))
	{
		return UpdateVariable(name, variableValue);
	}
	m_existingVariables.insert(make_pair(name, variableValue));

	return true;
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

bool CCalculator::InitializeFunction(const std::string& name, const std::string& first)
{
	if (IsFunctionExist(name) || !IsVariableExist(first) || IsVariableExist(name))
	{
		return false;
	}
	m_existingFunctions.insert(pair<string, Func>(name, { first }));

	return true;
}

bool CCalculator::InitializeFunction(const std::string& name, const std::string& first, const char operation, const std::string& second)
{
	auto action = GetOperationByChar(operation);

	if (IsFunctionExist(name) || IsVariableExist(name) || !IsVariableExist(first) || !IsVariableExist(second) || !action.has_value())
	{
		return false;
	}

	m_existingFunctions.insert(pair<string, Func>(name, { first, action.value(), second }));

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

double CCalculator::ConvertVariableValue(const string& value) const
{
	try
	{
		return boost::lexical_cast<double>(value);
	}
	catch (const bad_cast&)
	{
		if (IsVariableExist(value))
		{
			auto variableValue = GetVariableValue(value);
			return variableValue.has_value() ? variableValue.value() : NAN;
		}
		return NAN;
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

optional<CCalculator::Operation> CCalculator::GetOperationByChar(const char request) const
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

optional<double> CCalculator::CalculateFunction(const string& name) const
{
	if (!IsFunctionExist(name))
	{
		return nullopt;
	}
	
	auto func = m_existingFunctions.at(name);

	stack<Func> st;
	st.push(func);

	while (!st.empty())
	{
		Func currFunc = st.top();
		st.pop();

		// TODO
	}

	// TODO
	return NAN;
}