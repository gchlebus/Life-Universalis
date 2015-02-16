#pragma once

#include <gmock/gmock.h>
#include <GameEngine.h>

class GameObjectComponentMock : public GameObjectComponent
{
public:
	GameObjectComponentMock() : GameObjectComponent("MockComponent") { }

	MOCK_METHOD1(attachToParent, void(GameObject *parent));
    MOCK_METHOD0(onStart, void());
    MOCK_METHOD0(onBeforeFirstUpdate, void());
    MOCK_METHOD0(onUpdate, void());
	MOCK_METHOD0(onAttachToParent, void());
    MOCK_METHOD0(onDetachFromParent, void());
    MOCK_METHOD0(onDelete, void());
    MOCK_METHOD0(onEnabled, void());
    MOCK_METHOD0(onDisabled, void());
};
