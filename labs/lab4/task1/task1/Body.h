#pragma once
#include "stdafx.h"

class CBody
{
public:
	virtual double GetDensity() const = 0;
	virtual double GetVolume() const = 0;
	virtual double GetMass() const = 0;
	virtual std::string ToString(const int padding = PADDING) const = 0;

	virtual int GetId() const = 0;
	virtual void SetId(const int id) = 0;

	virtual ~CBody(){};
};
