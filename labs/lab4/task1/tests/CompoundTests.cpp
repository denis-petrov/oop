#include "stdafx.h"

#define _USE_MATH_DEFINES
#include "../task1/Compound.h"
#include "../task1/Sphere.h"
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
	
	BOOST_AUTO_TEST_CASE(able_add_one_element_is_sphere) 
	{
		CSphere sphere(1, 7);
		BOOST_CHECK(compound.AddChildBody(sphere));

		BOOST_CHECK(compound.GetMass() == sphere.GetMass());
		BOOST_CHECK(compound.GetDensity() == sphere.GetDensity());
		BOOST_CHECK(compound.GetVolume() == sphere.GetVolume());
		std::cout << compound.ToString();
		
		const auto expectdString = R"({ Compound }
	Size = 1
	Compound mass = 29.322
	Compound volume = 4.189
	Compound density = 7.000

	Contains elements:
  )" + sphere.ToString();

	std::cout << expectdString;
		std::cout << std::to_string(compound.ToString() == expectdString);
	BOOST_CHECK(compound.ToString() == expectdString);
	}


BOOST_AUTO_TEST_SUITE_END()