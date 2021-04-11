#include "Parallelepiped.h"

using namespace std;

CParallelepiped::CParallelepiped(const double width, const double height, const double depth, const double density) 
	: CSolidBody(density)
	, m_width(width)
	, m_height(height)
	, m_depth(depth)
{
	if (!(m_width > MIN_PARAM && m_height > MIN_PARAM && m_depth > MIN_PARAM))
	{
		throw invalid_argument("Not correct parameters for Parallelepiped.");
	}
}

double CParallelepiped::GetVolume() const 
{
	return GetWidth() * GetHeight() * GetDepth();
}

double CParallelepiped::GetWidth() const 
{
	return m_width;
}

double CParallelepiped::GetHeight() const 
{
	return m_height;
}

double CParallelepiped::GetDepth() const 
{
	return m_depth;
}

string CParallelepiped::ToString(const int padding) const
{
	stringstream stream;
	stream << "{ Parallelepiped }" << endl
		   << string("\t", padding) << "Width = " << GetWidth() << endl
		   << string("\t", padding) << "Height = " << GetHeight() << endl
		   << string("\t", padding) << "Depth = " << GetDepth() << endl
		   << CSolidBody::ToString() << endl;
	return stream.str();
}