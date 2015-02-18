#include "MotionComponent.h"
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
  if ((_speed > 0) && (!_isAtTargetPosition()))
  {
    _computeDistanceVector();
    _alignForwardVectorWithDistanceVector();
    _move();
  }
}

void MotionComponent::onAttachToParent()
{
  _parentTransform = &_parent->getTransform();
  _targetPosition = _parentTransform->getWorldPosition();
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
  _speed = std::max(speed, 0.f);
}

float MotionComponent::getSpeed() const
{
  return _speed;
}

bool MotionComponent::_isAtTargetPosition()
{
  return _parentTransform->getWorldPosition() == _targetPosition;
}

void MotionComponent::_computeDistanceVector()
{
  _distanceVector = _targetPosition - _parentTransform->getWorldPosition();
}

void MotionComponent::_alignForwardVectorWithDistanceVector()
{
  if (_shouldAlignForwardVector())
  {
    Vector3 forward = _parentTransform->getForwardVersor();
    Vector3 newForward = _distanceVector.normalized();
    float angle = acos(forward.dot(newForward));
    Vector3 axis = forward.cross(newForward).normalized();
    _parentTransform->rotate(axis, angle);
  }
}

bool MotionComponent::_shouldAlignForwardVector()
{
  return _distanceVector.normalized().dot(_parentTransform->getForwardVersor()) < 0.999;
}

void MotionComponent::_move()
{
  float deltaTime = static_cast<float>(_dayTime->getLastDelta().time);
  Vector3 motionVector = _speed * deltaTime * _distanceVector.normalized();
  
  if (_distanceVector.norm() < motionVector.norm())
  {
    _parentTransform->setWorldPosition(_targetPosition);
  }
  else
  {
    Vector3 worldPos = _parentTransform->getWorldPosition();
    _parentTransform->setWorldPosition(worldPos + motionVector);
  }
}
