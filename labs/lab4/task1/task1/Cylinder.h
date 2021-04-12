#pragma once
#include "SolidBody.h"

class CCylinder : public CSolidBody
{
public:
	CCylinder(const double baseRadius, const double height, const double density);
	virtual ~CCylinder(){};

	double GetVolume() const override;
	double GetBaseRadius() const;
	double GetHeight() const;

	std::string ToString(const int padding = PADDING) const override final;

private:
	double m_baseRadius;
	double m_height;
};
