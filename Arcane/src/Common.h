#pragma once

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#define NOMINMAX
#include <Windows.h>
#ifdef min
   #undef min
#endif
#ifdef max
   #undef max
#endif

#ifndef GET_X_LPARAM
   #define GET_X_LPARAM(lp) ((int)(short)LOWORD(lp))
#endif

#ifndef GET_Y_LPARAM
   #define GET_Y_LPARAM(lp) ((int)(short)HIWORD(lp))
#endif

#ifdef ARC_BUILD_DEBUG
   #define ARC_DEBUGBREAK() __debugbreak()
   #define ARC_ENABLE_ASSERTS
#else
   #define ARC_DEBUGBREAK()
#endif

#define ARC_EXPAND_MACRO(x) x
#define ARC_STRINGIFY_MACRO(x) #x

#include <cstdint>

using float32_t   =  float;
using float64_t   =  double;

#include "Core/Assert.h"
#include "Logging/Logging.h"
