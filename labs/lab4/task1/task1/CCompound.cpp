#include "Compound.h"

using namespace std;

bool CCompound::AddChildBody(const shared_ptr<CBody>& child)
{
	m_children.push_back(child);
	return true;
}

shared_ptr<CBody> CCompound::GetChildById(const int id) const
{
	try
	{
		return m_children.at(id);
	}
	catch (const exception&)
	{
		return nullptr;
	}
}

int CCompound::GetId() const
{
	return m_id;
}

void CCompound::SetId(const int id) 
{
	m_id = id;
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

string CCompound::ToString(const int padding) const
{
	stringstream stream;
	stream << "{ Compound }" << endl
		   << string("\t", padding) << "Size = " << m_children.size() << endl
		   << fixed << setprecision(3)
		   << string("\t", padding) << "Compound mass = " << GetMass() << endl
		   << string("\t", padding) << "Compound volume = " << GetVolume() << endl
		   << string("\t", padding) << "Compound density = " << GetDensity() << endl
		   << endl
		   << string("\t", padding) << "Contains elements: " << endl
		   << accumulate(m_children.begin(), m_children.end(), string(), [padding](string& sum, const shared_ptr<CBody>& elem) mutable {
				  return sum + string("\t", padding) + "ID = " + to_string(elem->GetId()) + "; " + elem->ToString(padding + 1);
			  });
	return stream.str();
}
