//
//  CompoundLogger.cpp
//  GameEngine
//
//  Created by Pawel Sulik on 18/03/15.
//  Copyright (c) 2015 LifeUniversalis. All rights reserved.
//

#include "CompoundLogger.h"

CompoundLogger::~CompoundLogger()
{
    for(auto l : _loggers)
    {
        delete l;
    }
}
bool CompoundLogger::init()
{
    return true;
}

void CompoundLogger::close()
{
    
}

void CompoundLogger::log(std::string txt, WarningLevel lvl, std::string filename, int lineNum)
{
    for(auto log : _loggers)
    {
        log->log(txt, lvl, filename, lineNum);
    }
}

void CompoundLogger::addLogger(ILogger* logger)
{
    _loggers.push_back(logger);
}
