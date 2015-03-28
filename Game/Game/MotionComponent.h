#pragma once

#include <GameEngine.h>

class DayTimeEntity;

class MotionComponent
    : public GameObjectComponent
{
public:
    MotionComponent();

    void onUpdate();
    void onAttachToParent();

    void setTargetPosition(const Vector3 &targetPosition);
    const Vector3& getTargetPosition() const;

    bool isAtTargetPosition();

    void setSpeed(const float speed);
    float getSpeed() const;

    void setThreshold(const float threshold);
    float getThreshold() const;

private:
    bool _shouldMove();
    void _computeDistanceVector();
    void _alignForwardVectorWithDistanceVector();
    bool _shouldAlignForwardVector();

    void _move();
    Vector3 _targetPosition;
    Vector3 _distanceVector;
    bool _isMoving;
    //! Distance units / game time minute.
    float _speed;
    //! Distance in which the position will be accepted as target reached.
    float _threshold;
    DayTimeEntity *_dayTime;

    Transform *_parentTransform;
};
