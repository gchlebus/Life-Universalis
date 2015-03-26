#include "MotionComponent.h"
#include "DayTimeEntity.h"

MotionComponent::MotionComponent()
    : GameObjectComponent("MotionComponent")
    , _dayTime(nullptr)
{
    _isMoving = false;
    _speed = 1.0f;
    _threshold = 2.0f;
}

void MotionComponent::onBeforeFirstUpdate()
{
    _dayTime = (DayTimeEntity*)(GameEngine::engine()->currentEnvironment->findEntity(EN_DAYTIME));
}

void MotionComponent::onUpdate()
{
    if ((_speed > 0) && _isMoving)
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

void MotionComponent::abort(unsigned int priority)
{
    if(priority >= _lastPriority)
        _isMoving = false;
}

void MotionComponent::setTargetPosition(const Vector3 &targetPosition, unsigned int priority)
{
    if((_isMoving && priority >= _lastPriority) || !_isMoving)
    {
        _isMoving = true;
        _targetPosition = targetPosition;
        _lastPriority = priority;
    }
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
    return _distanceVector.norm() <= _threshold;
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
    if(_distanceVector.norm() > 0.0)
        return _distanceVector.normalized().dot(_parentTransform->getForwardVersor()) < 0.999;
    return false;
}

void MotionComponent::_move()
{
    float deltaTime = (float)_dayTime->getLastDelta().time;
    Vector3 motionVector = _speed * deltaTime * _distanceVector.normalized();
    
    if (_distanceVector.norm() <= 0.0001f || _distanceVector.norm() < motionVector.norm())
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
