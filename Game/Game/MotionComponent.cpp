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

void MotionComponent::onStart()
{
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
        LOGF(F("Dist norm %1%") % _distanceVector.norm());
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
    
//    LOGF(F("Dist vec len %1%") % _distanceVector.norm());
//    LOGF(F("Motion vec len %1%") % motionVector.norm());
//    
//    LOGF(F("Dist Vec %1% %2% %3%") % _distanceVector.x() % _distanceVector.y() % _distanceVector.z());
//    LOGF(F("Motion Vec %1% %2% %3%") % motionVector.x() % motionVector.y() % motionVector.z());
//    
//    
//    Vector3 pos = _parentTransform->getWorldPosition();
//    LOGF(F("Target Vec %1% %2% %3%") % _targetPosition.x() % _targetPosition.y() % _targetPosition.z());
//    LOGF(F("Position Vec %1% %2% %3%") % pos.x() % pos.y() % pos.z());
    
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
