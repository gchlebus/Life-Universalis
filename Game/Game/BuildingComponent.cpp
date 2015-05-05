//
//  BuildingComponent.cpp
//  LifeUniversalis
//
//  Created by Pawel Sulik on 14.02.15.
//
//

#include "BuildingComponent.h"
#include "IMachine.h"

BuildingComponent::BuildingComponent()
    : GameObjectComponent("BuildingComponent")
{

}

BuildingComponent::~BuildingComponent()
{
    for (auto& m: _machines)
        delete m;
}

void BuildingComponent::onParentChangedComponents()
{
    paymentAgent = (PaymentAgentComponent*)_parent->findComponent("PaymentAgentComponent");
}

void BuildingComponent::onUpdate()
{
    for (auto& m: _machines)
        m->update();
}

void BuildingComponent::addMachine(IMachine* machine)
{
    if (_isMachinePresent(machine))
    {
        machine->setParent(this);
        _machines.push_back(machine);
    }
}

Workplace::PtrVector BuildingComponent::getWorkplaces()
{
    Workplace::PtrVector v;

    for (auto& m: _machines)
    {
        Workplace::PtrVector tmp = m->getWorkplaces();
        v.insert(v.end(), tmp.begin(), tmp.end());
    }

    return v;
}

bool BuildingComponent::_isMachinePresent(IMachine* machine)
{
    return find(_machines.begin(), _machines.end(), machine) == _machines.end();
}
