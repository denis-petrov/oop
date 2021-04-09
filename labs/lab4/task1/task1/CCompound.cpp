#include "Compound.h"

using namespace std;

double CCompound::GetVolume() const
{
	return accumulate(m_children.begin(), m_children.end(), 0.0, [](double sum, const shared_ptr<CBody>& elem) {
		return sum + elem->GetVolume();
	});
}

double CCompound::GetMass() const
{
	return accumulate(m_children.begin(), m_children.end(), 0.0, [](double sum, const shared_ptr<CBody>& elem) {
		return sum + elem->GetMass();
	});
}

double CCompound::GetDensity() const
{
	return GetMass() / GetVolume();
}

string CCompound::ToString() const
{
	stringstream stream;
	stream << "{ Compound }" << endl
		   << "\tSize = " << m_children.size() << endl
		   << fixed << setprecision(3)
		   << "\tCompound mass = " << GetMass() << endl
		   << "\tCompound volume = " << GetVolume() << endl
		   << "\tCompound density = " << GetDensity() << endl
		   << endl
		   << "\tContains elements: " << endl
		   << "\t" << accumulate(m_children.begin(), m_children.end(), string(), [](string& sum, const shared_ptr<CBody>& elem) {
				  return sum + elem->ToString();
			  });
	return stream.str();
}
