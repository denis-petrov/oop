#include "stdafx.h"

#define _USE_MATH_DEFINES
#include "../task1/Cylinder.h"
#include <math.h>

struct Cylinder_
{
	const double expectedBaseRadius = 12.2;
	const double expectedHeight = 4.4;
	const double expectedDensity = 2;
	const double expectedVolume = 2057.4164;
	const double expectedMass = 4114.833;
	const CCylinder cylinder;
	Cylinder_()
		: cylinder(expectedBaseRadius, expectedHeight, expectedDensity)
	{
	}
};

BOOST_FIXTURE_TEST_SUITE(Cylinder, Cylinder_)

	BOOST_AUTO_TEST_CASE(is_a_body)
	{
		BOOST_CHECK(static_cast<const CBody*>(&cylinder));
	}

	BOOST_AUTO_TEST_CASE(has_a_base_radius)
	{
		BOOST_CHECK_EQUAL(cylinder.GetBaseRadius(), expectedBaseRadius);
	}

	BOOST_AUTO_TEST_CASE(throw_the_invalid_argument_error_if_base_radius_does_not_correct)
	{
		BOOST_CHECK_THROW(CCylinder(0, 1, 1), std::invalid_argument);
		BOOST_CHECK_THROW(CCylinder(-1, 1, 1), std::invalid_argument);
		BOOST_CHECK_NO_THROW(CCylinder(0.01, 1, 1));
	}

	BOOST_AUTO_TEST_CASE(has_a_height)
	{
		BOOST_CHECK_EQUAL(cylinder.GetHeight(), expectedHeight);
	}

	BOOST_AUTO_TEST_CASE(throw_the_invalid_argument_error_if_height_does_not_correct)
	{
		BOOST_CHECK_THROW(CCylinder(1, 0, 1), std::invalid_argument);
		BOOST_CHECK_THROW(CCylinder(1, -1, 1), std::invalid_argument);
		BOOST_CHECK_NO_THROW(CCylinder(1, 0.01, 1));
	}

	BOOST_AUTO_TEST_CASE(has_a_density)
	{
		BOOST_CHECK_EQUAL(static_cast<const CBody&>(cylinder).GetDensity(), expectedDensity);
	}

	BOOST_AUTO_TEST_CASE(throw_the_invalid_argument_error_if_density_does_not_correct)
	{
		BOOST_CHECK_THROW(CCylinder(1, 1, 0), std::invalid_argument);
		BOOST_CHECK_THROW(CCylinder(1, 1, -1), std::invalid_argument);
		BOOST_CHECK_NO_THROW(CCylinder(1, 1, 0.01));
	}

	BOOST_AUTO_TEST_CASE(has_a_volume)
	{
		BOOST_CHECK_CLOSE_FRACTION(static_cast<const CBody&>(cylinder).GetVolume(), expectedVolume, 1e-7);
	}

	BOOST_AUTO_TEST_CASE(has_a_mass)
	{
		BOOST_CHECK_CLOSE_FRACTION(static_cast<const CBody&>(cylinder).GetMass(), expectedMass, 1e-7);
	}

	BOOST_AUTO_TEST_CASE(can_be_converted_to_string)
	{
		const auto expectedString = R"({ Cylinder }
	Base Radius = 12.2
	Height = 4.4
	Density = 2
	Volume = 2057.416
	Mass = 4114.833

)";
		BOOST_CHECK_EQUAL(static_cast<const CBody&>(cylinder).ToString(), expectedString);
	}

BOOST_AUTO_TEST_SUITE_END()