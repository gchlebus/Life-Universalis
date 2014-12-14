#pragma once
#include "GlobalHeaders.h"

class Updateable
{
public:
	//! \param deltaTime - Real time in [ms].
	virtual void update(const float deltaTime) = 0;
};