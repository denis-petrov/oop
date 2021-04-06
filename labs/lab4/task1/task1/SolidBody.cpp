#include "SolidBody.h"

using namespace std;

CSolidBody::CSolidBody(const double density)
	: m_density(density)
{
	if (m_density < DEFAULT_DENSITY)
	{
		throw invalid_argument("Density must be greater than or equal to " + DEFAULT_DENSITY);
	}
}

double CSolidBody::GetMass() const
{
	return GetVolume() * m_density;
}

double CSolidBody::GetDensity() const
{
	return m_density;
}

string CSolidBody::ToString() const
{
	stringstream stream;
	stream << fixed << setprecision(DEFAULT_PRECISION);

	stream << "Density: " << GetDensity()
		   << "\nVolume: " << GetVolume()
		   << "\nMass: " << GetMass() << "\n";
	return stream.str();
}
