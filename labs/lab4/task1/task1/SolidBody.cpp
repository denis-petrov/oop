#include "SolidBody.h"

using namespace std;

CSolidBody::CSolidBody(const double density)
	: m_density(density)
{
	if (!(m_density > MIN_PARAM))
	{
		throw invalid_argument("Density must be greater than or equal to " + MIN_PARAM);
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
	stream << "\tDensity = " << GetDensity() << endl 
		   << fixed << setprecision(3)
		   << "\tVolume = " << GetVolume() << endl
		   << "\tMass = " << GetMass() << endl;
	return stream.str();
}