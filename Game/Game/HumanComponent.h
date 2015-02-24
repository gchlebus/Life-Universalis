#pragma once

#include <GameEngine.h>

class Workplace;

class HumanComponent
: public GameObjectComponent
{
public:
  HumanComponent(const std::string& name, unsigned int age);
  
  const std::string& getName() const;
  
  unsigned int getAge() const;
  
  int getMoney() const;
  void addMoney(int amount);
  void deductMoney(int amount);
  
  const GameObject* getHome() const;
  void setHome(GameObject* home);
  
  const Workplace* getWorkplace() const;
  void setWorkplace(Workplace* workplace);
  
private:
  std::string _name;
  unsigned int _age;
  int _money;
  GameObject* _home;
  Workplace* _workplace;
};
