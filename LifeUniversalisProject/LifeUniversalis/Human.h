#pragma once
#include "GlobalHeaders.h"
#include "Updateable.h"

class Human : public Updateable
{
public:
	Human();
	void update(double ms);
//protected:
	float satiety;
	float health;
	float entertainment;
	float education;
};