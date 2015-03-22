#include "MotionComponent.h"
#include "DayTimeEntity.h"

MotionComponent::MotionComponent()
    : GameObjectComponent("MotionComponent")
      , _targetPosition(0.f, 0.f, 0.f)
      , _isMoving(false)
      , _speed(1.f)
      , _threshold(1e-5)
    , _dayTime(nullptr)
      , _parentTransform(nullptr)
{
}

void MotionComponent::onBeforeFirstUpdate()
{
    _dayTime = (DayTimeEntity*)(GameEngine::engine()->currentEnvironment->findEntity(EN_DAYTIME));
}

void MotionComponent::onUpdate()
{
    if (!_shouldMove())
        return;

    if (isAtTargetPosition())
    {
        _isMoving = false;
    }
    else {
        _alignForwardVectorWithDistanceVector();
        _move();
    }
}

bool MotionComponent::_shouldMove()
{
    return (_speed > 0) && _isMoving;
}

void MotionComponent::onAttachToParent()
{
    _parentTransform = &_parent->getTransform();
    _targetPosition = _parentTransform->getWorldPosition();
}

void MotionComponent::setTargetPosition(const Vector3 &targetPosition)
{
    _isMoving = true;
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

void MotionComponent::setThreshold(const float t)
{
    _threshold = std::max(t, 0.f);
}

float MotionComponent::getThreshold() const
{
    return _threshold;
}

bool MotionComponent::isAtTargetPosition()
{
    _computeDistanceVector();
    return _distanceVector.norm() <= _threshold;
}

void MotionComponent::_computeDistanceVector()
{
    _distanceVector = _targetPosition - _parentTransform->getWorldPosition();
}

void MotionComponent::_alignForwardVectorWithDistanceVector()
{
    if (!_shouldAlignForwardVector())
        return;

    Vector3 forward = _parentTransform->getForwardVersor();
    Vector3 newForward = _distanceVector.normalized();
    float angle = acos(forward.dot(newForward));
    Vector3 axis = forward.cross(newForward).normalized();
    _parentTransform->rotate(axis, angle);
}

bool MotionComponent::_shouldAlignForwardVector()
{
    return _distanceVector.normalized().dot(_parentTransform->getForwardVersor()) < 0.999;
}

void MotionComponent::_move()
{
    float deltaTime = (float)_dayTime->getLastDelta().time;
    Vector3 motionVector = _speed * deltaTime * _distanceVector.normalized();

    if (_distanceVector.norm() < motionVector.norm())
    {
        _parentTransform->setWorldPosition(_targetPosition);
        _isMoving = false;
    }
    else
    {
        Vector3 worldPos = _parentTransform->getWorldPosition();
        _parentTransform->setWorldPosition(worldPos + motionVector);
    }
}
