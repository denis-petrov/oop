#pragma once
#include <boost/core/noncopyable.hpp>

class CCalculator;

class CRemoteControl : boost::noncopyable
{
public:
	CRemoteControl(CCalculator& calculator, std::istream& input, std::ostream& output);
	bool HandleCommand();
	bool IsEndInput() const;

private:
	void Help();
	void Var();
	void Let();
	void Fn();
	void Print();
	void PrintVars();
	void PrintFns();
	void End();

private:
	using Handler = std::function<void()>;

	using ActionMap = std::map<std::string, Handler>;

	CCalculator& m_calculator;

	std::istream& m_input;
	std::ostream& m_output;

	bool m_isEndInput;

	const ActionMap m_actionMap;
};
