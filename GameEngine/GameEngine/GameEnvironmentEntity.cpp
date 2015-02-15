#include "GameEnvironmentEntity.h"

GameEnvironmentEntity::GameEnvironmentEntity(const std::string &name) : _name(name)
{
}

const std::string& GameEnvironmentEntity::getName() const
{
	return _name;
}