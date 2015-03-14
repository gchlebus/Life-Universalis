#pragma once

#include <GameEngine.h>

class Workplace;
class HumanAIMasterComponent;
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
    MotionComponent* humanMotion;

private:
    std::string _name;
    unsigned int _age;
    int _money;
    GameObject* _home;
    Workplace* _workplace;
};
