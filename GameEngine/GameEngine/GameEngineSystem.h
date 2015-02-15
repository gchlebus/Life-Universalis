#pragma once

#ifdef _WIN32
  #ifdef GameEngine_EXPORTS
    #define GAMEENGINE_EXPORT __declspec(dllexport)
  #else
    #define GAMEENGINE_EXPORT __declspec(dllimport)
  #endif
#else
  #define GAMEENGINE_EXPORT
#endif
