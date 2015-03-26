#pragma once

#include <GameEngine.h>

#define MC_PRIORITY_INTERACTION         1000
#define MC_PRIORITY_NAVIGATION_AGENT    900
#define MC_PRIORITY_FREE_MOTION         800

class DayTimeEntity;

class MotionComponent
  : public GameObjectComponent
{
public:
    MotionComponent();

    void onBeforeFirstUpdate();
    void onUpdate();
    void onAttachToParent();

    void abort(unsigned int priority);
    void setTargetPosition(const Vector3 &targetPosition, unsigned int priority);
    const Vector3& getTargetPosition() const;
    void setSpeed(const float speed);
    float getSpeed() const;
    
    void setThreshold(const float threshold);
    float getThreshold() const;
    
    bool isAtTargetPosition();
    
private:
    void _computeDistanceVector();
    void _alignForwardVectorWithDistanceVector();
    bool _shouldAlignForwardVector();
    void _move();

    unsigned int _lastPriority;
    Vector3 _targetPosition;
    Vector3 _distanceVector;
    
    bool _isMoving;

    //! Distance units / game time minute.
    float _speed;
    
    //! Distance in which the position will be accepted as target reached
    float _threshold;

    DayTimeEntity *_dayTime;
    Transform *_parentTransform;
};
