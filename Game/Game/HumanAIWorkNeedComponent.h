//
//  HumanAIWorkNeedComponent.h
//  Game
//
//  Created by Pawel Sulik on 10/03/15.
//  Copyright (c) 2015 LifeUniversalis. All rights reserved.
//

#pragma once

#include <GameEngine.h>
#include "HumanAINeedComponent.h"
#include "DayTimeEntity.h"

class HumanAIWorkNeedComponent : public HumanAINeedComponent
{
public:
    HumanAIWorkNeedComponent();
    
    void onUpdate();
    
    void updatePriority();
    std::string getNeedName();
    
protected:
    GameDate estimateNextWorkStart();
};
