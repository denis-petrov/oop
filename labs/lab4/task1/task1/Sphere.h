#pragma once
#include "SolidBody.h"

class CSphere : public CSolidBody
{
public:
	CSphere(const double radius, const double density);
	virtual ~CSphere(){};

	double GetVolume() const override final;
	double GetRadius() const;

	std::string ToString(const int padding = PADDING) const override;

private:
	double m_radius;
};
