#pragma once
#include <boost/core/noncopyable.hpp>

class CCar;

class CRemoteControl : boost::noncopyable
{
public:
	CRemoteControl(CCar& car, std::istream& input, std::ostream& output);
	bool HandleCommand();
	bool IsEndInput() const;

private:
	void Help();
	void Info();
	void EngineOn();
	void EngineOff();
	void SetSpeed();
	void SetGear();
	void End();

private:
	using Handler = std::function<void()>;

	using ActionMap = std::map<std::string, Handler>;

	CCar& m_car;

	std::istream& m_input;
	std::ostream& m_output;

	bool m_isEndInput;

	const ActionMap m_actionMap;
};
