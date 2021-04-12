#pragma once
#include "Body.h"

class CCompound : public CBody
{
public:
	bool AddChildBody(const std::shared_ptr<CBody>& child);
	std::shared_ptr<CBody> GetChildById(const int id) const;

	int GetId() const override final;
	void SetId(const int id) override final;

	double GetVolume() const override final;
	double GetMass() const override final;
	double GetDensity() const override final;
	std::string ToString(const int padding = PADDING) const override final;

private:
	int m_id;
	std::vector<std::shared_ptr<CBody>> m_children;
};
