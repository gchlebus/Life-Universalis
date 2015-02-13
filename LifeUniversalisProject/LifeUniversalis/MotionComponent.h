#pragma once

#include "GlobalHeaders.h"
#include "GameObjectComponent.h"

class GameObject;

class LIFEUNIVERSALIS_EXPORT MotionComponent
  : public GameObjectComponent
{
public:
  MotionComponent(GameObject *parent = nullptr);
  
  void onStart();
  void onUpdate();
  void onAttachToParent();
  void onDetachFromParent();
  void onDelete();
  
  void setTargetPosition(const Vector3 &targetPosition);
  const Vector3& getTargetPosition() const;
  void setSpeed(const float speed);
  float getSpeed() const;
  
private:
  bool _isAtTargetPosition();
  void _move();
  
  Vector3 _targetPosition;
  //! Distance units / game time second.
  float _speed;
};
