#include "HumanManagerEntity.h"
#include "BuildingTestComponent.h"


HumanManagerEntity::HumanManagerEntity() : GameEnvironmentEntity("HumanManager")
{
}


HumanManagerEntity::~HumanManagerEntity(void)
{
}


void HumanManagerEntity::onStart()
{
}

void HumanManagerEntity::onUpdate()
{
	std::cout << "HumanManager sie kurwa update'uje!!!!!!!!!!\n";
}

void HumanManagerEntity::onStop()
{
    std::cout << "COMMITTEST";
}

GameObject* HumanManagerEntity::create()
{
	GameObject* retVal = new GameObject();
	retVal->setName("Human");
	//retVal->addComponent(new BuildingTestComponent());
	return retVal;
}

void HumanManagerEntity::add(GameObject* human)
{
	GameEngine::engine()->currentScene->addObject(human);
	_humans.push_back(human);
}

void HumanManagerEntity::remove(GameObject* human)
{
	GameEngine::engine()->currentScene->removeObject(human);
	for(int i = 0; i < _humans.size(); i++)
	{
		if(_humans[i] == human)
		{
			_humans.erase(_humans.begin() + i);
			return;
		}
	}
}