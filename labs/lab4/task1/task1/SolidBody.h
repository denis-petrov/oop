#pragma once
#include "Body.h"

class CSolidBody : public CBody
{
public:
	CSolidBody(const double density = DEFAULT_DENSITY);
	virtual ~CSolidBody(){};

	double GetMass() const override final;
	double GetDensity() const override final;
	std::string ToString() const override;

private:
	double m_density;
};
