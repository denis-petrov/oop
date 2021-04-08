#include "stdafx.h"

#define _USE_MATH_DEFINES
#include "../task1/Cone.h"
#include <math.h>

struct Cone_
{
	const double expectedBaseRadius = 12.2;
	const double expectedHeight = 4.4;
	const double expectedDensity = 2;
	const double expectedVolume = 685.80548;
	const double expectedMass = 1371.6109;
	const CCone cone;
	Cone_()
		: cone(expectedBaseRadius, expectedHeight, expectedDensity)
	{
	}
};

BOOST_FIXTURE_TEST_SUITE(Cone, Cone_)

	BOOST_AUTO_TEST_CASE(is_a_body)
	{
		BOOST_CHECK(static_cast<const CBody*>(&cone));
	}

	BOOST_AUTO_TEST_CASE(has_a_base_radius)
	{
		BOOST_CHECK_EQUAL(cone.GetBaseRadius(), expectedBaseRadius);
	}

	BOOST_AUTO_TEST_CASE(throw_the_invalid_argument_error_if_base_radius_does_not_correct)
	{
		BOOST_CHECK_THROW(CCone(0, 1, 1), std::invalid_argument);
		BOOST_CHECK_THROW(CCone(-1, 1, 1), std::invalid_argument);
		BOOST_CHECK_NO_THROW(CCone(0.01, 1, 1));
	}

	BOOST_AUTO_TEST_CASE(has_a_height)
	{
		BOOST_CHECK_EQUAL(cone.GetHeight(), expectedHeight);
	}

	BOOST_AUTO_TEST_CASE(throw_the_invalid_argument_error_if_height_does_not_correct)
	{
		BOOST_CHECK_THROW(CCone(1, 0, 1), std::invalid_argument);
		BOOST_CHECK_THROW(CCone(1, -1, 1), std::invalid_argument);
		BOOST_CHECK_NO_THROW(CCone(1, 0.01, 1));
	}

	BOOST_AUTO_TEST_CASE(has_a_density)
	{
		BOOST_CHECK_EQUAL(static_cast<const CBody&>(cone).GetDensity(), expectedDensity);
	}

	BOOST_AUTO_TEST_CASE(throw_the_invalid_argument_error_if_density_does_not_correct)
	{
		BOOST_CHECK_THROW(CCone(1, 1, 0), std::invalid_argument);
		BOOST_CHECK_THROW(CCone(1, 1, -1), std::invalid_argument);
		BOOST_CHECK_NO_THROW(CCone(1, 1, 0.01));
	}

	BOOST_AUTO_TEST_CASE(has_a_volume)
	{
		BOOST_CHECK_CLOSE_FRACTION(static_cast<const CBody&>(cone).GetVolume(), expectedVolume, 1e-7);
	}

	BOOST_AUTO_TEST_CASE(has_a_mass)
	{
		BOOST_CHECK_CLOSE_FRACTION(static_cast<const CBody&>(cone).GetMass(), expectedMass, 1e-7);
	}

	BOOST_AUTO_TEST_CASE(can_be_converted_to_string)
	{
		const auto expectedString = R"({ Cone }
	Base Radius = 12.2
	Height = 4.4
	Density = 2
	Volume = 685.805
	Mass = 1371.611

)";
		BOOST_CHECK_EQUAL(static_cast<const CBody&>(cone).ToString(), expectedString);
	}

BOOST_AUTO_TEST_SUITE_END()