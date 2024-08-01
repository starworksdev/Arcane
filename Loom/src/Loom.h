#pragma once

#include <Windows.h>
#include <string>
#include <mutex>

namespace Loom
{
   typedef void (*EntryPointFunc)(HINSTANCE, int);

   HMODULE LoadDLL(const std::wstring& dllName, const std::wstring& funcName, EntryPointFunc& runGameFunc);
   void RunDLL(EntryPointFunc runGameFunc, HINSTANCE hInstance, int nCmdShow);
   void UnloadDLL(HMODULE hModule);
   std::wstring GetErrorMessage(DWORD errorCode);

   extern std::mutex dllMutex;
}