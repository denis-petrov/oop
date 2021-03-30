#include "stdafx.h"
#include "Calculator.h"

using namespace std;

/* Public methods*/
CCalculator::CCalculator()
{
}

CCalculator::~CCalculator()
{
}

bool CCalculator::DeclareVariable(const string& variableName) 
{
	if (!IsVariableUse(variableName) && !variableName.empty())
	{
		Variable variable{ false, NAN };
		m_usedVariables.insert(make_pair(variableName, variable));
		return true;
	}
	return false;
}

bool CCalculator::InitializeVariable(const std::string& variableName, const std::string& identifier)
{
	if (IsVariableUse(variableName) || identifier.empty())
		return false;

	Variable variable{ false, NAN };
	try
	{
		double value = boost::lexical_cast<double>(identifier);
		variable.argument = value;
	}
	catch (const bad_cast&)
	{
		if (!IsVariableUse(identifier))
			DeclareVariable(identifier);

		variable.isPointer = true;
		variable.pointer = identifier;
	}

	m_usedVariables.insert(make_pair(variableName, variable));
	return true;
}


/* Private methods */
bool CCalculator::IsVariableUse(const string& variable) const 
{
	auto it = m_usedVariables.find(variable);
	if (it != m_usedVariables.end())
	{
		return true;
	}
	return false;
}