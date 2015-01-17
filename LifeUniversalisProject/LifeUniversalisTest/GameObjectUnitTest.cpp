#include "..\LifeUniversalis\GameObject.h"
#include "GameObjectComponentMock.h"

#include <gtest\gtest.h>

class GameObjectTest : public ::testing::Test
{
protected:
	GameObject gameObject;
};

TEST_F(GameObjectTest, DestructorTest)
{
	GameObjectComponentMock *component = new GameObjectComponentMock();
	EXPECT_CALL(*component, onDetachFromParent()).Times(1);
	EXPECT_CALL(*component, onDelete()).Times(1);

	{
		GameObject object;
		object.addComponent(component);
	}
}

TEST_F(GameObjectTest, StartTest)
{
	GameObjectComponentMock *component = new GameObjectComponentMock();
	EXPECT_CALL(*component, onStart()).Times(1);
	gameObject.addComponent(component);
	gameObject.start();
}

TEST_F(GameObjectTest, UpdateTest)
{
	GameObjectComponentMock *component = new GameObjectComponentMock();
	EXPECT_CALL(*component, onUpdate()).Times(1);
	gameObject.addComponent(component);
	gameObject.update();
}

TEST_F(GameObjectTest, AddComponentTest)
{
	GameObjectComponentMock *component = new GameObjectComponentMock();
	EXPECT_CALL(*component, onAttachToParent()).Times(1);
	ASSERT_TRUE(gameObject.addComponent(component));
	ASSERT_FALSE(gameObject.addComponent(component));
}

TEST_F(GameObjectTest, FindComponentTest)
{
	GameObjectComponentMock *component = new GameObjectComponentMock();
	gameObject.addComponent(component);
	ASSERT_EQ(component, gameObject.findComponent(component->getName()));
	ASSERT_EQ(nullptr, gameObject.findComponent("ComponentThatNotExists"));
}

TEST_F(GameObjectTest, RemoveComponentTest)
{
	GameObjectComponentMock *component = new GameObjectComponentMock();
	gameObject.addComponent(component);
	EXPECT_CALL(*component, onDetachFromParent()).Times(1);
	ASSERT_EQ(component, gameObject.removeComponent(component->getName()));
	ASSERT_EQ(nullptr, gameObject.removeComponent("ComponentThatNotExists"));
	delete component;
}

TEST_F(GameObjectTest, DeleteComponentTest)
{
	GameObjectComponentMock *component = new GameObjectComponentMock();
	gameObject.addComponent(component);
	EXPECT_CALL(*component, onDetachFromParent()).Times(1);
	EXPECT_CALL(*component, onDelete()).Times(1);
	ASSERT_TRUE(gameObject.deleteComponent(component->getName()));
	ASSERT_FALSE(gameObject.deleteComponent("ComponentThatNotExists"));
}
