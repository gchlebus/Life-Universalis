#pragma once

#include <GameEngine.h>
#include "HumanComponentNames.h"

class Workplace;
class HumanAIMasterComponent;
class HumanInteractionControllerComponent;
class MotionComponent;

class HumanComponent : public GameObjectComponent
{
public:
    HumanComponent(const std::string& name, unsigned int age);

    const std::string& getHumanName() const;

    unsigned int getAge() const;

    int getMoney() const;
    void addMoney(int amount);
    void deductMoney(int amount);

    GameObject* getHome() const;
    void setHome(GameObject* home);

    Workplace* getWorkplace() const;
    void setWorkplace(Workplace* workplace);
    
    
    void onParentChangedComponents();
    
    HumanAIMasterComponent* humanAIMaster;
    HumanInteractionControllerComponent* humanInteraction;
    MotionComponent* humanMotion;

private:
    std::string _name;
    unsigned int _age;
    int _money;
    GameObject* _home;
    Workplace* _workplace;
};
