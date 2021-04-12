#pragma once
#include "stdafx.h"
#include "Body.h"
#include "Compound.h"
#include <boost/core/noncopyable.hpp>

class CBodiesControl : boost::noncopyable
{
public:
	CBodiesControl(std::istream& input, std::ostream& output);
	bool HandleCommand();
	bool IsEndInput() const;

private:
	void Help();
	void AddBody();
	void UpdateCompound();
	void PrintMostMassiveBody();
	void PrintLightestBodyInWater();
	void PrintAll();
	void End();

private:
	bool AddSphere();
	bool AddParallelepiped();
	bool AddCone();
	bool AddCylinder();
	bool AddCompound();

private:
	using HandlerCommand = std::function<void()>;
	using ActionMap = std::map<std::string, HandlerCommand>;
	const ActionMap m_actionMap;

	using HandlerBody = std::function<bool()>;
	using ActionBody = std::map<std::string, HandlerBody>;
	const ActionBody m_addBodyMap;

	std::vector<std::shared_ptr<CBody>> m_bodies;
	int m_lastIndex = 0;
	std::optional<std::shared_ptr<CBody>> GetBodyById(const int id) const;
	std::shared_ptr<CCompound> GetCompoudBodyByStringId(const std::string& appendIdStr, std::vector<std::shared_ptr<CCompound>>& usedNode) const;
	bool IsBodyByIdExist(const int id) const;
	void RemoveBodyById(const int id);

	std::istream& m_input;
	std::ostream& m_output;

	bool m_isEndInput;
};
