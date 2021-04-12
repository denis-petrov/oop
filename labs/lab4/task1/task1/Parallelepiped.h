#pragma once
#include "SolidBody.h" 

class CParallelepiped : public CSolidBody
{
public:
	CParallelepiped(const double width, const double height, const double depth, const double density);
	virtual ~CParallelepiped(){};

	double GetVolume() const override;
	double GetWidth() const;
	double GetHeight() const;
	double GetDepth() const;

	std::string ToString(const int padding = PADDING) const override final;

private:
	double m_width;
	double m_height;
	double m_depth;
};
