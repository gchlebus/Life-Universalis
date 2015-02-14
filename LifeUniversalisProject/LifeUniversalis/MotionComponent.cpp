#include "MotionComponent.h"
#include "GameObject.h"
#include "GameEngine.h"
#include "DayTimeEntity.h"

MotionComponent::MotionComponent()
  : GameObjectComponent("MotionComponent")
  , _dayTime(nullptr)
{
  
}

void MotionComponent::onStart()
{
  _dayTime = static_cast<DayTimeEntity*>(GameEngine::engine()->currentEnvironment->findEntity("DayTime"));
}

void MotionComponent::onBeforeFirstUpdate()
{
}
void MotionComponent::onUpdate()
{
  if (_isAtTargetPosition())
  {
    _move();
  }
}

void MotionComponent::onAttachToParent()
{
  _targetPosition = _parent->getTransform().getWorldPosition();
}

void MotionComponent::onDetachFromParent()
{
  
}

void MotionComponent::onDelete()
{
  
}
void MotionComponent::onEnabled()
{
    
}
void MotionComponent::onDisabled()
{
    
}

void MotionComponent::setTargetPosition(const Vector3 &targetPosition)
{
  _targetPosition = targetPosition;
}

const Vector3& MotionComponent::getTargetPosition() const
{
  return _targetPosition;
}

void MotionComponent::setSpeed(const float speed)
{
  _speed = speed;
}

float MotionComponent::getSpeed() const
{
  return _speed;
}

bool MotionComponent::_isAtTargetPosition()
{
  return _parent->getTransform().getWorldPosition() == _targetPosition;
}

void MotionComponent::_move()
{
  Vector3 worldPos = _parent->getTransform().getWorldPosition();
  Vector3 vec = _targetPosition - worldPos;
  vec.normalize();
  
  //float lastDelta = static_cast<float>(GameEngine::engine()->kernel->timer->getLastDelta());
  
  //_parent->getTransform().setWorldPosition(worldPos + _speed*T_S(lastDelta)*vec);
}
