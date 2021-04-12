#include "BodiesControlHandler.h"
#include "BodiesControl.h"
#include "Compound.h"
#include "Cone.h"
#include "Cylinder.h"
#include "Parallelepiped.h"
#include "Sphere.h"

using namespace std;

CBodiesControl::CBodiesControl(std::istream& input, std::ostream& output)
	: m_input(input)
	, m_output(output)
	, m_isEndInput(false)
	, m_actionMap({
		  { HELP, bind(&CBodiesControl::Help, this) },
		  { ADD, bind(&CBodiesControl::AddBody, this) },
		  { UPDATE_COMPOUND, bind(&CBodiesControl::UpdateCompound, this) },
		  { PRINT_MOST_MASSIVE, bind(&CBodiesControl::PrintMostMassiveBody, this) },
		  { PRINT_LIGHTEST_IN_WATER, bind(&CBodiesControl::PrintLightestBodyInWater, this) },
		  { PRINT_ALL, bind(&CBodiesControl::PrintAll, this) },
		  { END, bind(&CBodiesControl::End, this) },
	  })
	, m_addBodyMap({
		  { SPHERE, bind(&CBodiesControl::AddSphere, this) },
		  { PARALLELEPIPED, bind(&CBodiesControl::AddParallelepiped, this) },
		  { CONE, bind(&CBodiesControl::AddCone, this) },
		  { CYLINDER, bind(&CBodiesControl::AddCylinder, this) },
		  { COMPOUND, bind(&CBodiesControl::AddCompound, this) },
	  })
{
}

bool CBodiesControl::HandleCommand()
{
	string action;
	if (!(m_input >> action))
	{
		return false;
	}

	m_isEndInput = (action == END) ? true : false;

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		it->second();
		return true;
	}

	return false;
}

bool CBodiesControl::IsEndInput() const
{
	return m_isEndInput;
}

void CBodiesControl::Help()
{
	ifstream source(HELP_FILE_NAME);

	istreambuf_iterator<char> beginSource(source);
	istreambuf_iterator<char> endSource;
	ostreambuf_iterator<char> beginDest(m_output);
	copy(beginSource, endSource, beginDest);

	m_output << "\n\n";
}

void CBodiesControl::AddBody()
{
	string bodyName;
	m_input >> bodyName;

	auto it = m_addBodyMap.find(bodyName);
	if (it != m_addBodyMap.end())
	{
		m_output << bodyName;
		if (it->second())
			m_output << " was added with ID = " << m_lastIndex - 1;
		else
			m_output << " was not added";
	}

	m_output << "\n\n";
}

optional<double> CastToDouble(const string& value)
{
	try
	{
		return boost::lexical_cast<double>(value);
	}
	catch (const bad_cast&)
	{
		return nullopt;
	}
}

optional<int> CastToInt(const string& value)
{
	try
	{
		return boost::lexical_cast<int>(value);
	}
	catch (const bad_cast&)
	{
		return nullopt;
	}
}

void CBodiesControl::PrintMostMassiveBody()
{
	shared_ptr<CBody> mostMassiveBody = nullptr;
	int id = 0;
	for (auto& elem : m_bodies)
	{
		if (mostMassiveBody == nullptr || mostMassiveBody->GetMass() < elem->GetMass())
		{
			mostMassiveBody = elem;
			id = elem->GetId();
		}
	}

	m_output << "The most massive Body is:";
	if (mostMassiveBody != nullptr)
		m_output << "\nID = " << to_string(id) << "; " << mostMassiveBody->ToString();
	else
		m_output << " No one Body.\n\n";
}

double GetWeightInWater(const shared_ptr<CBody>& elem)
{
	return GRAVITY * (elem->GetMass() - WATER_DENSITY * elem->GetVolume());
}

void CBodiesControl::PrintLightestBodyInWater()
{
	shared_ptr<CBody> lightestBodyInWater = nullptr;
	int id = 0;
	for (auto& elem : m_bodies)
	{
		if (lightestBodyInWater == nullptr || GetWeightInWater(lightestBodyInWater) < GetWeightInWater(elem))
		{
			lightestBodyInWater = elem;
			id = elem->GetId();
		}
	}

	m_output << "The lightest Body in water is:";
	if (lightestBodyInWater != nullptr)
		m_output << "\nID = " << to_string(id) << "; " << lightestBodyInWater->ToString();
	else
		m_output << " No one Body.\n\n";
}

