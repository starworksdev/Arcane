#include "Loom.h"
#include <iostream>
#include <memory>
#include "Util/StringUtil.h"

std::mutex Loom::dllMutex;

HMODULE Loom::LoadDLL(const std::wstring& dllName, const std::wstring& funcName, EntryPointFunc& runGameFunc)
{
   std::lock_guard<std::mutex> lock(Loom::dllMutex);

   HMODULE hModule = LoadLibrary(dllName.c_str());
   if (!hModule)
   {
      DWORD error = GetLastError();
      std::wcerr << L"Failed to load " << dllName << L", error code: " << error << L" (" << GetErrorMessage(error) << L")" << std::endl;
      MessageBox(NULL, (L"Failed to load " + dllName + L": " + GetErrorMessage(error)).c_str(), L"Error", MB_OK);
      return nullptr;
   }

   runGameFunc = (EntryPointFunc) GetProcAddress(hModule, Arcane::StringUtil::ToString(funcName).c_str());
   if (!runGameFunc)
   {
      DWORD error = GetLastError();
      std::wcerr << L"Failed to find " << funcName << L" function in " << dllName << L", error code: " << error << L" (" << GetErrorMessage(error) << L")" << std::endl;
      MessageBox(NULL, (L"Failed to find " + funcName + L" function in " + dllName + L": " + GetErrorMessage(error)).c_str(), L"Error", MB_OK);
      FreeLibrary(hModule);
      return nullptr;
   }

   return hModule;
}

void Loom::RunDLL(EntryPointFunc runGameFunc, HINSTANCE hInstance, int nCmdShow)
{
   runGameFunc(hInstance, nCmdShow);

   MSG msg = { 0 };
   while (GetMessage(&msg, NULL, 0, 0))
   {
      TranslateMessage(&msg);
      DispatchMessage(&msg);

      if (msg.message == WM_QUIT)
         break;
   }
}

void Loom::UnloadDLL(HMODULE hModule)
{
   std::lock_guard<std::mutex> lock(Loom::dllMutex);

   if (hModule)
   {
      FreeLibrary(hModule);
   }
}

std::wstring Loom::GetErrorMessage(DWORD errorCode)
{
   LPWSTR messageBuffer = nullptr;
   size_t size = FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, errorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPWSTR)&messageBuffer, 0, NULL);
   std::wstring message(messageBuffer, size);
   LocalFree(messageBuffer);
   return message;
}
