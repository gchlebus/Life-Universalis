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
    PaymentAction(std::string description, unsigned int cashAmount, PaymentAgentComponent *sourceAgent);
    std::string desc;
    unsigned int amount;
    PaymentAgentComponent *source;
    GameDate date;
};

enum PaymentResult
{
    OK,
    InsufficientFinancialResources,
    InvalidTarget
};

class PaymentAgentComponent : public GameObjectComponent
{
public:
    PaymentAgentComponent();
    
    PaymentResult bookPayment(unsigned int amount, PaymentAgentComponent *target, std::string description);
    
    void onUpdate();
protected:
    void addPayment(PaymentAction* payment);
private:
    int _cash;
    std::list<PaymentAction*> _addedPayments;
    std::list<PaymentAction*> _history;
};