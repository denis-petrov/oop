#include "Sphere.h"

using namespace std;

CSphere::CSphere(const double radius, const double density)
	: CSolidBody(density)
	, m_radius(radius)
{
	if (!(radius > MIN_PARAM))
	{
		throw invalid_argument("Radius must be greater than or equal to " + MIN_PARAM);
	}
}

double CSphere::GetVolume() const
{
	return (4.0 / 3.0) * M_PI * pow(m_radius, 3);
}

double CSphere::GetRadius() const
{
	return m_radius;
}

string CSphere::ToString() const
{
	stringstream stream;
	stream << "{ Sphere }\n"
		   << "\tRadius = " << GetRadius() << endl
		   << CSolidBody::ToString() << endl;
	return stream.str();
}
