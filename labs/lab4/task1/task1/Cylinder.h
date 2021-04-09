#pragma once
#include "SolidBody.h"

class CCylinder : public CSolidBody
{
public:
	CCylinder(const double baseRadius, const double height, const double density = DEFAULT_DENSITY);
	virtual ~CCylinder(){};

	double GetVolume() const override;
	double GetBaseRadius() const;
	double GetHeight() const;

	std::string ToString() const override final;

private:
	double m_baseRadius;
	double m_height;
};
