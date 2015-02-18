#include "TestGameEngine.h"

#include <gtest/gtest.h>
#include <MotionComponent.h>
#include <GameEngine.h>
#include <DayTimeEntity.h>

class MotionComponentTest : public ::testing::Test
{
protected:
  void SetUp()
  {
    dayTimeEntity = new DayTimeEntity();
    object = new GameObject();
    motion = new MotionComponent();
    
    engine.engine->currentEnvironment->addEntity(dayTimeEntity);
    object->addComponent(motion);
    engine.engine->currentScene->addObject(object);
    
    engine.run();
  }
  
  void TearDown()
  {
    engine.stop();
    
    delete dayTimeEntity;
    delete object;
  }
  
  void msWait(unsigned int ms)
  {
    boost::this_thread::sleep(boost::posix_time::milliseconds(ms));
  }
  
  TestGameEngine engine;
  DayTimeEntity *dayTimeEntity;
  GameObject *object;
  MotionComponent *motion;
};

TEST_F(MotionComponentTest, OnSetTargetAndNonZeroSpeed_FwdVectorPointsAtTargetPosition)
{
  Vector3 target(1.f, 1.f, 1.f);
  motion->setSpeed(1);
  motion->setTargetPosition(target);
  
  msWait(10);
  
  Vector3 fwd = object->getTransform().getForwardVersor();
  ASSERT_FLOAT_EQ(1.0f, fwd.dot(target.normalized()));
}

TEST_F(MotionComponentTest, OnSetTargetAndZeroSpeed_FwdVectorIsNotRotated)
{
  Vector3 target(1.f, 1.f, 1.f);
  Vector3 oldFwd = object->getTransform().getForwardVersor();
  motion->setSpeed(0);
  motion->setTargetPosition(target);
  
  msWait(10);
  
  Vector3 newFwd = object->getTransform().getForwardVersor();
  ASSERT_FLOAT_EQ(1.f, oldFwd.dot(newFwd));
}

TEST_F(MotionComponentTest, OnSetTargetAndNonZeroSpeed_GameObjectArrivesAtTarget)
{
  Vector3 target(1.f, 1.f, 1.f);
  motion->setSpeed(1);
  motion->setTargetPosition(target);
  
  msWait(10);
  
  Vector3 pos = object->getTransform().getWorldPosition();
  ASSERT_FLOAT_EQ(0.f, (target - pos).norm());
}

TEST_F(MotionComponentTest, OnSetTargetAndZeroSpeed_GameObjectDoesNotMove)
{
  Vector3 target(1.f, 1.f, 1.f);
  Vector3 oldPos = object->getTransform().getWorldPosition();
  motion->setSpeed(0);
  motion->setTargetPosition(target);
  
  msWait(10);
  
  Vector3 newPos = object->getTransform().getWorldPosition();
  ASSERT_FLOAT_EQ(0.f, (oldPos - newPos).norm());
}