void CBodiesControl::PrintAll()
{
	if (m_bodies.empty())
		m_output << "All Bodies: No one Body.\n\n";
	else
		m_output << "\nAll Bodies: \n";

	for (auto& elem : m_bodies)
	{
		m_output << "ID = " << to_string(elem->GetId()) << "; " << elem->ToString();
	}
}

void CBodiesControl::End()
{
	m_output << "\n----RESULT----\n";
	PrintAll();
	PrintMostMassiveBody();
	PrintLightestBodyInWater();
	m_output << "Goodbye.\n\n";
}

bool CBodiesControl::AddSphere()
{
	string search;
	if (!(getline(m_input, search)))
	{
		cout << "Not correct input.";
		return false;
	}

	smatch matches;
	if (regex_match(search, matches, ADD_SPHERE_REGEX))
	{
		auto radius = CastToDouble(matches[2].str());
		auto density = CastToDouble(matches[4].str());

		try
		{
			auto newElem = make_shared<CSphere>(radius.value(), density.value());
			newElem->SetId(m_lastIndex);
			m_bodies.push_back(newElem);
			m_lastIndex++;
			return true;
		}
		catch (const invalid_argument&)
		{
			return false;
		}
	}

	return false;
}

bool CBodiesControl::AddParallelepiped()
{
	string search;
	if (!(getline(m_input, search)))
	{
		cout << "Not correct input.";
		return false;
	}

	smatch matches;
	if (regex_match(search, matches, ADD_PARALLELEPIPED_REGEX))
	{
		auto width = CastToDouble(matches[2].str());
		auto height = CastToDouble(matches[4].str());
		auto depth = CastToDouble(matches[6].str());
		auto density = CastToDouble(matches[8].str());

		try
		{
			auto newElem = make_shared<CParallelepiped>(width.value(), height.value(), depth.value(), density.value());
			newElem->SetId(m_lastIndex);
			m_bodies.push_back(newElem);
			m_lastIndex++;
			return true;
		}
		catch (const invalid_argument&)
		{
			return false;
		}
	}
	return false;
}

bool CBodiesControl::AddCone()
{
	string search;
	if (!(getline(m_input, search)))
	{
		cout << "Not correct input.";
		return false;
	}

	smatch matches;
	if (regex_match(search, matches, ADD_CONE_REGEX))
	{
		auto baseRadius = CastToDouble(matches[2].str());
		auto height = CastToDouble(matches[4].str());
		auto density = CastToDouble(matches[6].str());

		try
		{
			auto newElem = make_shared<CCone>(baseRadius.value(), height.value(), density.value());
			newElem->SetId(m_lastIndex);
			m_bodies.push_back(newElem);
			m_lastIndex++;
			return true;
		}
		catch (const invalid_argument&)
		{
			return false;
		}
	}
	return false;
}

bool CBodiesControl::AddCylinder()
{
	string search;
	if (!(getline(m_input, search)))
	{
		cout << "Not correct input.";
		return false;
	}

	smatch matches;
	if (regex_match(search, matches, ADD_CONE_REGEX))
	{
		auto baseRadius = CastToDouble(matches[2].str());
		auto height = CastToDouble(matches[4].str());
		auto density = CastToDouble(matches[6].str());

		try
		{
			auto newElem = make_shared<CCylinder>(baseRadius.value(), height.value(), density.value());
			newElem->SetId(m_lastIndex);
			m_bodies.push_back(newElem);
			m_lastIndex++;
			return true;
		}
		catch (const invalid_argument&)
		{
			return false;
		}
	}
	return false;
}

bool CBodiesControl::AddCompound()
{
	string search;
	if (!(getline(m_input, search)))
	{
		cout << "Not correct input.";
		return false;
	}

	CCompound compound;
	int coutElems = 0;

	auto begin = sregex_iterator(search.begin(), search.end(), ADD_COMPOUND_REGEX);
	auto end = sregex_iterator();
	for (sregex_iterator i = begin; i != end; ++i)
	{
		smatch match = *i;
		auto id = CastToInt(match[2]);
		if (id.has_value() && IsBodyExist(id.value()))
		{
			auto elemPair = GetBody(id.value());
			if (elemPair == nullptr)
				continue;

			compound.AddChildBody(elemPair);
			coutElems++;
			RemoveBody(id.value());
		}
	}

	if (coutElems != 0)
	{
		auto newElem = make_shared<CCompound>(compound);
		newElem->SetId(m_lastIndex);
		m_bodies.push_back(newElem);
		m_lastIndex++;
		return true;
	}
	return false;
}

