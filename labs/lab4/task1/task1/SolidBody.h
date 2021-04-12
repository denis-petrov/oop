#pragma once
#include "Body.h"

class CSolidBody : public CBody
{
public:
	CSolidBody(const double density = DEFAULT_DENSITY);
	virtual ~CSolidBody(){};

	double GetMass() const override;
	double GetDensity() const override;
	std::string ToString(const int padding = PADDING) const override;

	int GetId() const override final;
	void SetId(const int id) override final;

private:
	double m_density;
	int m_id;
};
