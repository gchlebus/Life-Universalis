#pragma once

#ifdef _WIN32
  #ifdef LIFEUNIVERSALISEXPORTS
    #define LIFEUNIVERSALIS_EXPORT __declspec(dllexport)
  #else
    #define LIFEUNIVERSALIS_EXPORT __declspec(dllimport)
  #endif
#else
  #define LIFEUNIVERSALIS_EXPORT
#endif
