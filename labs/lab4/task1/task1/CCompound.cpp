#include "Compound.h"

using namespace std;

bool CCompound::AddChildBody(const shared_ptr<CBody>& child)
{
	if (GetChildById(child->GetId()) == nullptr)
	{
		m_children.push_back(child);
		return true;
	}
	return false;
}

shared_ptr<CBody> CCompound::GetChildById(const int id) const
{
	for (auto& child : m_children)
		if (child->GetId() == id)
			return child;
	return nullptr;
}


optional<shared_ptr<CCompound>> CCompound::GetNestedCompound(const vector<int>& elemIds, vector<shared_ptr<CCompound>>& usedNodes) const
{
	shared_ptr<CCompound> nestedElem;
	for (size_t i = 0; i < elemIds.size(); i++)
	{
		auto temp = (i == 0) ? GetChildById(elemIds[i]) : nestedElem->GetChildById(elemIds[i]);
		if (temp == nullptr)
			return nullptr;
		nestedElem = static_pointer_cast<CCompound>(temp);
		usedNodes.push_back(nestedElem);
	}
	return nestedElem;
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
