#include "stdafx.h"
#include "RemoteControl.h"
#include "Calculator.h"

using namespace std;

const string HELP_FILE_NAME = "help.txt";
const string HELP = "help";
const string VAR = "var";
const string LET = "let";
const string FN = "fn";
const string PRINT = "print";
const string PRINTVARS = "printvars";
const string PRINTFNS = "printfns";
const string END = "end";

const char ADD = '+';
const char SUBTRACT = '-';
const char MULTIPLICATION = '*';
const char DIVISION = '/';

const regex ONE_IDENTIFIER_REGEX("(\\s+)(\\w+)=(\\w+)");
const regex FULL_FUNCTION_REGEX("(\\s+)(\\w+)=(\\w+)+(\\+|\\-|\\*|/)+(\\w+)");

CRemoteControl::CRemoteControl(CCalculator& calculator, std::istream& input, std::ostream& output)
	: m_calculator(calculator)
	, m_input(input)
	, m_output(output)
	, m_isEndInput(false)
	, m_actionMap({
		  { HELP, bind(&CRemoteControl::Help, this) },
		  { VAR, bind(&CRemoteControl::Var, this) },
		  { LET, bind(&CRemoteControl::Let, this) },
		  { FN, bind(&CRemoteControl::Fn, this) },
		  { PRINT, bind(&CRemoteControl::Print, this) },
		  { PRINTVARS, bind(&CRemoteControl::PrintVars, this) },
		  { PRINTFNS, bind(&CRemoteControl::PrintFns, this) },
		  { END, bind(&CRemoteControl::End, this) },
	  })
{
}

bool CRemoteControl::HandleCommand()
{
	string action;
	if (!(m_input >> action))
	{
		return false;
	}

	m_isEndInput = (action == "end") ? true : false;

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		it->second();
		return true;
	}

	return false;
}

bool CRemoteControl::IsEndInput() const
{
	return m_isEndInput;
}

void CRemoteControl::Help()
{
	ifstream source(HELP_FILE_NAME);

	istreambuf_iterator<char> beginSource(source);
	istreambuf_iterator<char> endSource;
	ostreambuf_iterator<char> beginDest(m_output);
	copy(beginSource, endSource, beginDest);

	m_output << "\n\n";
}

void CRemoteControl::Var()
{
	string argument;
	if (!(m_input >> argument))
	{
		cout << "Not correct input.\nUse: var <identificator>";
	}

	if (m_calculator.DeclareVariable(argument))
	{
		cout << "Variable: " << argument << " has been declared";
	}
	else
	{
		cout << "Was error while declaring variable: " << argument;
	}
	cout << "\n\n";
}

void CRemoteControl::Let()
{
	string search;
	if (!(getline(m_input, search)))
	{
		cout << "Not correct input.\nUse: let <identificator1>=<number> OR let <identificator1>=<identificator2>";
	}
	string identifier, value;

	smatch matches;
	if (regex_match(search, matches, ONE_IDENTIFIER_REGEX))
	{
		identifier = matches[2].str();
		value = matches[3].str();
	}
	else
	{
		cout << "Not correct input.\nUse: let <identificator>=<number>";
	}

	if (m_calculator.InitializeVariable(identifier, value))
	{
		cout << "Variable: " << identifier << " has been declared by: " << value;
	}
	else
	{
		cout << "Was error while declaring variable: " << identifier;
	}
	cout << "\n\n";
}

void CRemoteControl::Fn()
{
	string search;
	if (!(getline(m_input, search)))
	{
		cout << "Not correct input.\nUse: fn <identificator1>=<identificator2>"
			 << "OR fn <identificator1>=<identificator2><operation><identificator3>";
	}
	string identifier, first, operation, second;

	smatch matches;
	if (regex_match(search, matches, FULL_FUNCTION_REGEX))
	{
		identifier = matches[2].str();
		first = matches[3].str();
		operation = matches[4].str();
		second = matches[5].str();

		if (m_calculator.InitializeFunction(identifier, first, operation[0], second))
		{
			cout << "Function: " << identifier << " has been declared by: " << first << operation << second;
		}
	}
	else if (regex_match(search, matches, ONE_IDENTIFIER_REGEX) && !IsFullFunction(search))
	{
		identifier = matches[2].str();
		first = matches[3].str();

		if (m_calculator.InitializeFunction(identifier, first))
		{
			cout << "Function: " << identifier << " has been declared by: " << first;
		}
	}
	else
	{
		cout << "Not correct input.\nUse: let <identificator>=<number>";
	}

	cout << "\n\n";
}

void CRemoteControl::Print()
{
	string identificator;
	if (!(m_input >> identificator))
	{
		cout << "Not correct input.\nUse: print <identificator>";
	}
	cout << m_calculator.GetEntityValue(identificator) << "\n";
}

void CRemoteControl::PrintVars()
{
	cout << m_calculator.GetVariables() << "\n";
}

void CRemoteControl::PrintFns()
{
	cout << m_calculator.GetFunctions() << "\n";
}

void CRemoteControl::End()
{
	m_output << "Goodbye.\n\n";
}

bool IsFullFunction(const string& s)
{
	return (s.find(ADD) != string::npos) || (s.find(SUBTRACT) != string::npos) 
		|| (s.find(MULTIPLICATION) != string::npos) || (s.find(DIVISION) != string::npos);
}