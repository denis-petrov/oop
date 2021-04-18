#include "Cylinder.h"

using namespace std;

CCylinder::CCylinder(const double baseRadius, const double height, const double density)
	: CSolidBody(density)
	, m_baseRadius(baseRadius)
	, m_height(height)
{
	if (!(m_baseRadius > MIN_PARAM && m_height > MIN_PARAM))
	{
		throw invalid_argument("Not correct parameters for Cylinder.");
	}
}

double CCylinder::GetVolume() const
{
	return M_PI * pow(GetBaseRadius(), 2) * GetHeight();
}

double CCylinder::GetBaseRadius() const
{
	return m_baseRadius;
}

double CCylinder::GetHeight() const
{
	return m_height;
}

string CCylinder::ToString(const int padding) const
{
	stringstream stream;
	stream << "{ Cylinder }" << endl
		   << string(padding, '\t') << "Base Radius = " << GetBaseRadius() << endl
		   << string(padding, '\t') << "Height = " << GetHeight() << endl
		   << CSolidBody::ToString(padding) << endl;
	return stream.str();
}
