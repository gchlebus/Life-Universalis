//
//  PaymentAgentComponent.h
//  Game
//
//  Created by Pawel Sulik on 13.04.15.
//  Copyright (c) 2015 LifeUniversalis. All rights reserved.
//

#pragma once
#include <GameEngine.h>
#include "DayTimeEntity.h"

class PaymentAgentComponent;

struct PaymentAction
{
    friend PaymentAgentComponent;
protected:
    PaymentAction(std::string description, unsigned int cashAmount, PaymentAgentComponent *targetAgent);
    std::string desc;
    unsigned int amount;
    PaymentAgentComponent *target;
    GameDate date;
};

class PaymentAgentComponent : public GameObjectComponent
{
public:
    PaymentAgentComponent();
    
    void addPayment(PaymentAction* payment);
    
    void onUpdate();
protected:
    int _cash;
    std::list<PaymentAction*> _addedActions;
    std::list<PaymentAction*> _history;
};