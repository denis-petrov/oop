#include "SolidBody.h"

using namespace std;

CSolidBody::CSolidBody(const double density)
	: m_density(density)
	, m_id(0)
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

string CSolidBody::ToString(const int padding) const
{
	stringstream stream;
	stream << string(padding, '\t') << "Density = " << GetDensity() << endl 
		   << fixed << setprecision(3)
		   << string(padding, '\t') << "Volume = " << GetVolume() << endl
		   << string(padding, '\t') << "Mass = " << GetMass() << endl;
	return stream.str();
}

int CSolidBody::GetId() const 
{
	return m_id;
}

void CSolidBody::SetId(const int id) 
{
	m_id = id;
}


