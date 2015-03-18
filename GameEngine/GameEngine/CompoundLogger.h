//
//  CompoundLogger.h
//  GameEngine
//
//  Created by Pawel Sulik on 18/03/15.
//  Copyright (c) 2015 LifeUniversalis. All rights reserved.
//

<<<<<<< Updated upstream
#ifndef GameEngine_CompoundLogger_h
#define GameEngine_CompoundLogger_h


#endif
=======
#pragma once
#include "GlobalHeaders.h"
#include "ILogger.h"

class GAMEENGINE_EXPORT CompoundLogger
{
public:
    ~CompoundLogger();
    bool init();
    void close();
    
    void log(std::string txt, WarningLevel lvl, std::string filename, int lineNum);
    
    void addLogger(ILogger* logger);
    
protected:
    std::vector<ILogger*> _loggers;
};
>>>>>>> Stashed changes
