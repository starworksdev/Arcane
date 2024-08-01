#include "Loom.h"
#include "CommandLineParser.h"
#include <Windows.h>
#include <memory>

static constexpr const wchar_t* ENTRY_POINT_FUNCTION_NAME = L"EntryPoint";

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
   _In_opt_ HINSTANCE hPrevInstance,
   _In_ LPWSTR    lpCmdLine,
   _In_ int       nCmdShow)
{
   Loom::OptionHandlers handlers;
   Loom::PositionalArguments positionalArgs;
   std::wstring errorMsg;

   if (!Loom::ProcessCommandLine(lpCmdLine, handlers, positionalArgs, errorMsg))
   {
      MessageBox(NULL, errorMsg.c_str(), L"Error", MB_OK);
      return 1;
   }

   if (Loom::GetPositionalArgumentCount(positionalArgs) < 1)
   {
      MessageBox(NULL, L"Usage: Loom.exe <ClientDLLName>", L"Error", MB_OK);
      return 1;
   }

   std::wstring dllName;
   if (Loom::TryPopPositionalArgument(positionalArgs, dllName, L"No valid DLL name provided.") != 0)
      return 1;

   Loom::EntryPointFunc runGameFunc;
   HMODULE hModule = Loom::LoadDLL(dllName, ENTRY_POINT_FUNCTION_NAME, runGameFunc);
   if (!hModule)
      return 1;

   Loom::RunDLL(runGameFunc, hInstance, nCmdShow);
   Loom::UnloadDLL(hModule);

   return 0;
}
