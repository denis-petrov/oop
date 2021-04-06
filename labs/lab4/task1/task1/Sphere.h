#pragma once
#include "SolidBody.h"

class CSphere : public CSolidBody
{
public:
	CSphere(const double radius, const double density = DEFAULT_DENSITY);

	double GetVolume() const override final;
	double GetRadius() const;

	std::string ToString() const override;

private:
	double m_radius;
};
