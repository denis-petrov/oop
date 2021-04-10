#include "stdafx.h"

#define _USE_MATH_DEFINES
#include "../task1/Compound.h"
#include "../task1/Sphere.h"
#include "../task1/Parallelepiped.h"
#include <math.h>

struct Compound_
{
	CCompound compound;
};

BOOST_FIXTURE_TEST_SUITE(Compound, Compound_)

	BOOST_AUTO_TEST_CASE(is_a_body)
	{
		BOOST_CHECK(static_cast<const CBody*>(&compound));
	}
	
	BOOST_AUTO_TEST_CASE(able_add_one_element) 
	{
		CSphere sphere(1, 7);
		auto sharedSphere = std::make_shared<CSphere>(sphere);
		BOOST_CHECK(compound.AddChildBody(sharedSphere));
		BOOST_CHECK(compound.GetMass() == sphere.GetMass());
		BOOST_CHECK(compound.GetDensity() == sphere.GetDensity());
		BOOST_CHECK(compound.GetVolume() == sphere.GetVolume());

		std::stringstream stream;
		stream << "{ Compound }" << std::endl
			   << "\tSize = 1" << std::endl
			   << std::fixed << std::setprecision(3)
			   << "\tCompound mass = 29.322" << std::endl
			   << "\tCompound volume = 4.189" << std::endl
			   << "\tCompound density = 7.000" << std::endl
			   << std::endl
			   << "\tContains elements: " << std::endl
			   << "\t(1) " << sphere.ToString();
		
		BOOST_CHECK(compound.ToString() == stream.str());
	}

	BOOST_AUTO_TEST_CASE(able_add_two_elements)
	{
		CSphere sphere(1, 7);
		auto sharedSphere = std::make_shared<CSphere>(sphere);
		BOOST_CHECK(compound.AddChildBody(sharedSphere));
		BOOST_CHECK(compound.GetMass() == sphere.GetMass());
		BOOST_CHECK(compound.GetDensity() == sphere.GetDensity());
		BOOST_CHECK(compound.GetVolume() == sphere.GetVolume());

		CParallelepiped parallelepiped(1, 7, 8);
		auto sharedParallelepiped = std::make_shared<CParallelepiped>(parallelepiped);
		BOOST_CHECK(compound.AddChildBody(sharedParallelepiped));
		BOOST_CHECK(compound.GetMass() == (sphere.GetMass() + parallelepiped.GetMass()));
		BOOST_CHECK(compound.GetVolume() == (sphere.GetVolume() + parallelepiped.GetVolume()));
		BOOST_CHECK(compound.GetDensity() == (compound.GetMass() / compound.GetVolume()));

		std::stringstream stream;
		stream << "{ Compound }" << std::endl
			   << "\tSize = 2" << std::endl
			   << std::fixed << std::setprecision(3)
			   << "\tCompound mass = 85.322" << std::endl
			   << "\tCompound volume = 60.189" << std::endl
			   << "\tCompound density = 1.418" << std::endl
			   << std::endl
			   << "\tContains elements: " << std::endl
			   << "\t(1) " << sphere.ToString() 
			   << "\t(2) " << parallelepiped.ToString();

		BOOST_CHECK(compound.ToString() == stream.str());
	}

	BOOST_AUTO_TEST_CASE(able_add_compound_element)
	{
		CCompound compound2;

		CSphere sphere(1, 7);
		auto sharedSphere = std::make_shared<CSphere>(sphere);
		BOOST_CHECK(compound2.AddChildBody(sharedSphere));

		CParallelepiped parallelepiped(1, 7, 8);
		auto sharedParallelepiped = std::make_shared<CParallelepiped>(parallelepiped);
		BOOST_CHECK(compound2.AddChildBody(sharedParallelepiped));

		auto sharedComp = std::make_shared<CCompound>(compound2);
		BOOST_CHECK(compound.AddChildBody(sharedComp));

		std::stringstream stream;
		stream << "{ Compound }" << std::endl
			   << "\tSize = 1" << std::endl
			   << std::fixed << std::setprecision(3)
			   << "\tCompound mass = 85.322" << std::endl
			   << "\tCompound volume = 60.189" << std::endl
			   << "\tCompound density = 1.418" << std::endl
			   << std::endl
			   << "\tContains elements: " << std::endl
			   << "\t(1) " << compound2.ToString();

		BOOST_CHECK(compound.ToString() == stream.str());
	}

BOOST_AUTO_TEST_SUITE_END()