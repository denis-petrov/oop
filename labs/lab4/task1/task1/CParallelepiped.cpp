#include "Parallelepiped.h"

using namespace std;

CParallelepiped::CParallelepiped(const double width, const double height, const double depth, const double density) 
	: CSolidBody(density)
	, m_width(width)
	, m_height(height)
	, m_depth(depth)
{
	if (m_width < DEFAULT_WIDTH || m_height < DEFAULT_HEIGTH || m_depth < DEFAULT_DEPTH)
	{
		throw invalid_argument("Not correct parameters for parallelepiped.");
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

string CParallelepiped::ToString() const 
{
	stringstream stream;
	stream << "{ Parallelepiped }\n"
		   << "Width: " << GetWidth()
		   << "Height: " << GetHeight()
		   << "Depth: " << GetDepth()
		   << CSolidBody::ToString() << "\n";
	return stream.str();
}