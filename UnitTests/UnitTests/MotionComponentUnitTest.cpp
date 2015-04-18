#include "TestGameEngine.h"

#include <gtest/gtest.h>
#include <MotionComponent.h>

class MotionComponentTest
    : public ::testing::Test
{
protected:
    MotionComponentTest()
    {
        motionComponent = new MotionComponent();
        motionComponent->setSpeed(1.f);
        gameObject.addComponent(motionComponent);
    }

    Vector3 getGameObjectForwardVersor()
    {
        return gameObject.getTransform().getForwardVersor();
    }

    Vector3 getGameObjectWorldPosition()
    {
        return gameObject.getTransform().getWorldPosition();
    }

    TestGameEngine engine;
    GameObject gameObject;
    MotionComponent* motionComponent;
};

TEST_F(MotionComponentTest, OnNoTargetSetAndGameObjectPositionChange_GameObjectDoesNotMove)
{
    Vector3 pos(1.f, 1.f, 1.f);
    gameObject.getTransform().setWorldPosition(pos);

    engine.setLastDelta(1);
    motionComponent->onUpdate();

    ASSERT_FLOAT_EQ(0.f, (getGameObjectWorldPosition() - pos).norm());
}

TEST_F(MotionComponentTest, OnTargetPositionEqualToCurrentPosition_GameObjectDoesNotMove)
{
    Vector3 pos = getGameObjectWorldPosition();
    motionComponent->setTargetPosition(pos, MC_PRIORITY_TASK);

    engine.setLastDelta(1);
    motionComponent->onUpdate();

    ASSERT_FLOAT_EQ(0.f, (pos - getGameObjectWorldPosition()).norm());
}

TEST_F(MotionComponentTest, OnTargetPositionEqualToCurrentPosition_GameObjectDoesNotRotate)
{
    Vector3 fwd = getGameObjectForwardVersor();
    motionComponent->setTargetPosition(getGameObjectWorldPosition(), MC_PRIORITY_TASK);

    motionComponent->onUpdate();

    ASSERT_FLOAT_EQ(0.f, (getGameObjectForwardVersor() - fwd).norm());
}


class SetTargetMotionComponentTest
    : public MotionComponentTest
{
protected:
    SetTargetMotionComponentTest()
    {
        // with speed=1 target should be reached in 5 min
        target = Vector3(3.f, 4.f, 0.f);
        motionComponent->setTargetPosition(target, MC_PRIORITY_TASK);
    }

    Vector3 target;
};

TEST_F(SetTargetMotionComponentTest, FwdVectorPointsAtTargetPosition)
{
    motionComponent->onUpdate();

    ASSERT_FLOAT_EQ(1.0f, getGameObjectForwardVersor().dot(target.normalized()));
}

TEST_F(SetTargetMotionComponentTest, WhenGivenEnoughTime_GameObjectArrivesAtTarget)
{
    engine.setLastDelta(5);
    motionComponent->onUpdate();

    Vector3 pos = getGameObjectWorldPosition();
    ASSERT_FLOAT_EQ(0.f, (target - pos).norm());
}

TEST_F(SetTargetMotionComponentTest, WhenZeroSpeed_FwdVectorIsNotRotated)
{
    Vector3 oldFwd = getGameObjectForwardVersor();
    motionComponent->setSpeed(0);

    motionComponent->onUpdate();

    ASSERT_FLOAT_EQ(1.f, oldFwd.dot(getGameObjectForwardVersor()));
}

TEST_F(SetTargetMotionComponentTest, WhenZeroSpeed_GameObjectDoesNotMove)
{
    Vector3 oldPos = getGameObjectWorldPosition();
    motionComponent->setSpeed(0);

    engine.setLastDelta(1);
    motionComponent->onUpdate();

    ASSERT_FLOAT_EQ(0.f, (oldPos - getGameObjectWorldPosition()).norm());
}
