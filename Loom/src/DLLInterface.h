#pragma once

#include <mutex>
#include <string>

#include "Common.h"

typedef void (*EntryPointFunc)(HINSTANCE, int32_t);

HMODULE LoadDLL(const std::wstring& dllName, const std::wstring& funcName, EntryPointFunc& runGameFunc);
void RunDLL(EntryPointFunc runGameFunc, HINSTANCE hInstance, int32_t nCmdShow);
void UnloadDLL(HMODULE hModule);

std::wstring GetErrorMessage(DWORD errorCode);

extern std::mutex dllMutex;