shared_ptr<CCompound> CBodiesControl::GetNestedCompoudBody(const vector<string>& elemIds, vector<shared_ptr<CCompound>>& usedNodes) const
{
	auto id = CastToInt(elemIds[0]).value();
	auto firstBody = GetBody(id);
	if (firstBody == nullptr)
		return nullptr;

	shared_ptr<CCompound> nestedAppendElem = static_pointer_cast<CCompound>(firstBody);
	usedNodes.push_back(nestedAppendElem);

	bool isFirst = true;
	for (auto& elemId : elemIds)
	{
		if (isFirst)
		{
			isFirst = false;
			continue;
		}

		auto id = CastToInt(elemId).value();
		auto nestedElem = nestedAppendElem->GetChildById(id);
		if (nestedElem == nullptr)
			return nullptr;

		nestedAppendElem = static_pointer_cast<CCompound>(nestedElem);
		usedNodes.push_back(nestedAppendElem);
	}
	return nestedAppendElem;
}

pair<shared_ptr<CCompound>, vector<shared_ptr<CCompound>>> CBodiesControl::GetCompoundBody(const string& appendIdStr) const
{
	vector<shared_ptr<CCompound>> usedNodes;
	vector<string> elemIds;
	boost::split(elemIds, appendIdStr, boost::is_any_of("-"));

	shared_ptr<CCompound> appendBody;
	if (elemIds.size() > 1)
	{
		appendBody = GetNestedCompoudBody(elemIds, usedNodes);
	}
	else
	{
		appendBody = static_pointer_cast<CCompound>(GetBody(CastToInt(elemIds[0]).value()));
		usedNodes.push_back(appendBody);
	}
	return { appendBody, usedNodes };
}

void CBodiesControl::UpdateCompound()
{
	string search, appendIdStr;
	getline(m_input, search);

	optional<shared_ptr<CBody>> pushBody;

	smatch matches;
	if (regex_match(search, matches, UPDATE_COMPOUND_REGEX))
	{
		appendIdStr = matches[2].str();
		auto pushIdOpt = CastToInt(matches[6].str());
		if (!pushIdOpt.has_value())
		{
			m_output << "Not correct input.\n\n";
			return;
		}
		pushBody = GetBody(pushIdOpt.value());
	}
	else
	{
		m_output << "Not correct input.\n\n";
		return;
	}

	if (!pushBody.has_value())
	{
		m_output << "Not correct Push Body element.\n\n";
		return;
	}

	auto [appendBody, usedNodes] = GetCompoundBody(appendIdStr);

	auto cycleIterator = std::find_if(usedNodes.begin(), usedNodes.end(),
		[=](const shared_ptr<CCompound>& appendBody) { return appendBody == pushBody.value(); });

	if (appendBody != nullptr && cycleIterator == usedNodes.end())
	{
		appendBody->AddChildBody(pushBody.value());
		RemoveBody(pushBody.value()->GetId());

		m_output << "Update Compound Body was completed successfully.\n\n";
	}
	else
		m_output << "Not correct input or Found cycle of Bodies.\n\n";
}


shared_ptr<CBody> CBodiesControl::GetBody(const int id) const
{
	for (auto& elem : m_bodies)
	{
		if (elem->GetId() == id)
		{
			return elem;
		}
	}
	return nullptr;
}

bool CBodiesControl::IsBodyExist(const int id) const
{
	for (auto& elem : m_bodies)
	{
		if (elem->GetId() == id)
		{
			return true;
		}
	}
	return false;
}

void CBodiesControl::RemoveBody(const int id)
{
	m_bodies.erase(
		remove_if(
			m_bodies.begin(),
			m_bodies.end(),
			[id](const shared_ptr<CBody>& e) {
				return id == e->GetId();
			}),
		m_bodies.end());
}
