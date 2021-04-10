#include "Compound.h"

using namespace std;

bool CCompound::AddChildBody(const std::shared_ptr<CBody> child)
{
	m_children.push_back(child);
	return true;
}

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
		   << accumulate(m_children.begin(), m_children.end(), string(), [index = 0](string& sum, const shared_ptr<CBody>& elem) mutable {
				  return sum + "\t(" + to_string(++index) + ") "+ elem->ToString();
			  });
	return stream.str();
}
