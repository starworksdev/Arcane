#pragma once

#ifdef ARCANE_TEST_EXPORTS
   #define ARC_API extern "C" __declspec(dllexport)
#else
   #define ARC_API extern "C" __declspec(dllimport)
#endif

#include "Common.h"
#include "Core/Application.h"
