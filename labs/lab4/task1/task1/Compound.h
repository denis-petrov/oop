#pragma once
#include "Body.h"

class CCompound : public CBody
{
public:
	bool AddChildBody(const std::shared_ptr<CBody> child);

	double GetVolume() const override final;
	double GetMass() const override final;
	double GetDensity() const override final;
	std::string ToString() const override final;

private:
	std::vector<std::shared_ptr<CBody>> m_children;
};
