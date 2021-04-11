#include "Cone.h"

using namespace std;

CCone::CCone(const double baseRadius, const double height, const double density)
	: CSolidBody(density)
	, m_baseRadius(baseRadius)
	, m_height(height)
{
	if (!(m_baseRadius > MIN_PARAM && m_height > MIN_PARAM))
	{
		throw invalid_argument("Not correct parameters for Cone.");
	}
}

double CCone::GetVolume() const 
{
	return (1.0 / 3.0) * M_PI * pow(GetBaseRadius(), 2) * GetHeight();
}

double CCone::GetBaseRadius() const 
{
	return m_baseRadius;
}

double CCone::GetHeight() const
{
	return m_height;
}

string CCone::ToString(const int padding) const 
{
	stringstream stream;
	stream << "{ Cone }" << endl
		   << string("\t", padding) << "Base Radius = " << GetBaseRadius() << endl
		   << string("\t", padding) << "Height = " << GetHeight() << endl
		   << CSolidBody::ToString(padding) << endl;
	return stream.str();
}