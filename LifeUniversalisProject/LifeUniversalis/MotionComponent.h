#pragma once

#include "GlobalHeaders.h"
#include "GameObjectComponent.h"
#include "GameEnvironment.h"

class GameObject;
class DayTimeEntity;

class LIFEUNIVERSALIS_EXPORT MotionComponent
  : public GameObjectComponent
{
public:
    MotionComponent();

    void onStart();
    void onBeforeFirstUpdate();
    void onUpdate();
    void onAttachToParent();
    void onDetachFromParent();
    void onDelete();
    void onEnabled();
    void onDisabled();

    void setTargetPosition(const Vector3 &targetPosition);
    const Vector3& getTargetPosition() const;
    void setSpeed(const float speed);
    float getSpeed() const;
  
private:
    bool _isAtTargetPosition();
    void _move();

    Vector3 _targetPosition;

    //! Distance units / game time minute.
    float _speed;

    DayTimeEntity *_dayTime;
};
