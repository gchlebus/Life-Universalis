#include "HumanComponent.h"
#include "HumanComponentNames.h"

HumanComponent::HumanComponent(const std::string& name, unsigned int age)
: GameObjectComponent(HC_MAIN)
, _name(name)
, _age(age)
, _money(0)
, _home(nullptr)
, _workplace(nullptr)
{
}

const std::string& HumanComponent::getHumanName() const
{
    return _name;
}

unsigned int HumanComponent::getAge() const
{
    return _age;
}

int HumanComponent::getMoney() const
{
    return _money;
}

void HumanComponent::addMoney(int amount)
{
    _money += amount;
}

void HumanComponent::deductMoney(int amount)
{
    _money -= amount;
}

GameObject* HumanComponent::getHome() const
{
    return _home;
}

void HumanComponent::setHome(GameObject* home)
{
    _home = home;
}

Workplace* HumanComponent::getWorkplace() const
{
    return _workplace;
}

void HumanComponent::setWorkplace(Workplace* workplace)
{
    _workplace = workplace;
}

void HumanComponent::onParentChangedComponents()
{
    humanAIMaster = (HumanAIMasterComponent*)_parent->findComponent("HumanAIMasterComponent");
    humanMotion = (MotionComponent*)_parent->findComponent(HC_MOTION);
    humanInteraction = (HumanInteractionControllerComponent*)_parent->findComponent(HC_INTERACTION_CONTROLLER);
}
