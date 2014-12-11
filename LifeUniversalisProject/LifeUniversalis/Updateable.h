#pragma once
#include "GlobalHeaders.h"

class Updateable
{
public:
	virtual void update(double ms) = 0;
};