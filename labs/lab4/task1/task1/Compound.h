#pragma once
#include "Body.h"

class CCompound : public CBody
{
public:
	template <typename T>
	bool AddChildBody(const T& child)
	{
		if (IsBody(child))
		{
			m_children.push_back(std::make_shared<T>(child));
			return true;
		}
		return false;
	}

	double GetVolume() const override final;
	double GetMass() const override final;
	double GetDensity() const override final;
	std::string ToString() const override final;

private:
	std::vector<std::shared_ptr<CBody>> m_children;

	template <typename T>
	bool IsBody(T const& item)
	{
		return dynamic_cast<CBody const*>(&item);
	}
};
