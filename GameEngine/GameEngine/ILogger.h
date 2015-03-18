//
//  ILogger.h
//  GameEngine
//
//  Created by Pawel Sulik on 18/03/15.
//  Copyright (c) 2015 LifeUniversalis. All rights reserved.
//

#pragma once
#include "GlobalHeaders.h"

enum GAMEENGINE_EXPORT WarningLevel
{
    WL_DEBUG = 0,
    WL_INFO = 1,
    WL_WARNING = 2,
    WL_ERROR = 3,
};

class GAMEENGINE_EXPORT ILogger
{
public:
    ILogger() : _filter(WL_DEBUG) { }
    virtual ~ILogger() { }
    
    virtual void log(std::string txt, WarningLevel lvl, std::string filename, int lineNum) = 0;
    void setFilter(WarningLevel lvl) { _filter = lvl; }
protected:
    WarningLevel _filter;
};
