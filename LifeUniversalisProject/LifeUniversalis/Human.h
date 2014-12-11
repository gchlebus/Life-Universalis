#pragma once
#include "GlobalHeaders.h"
#include "Updateable.h"

class Human : public Updateable
{
public:
	Human();
	void update();
//protected:
	float hunger;
	float health;
	float entertainment;
	float education;
};