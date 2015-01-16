#pragma once

#include "..\LifeUniversalis\GameObjectComponent.h"

#include <gmock/gmock.h>

class GameObjectComponentMock : public GameObjectComponent
{
public:
	GameObjectComponentMock() : GameObjectComponent("MockComponent") { }

	MOCK_METHOD1(attachToParent, void(GameObject *parent));
	MOCK_METHOD0(onStart, void());
	MOCK_METHOD0(onUpdate, void());
	MOCK_METHOD0(onAttachToParent, void());
	MOCK_METHOD0(onDetachFromParent, void());
	MOCK_METHOD0(onDelete, void());
};
