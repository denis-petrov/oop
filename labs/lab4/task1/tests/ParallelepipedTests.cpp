#include "stdafx.h"

#define _USE_MATH_DEFINES
#include "../task1/Parallelepiped.h"
#include <math.h>

struct Parallelepiped_
{
	const double expectedWidth = 12.2;
	const double expectedHeight = 4.4;
	const double expectedDepth = 8.8;
	const double expectedDensity = 2;
	const double expectedVolume = 472.384;
	const double expectedMass = 944.768;
	const CParallelepiped parallelepiped;
	Parallelepiped_()
		: parallelepiped(expectedWidth, expectedHeight, expectedDepth, expectedDensity)
	{
	}
};

BOOST_FIXTURE_TEST_SUITE(Parallelepiped, Parallelepiped_)

	BOOST_AUTO_TEST_CASE(is_a_body)
	{
		BOOST_CHECK(static_cast<const CBody*>(&parallelepiped));
	}

	BOOST_AUTO_TEST_CASE(has_a_width)
	{
		BOOST_CHECK_EQUAL(parallelepiped.GetWidth(), expectedWidth);
	}

	BOOST_AUTO_TEST_CASE(throw_the_invalid_argument_error_if_width_does_not_correct)
	{
		BOOST_CHECK_THROW(CParallelepiped(0, 1, 1), std::invalid_argument);
		BOOST_CHECK_THROW(CParallelepiped(-1, 1, 1), std::invalid_argument);
		BOOST_CHECK_NO_THROW(CParallelepiped(0.01, 1, 1));
	}

	BOOST_AUTO_TEST_CASE(has_a_height)
	{
		BOOST_CHECK_EQUAL(parallelepiped.GetHeight(), expectedHeight);
	}

	BOOST_AUTO_TEST_CASE(throw_the_invalid_argument_error_if_height_does_not_correct)
	{
		BOOST_CHECK_THROW(CParallelepiped(1, 0, 1), std::invalid_argument);
		BOOST_CHECK_THROW(CParallelepiped(1, -1, 1), std::invalid_argument);
		BOOST_CHECK_NO_THROW(CParallelepiped(1, 0.01, 1));
	}

	BOOST_AUTO_TEST_CASE(has_a_depth)
	{
		BOOST_CHECK_EQUAL(parallelepiped.GetDepth(), expectedDepth);
	}

	BOOST_AUTO_TEST_CASE(throw_the_invalid_argument_error_if_depth_does_not_correct)
	{
		BOOST_CHECK_THROW(CParallelepiped(1, 1, 0), std::invalid_argument);
		BOOST_CHECK_THROW(CParallelepiped(1, 1, -1), std::invalid_argument);
		BOOST_CHECK_NO_THROW(CParallelepiped(1, 1, 0.01));
	}

	BOOST_AUTO_TEST_CASE(has_a_density)
	{
		BOOST_CHECK_EQUAL(static_cast<const CBody&>(parallelepiped).GetDensity(), expectedDensity);
	}

	BOOST_AUTO_TEST_CASE(throw_the_invalid_argument_error_if_density_does_not_correct)
	{
		BOOST_CHECK_THROW(CParallelepiped(1, 1, 1, 0), std::invalid_argument);
		BOOST_CHECK_THROW(CParallelepiped(1, 1, 1, -1), std::invalid_argument);
		BOOST_CHECK_NO_THROW(CParallelepiped(1, 1, 1, 0.01));
	}

	BOOST_AUTO_TEST_CASE(has_a_volume)
	{
		BOOST_CHECK_CLOSE_FRACTION(static_cast<const CBody&>(parallelepiped).GetVolume(), expectedVolume, 1e-7);
	}

	BOOST_AUTO_TEST_CASE(has_a_mass)
	{
		BOOST_CHECK_CLOSE_FRACTION(static_cast<const CBody&>(parallelepiped).GetMass(), expectedMass, 1e-7);
	}

	BOOST_AUTO_TEST_CASE(can_be_converted_to_string)
	{
		const auto expectedString = R"({ Parallelepiped }
	Width = 12.2
	Height = 4.4
	Depth = 8.8
	Density = 2
	Volume = 472.384
	Mass = 944.768

)";
		BOOST_CHECK_EQUAL(static_cast<const CBody&>(parallelepiped).ToString(), expectedString);
	}

BOOST_AUTO_TEST_SUITE_END()