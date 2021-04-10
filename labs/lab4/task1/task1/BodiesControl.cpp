#include "stdafx.h"
#include "BodiesControl.h"
#include "Compound.h"
#include "Cone.h"
#include "Cylinder.h"
#include "Parallelepiped.h"
#include "Sphere.h"

using namespace std;

const string HELP_FILE_NAME = "help.txt";
const string HELP = "help";
const string ADD = "add";
const string MOST_MASSIVE_BODY = "mostMassiveBody";
const string LIGHTEST_BODY_IN_WATER = "lightestBodyInWater";
const string PRINT_ALL = "printAll";
const string END = "end";

const string SPHERE = "Sphere";
const regex ADD_SPHERE_REGEX("(\\s+)(\\d+)(\\s+)?(\\d+)?");

const string PARALLELEPIPED = "Parallelepiped";
const regex ADD_PARALLELEPIPED_REGEX("(\\s+)(\\d+)(\\s+)(\\d+)(\\s+)(\\d+)(\\s+)?(\\d+)?");

const string CONE = "Cone";
const regex ADD_CONE_REGEX("(\\s+)(\\d+)(\\s+)(\\d+)(\\s+)?(\\d+)?");

const string CYLINDER = "Cylinder";
const regex ADD_CYLINDER_REGEX("(\\s+)(\\d+)(\\s+)(\\d+)(\\s+)?(\\d+)?");

const string COMPOUND = "Compound";
const regex ADD_COMPOUND_REGEX("(\\s+)(\\d+)");

const int EMPTY = -1;

CBodiesControl::CBodiesControl(std::istream& input, std::ostream& output)
	: m_input(input)
	, m_output(output)
	, m_isEndInput(false)
	, m_actionMap({
		  { HELP, bind(&CBodiesControl::Help, this) },
		  { ADD, bind(&CBodiesControl::AddBody, this) },
		  { MOST_MASSIVE_BODY, bind(&CBodiesControl::GetMostMassiveBody, this) },
		  { LIGHTEST_BODY_IN_WATER, bind(&CBodiesControl::GetLightestBodyInWater, this) },
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

void CBodiesControl::GetMostMassiveBody()
{

	m_output << "\n\n";
}

void CBodiesControl::GetLightestBodyInWater()
{

	m_output << "\n\n";
}

void CBodiesControl::PrintAll()
{
	if (m_bodies.empty())
		m_output << "\nNo one Body.\n\n";
	else
		m_output << "\nAll Bodies: \n";
	
	for (auto& elem : m_bodies)
	{
		m_output << "ID = " << elem.first << "; " << elem.second->ToString();
	}
}


void CBodiesControl::End()
{
	PrintAll();

	m_output << "Goodbye.\n\n";
}

double CastToDouble(const string& value)
{
	try
	{
		return boost::lexical_cast<double>(value);
	}
	catch (const bad_cast&)
	{
		return NAN;
	}
}

int CastToInt(const string& value)
{
	try
	{
		return boost::lexical_cast<int>(value);
	}
	catch (const bad_cast&)
	{
		return EMPTY;
	}
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

		if (isnan(density))
			m_bodies.push_back(make_pair(m_lastIndex, make_shared<CSphere>(radius)));
		else
			m_bodies.push_back(make_pair(m_lastIndex, make_shared<CSphere>(radius, density)));

		m_lastIndex++;
		return true;
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

		if (isnan(density))
			m_bodies.push_back(make_pair(m_lastIndex, make_shared<CParallelepiped>(width, height, depth)));
		else
			m_bodies.push_back(make_pair(m_lastIndex, make_shared<CParallelepiped>(width, height, depth, density)));

		m_lastIndex++;
		return true;
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

		if (isnan(density))
			m_bodies.push_back(make_pair(m_lastIndex, make_shared<CCone>(baseRadius, height)));
		else
			m_bodies.push_back(make_pair(m_lastIndex, make_shared<CCone>(baseRadius, height, density)));

		m_lastIndex++;
		return true;
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

		if (isnan(density))
			m_bodies.push_back(make_pair(m_lastIndex, make_shared<CCylinder>(baseRadius, height)));
		else
			m_bodies.push_back(make_pair(m_lastIndex, make_shared<CCylinder>(baseRadius, height, density)));

		m_lastIndex++;
		return true;
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
	int matchCount = distance(begin, end);
	for (sregex_iterator i = begin; i != end; ++i)
	{
		smatch match = *i;
		int id = CastToInt(match[2]);
		if (id != EMPTY && IsBodyByIdExist(id))
		{
			auto elem = GetBodyById(id);
			if (!elem.has_value())
				continue;

			compound.AddChildBody(elem->second);
			coutElems++;
			RemoveBodyById(id);
		}
	}

	if (coutElems != 0)
	{
		m_bodies.push_back(make_pair(m_lastIndex, make_shared<CCompound>(compound)));
		m_lastIndex++;
		return true;
	}
	return false;
}

optional<pair<int, shared_ptr<CBody>>> CBodiesControl::GetBodyById(const int id) const
{
	for (auto& pair : m_bodies)
	{
		if (pair.first == id)
		{
			return pair;
		}
	}
	return nullopt;
}

bool CBodiesControl::IsBodyByIdExist(const int id) const 
{
	for (auto& pair : m_bodies)
	{
		if (pair.first == id)
		{
			return true;
		}
	}
	return false;
}

void CBodiesControl::RemoveBodyById(const int id)
{
	m_bodies.erase(
		remove_if(
			m_bodies.begin(),
			m_bodies.end(),
			[id](const pair<int, shared_ptr<CBody>>& e) {
				return id == e.first;
			}),
		m_bodies.end());
}
