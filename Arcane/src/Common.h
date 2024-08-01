#pragma once

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include <Windows.h>

#ifndef GET_X_LPARAM
   #define GET_X_LPARAM(lp) ((int)(short)LOWORD(lp))
#endif

#ifndef GET_Y_LPARAM
   #define GET_Y_LPARAM(lp) ((int)(short)HIWORD(lp))
#endif
