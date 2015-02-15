#pragma once
#include "GlobalHeaders.h"

class GAMEENGINE_EXPORT GameEnvironmentEntity
{
public:
	GameEnvironmentEntity(const std::string &name);
	virtual void onStart() = 0;
	virtual void onUpdate() = 0;
	virtual void onStop() = 0;

	const std::string& getName() const;
private:
	std::string _name;
};