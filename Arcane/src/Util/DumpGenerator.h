#pragma once

#include <windows.h>
#include <DbgHelp.h>
#include <string>

#pragma comment(lib, "Dbghelp.lib")

namespace Arcane
{
   namespace DumpGenerator
   {
      enum class DumpType
      {
         MiniDumpNormal          =  MiniDumpNormal,
         MiniDumpWithDataSegs    =  MiniDumpWithDataSegs,
         MiniDumpWithFullMemory  =  MiniDumpWithFullMemory,
         MiniDumpWithHandleData  =  MiniDumpWithHandleData,
         MiniDumpWithThreadInfo  =  MiniDumpWithThreadInfo,
      };

      bool MiniDump(EXCEPTION_POINTERS* exceptionInfo = nullptr, DumpType dumpType = DumpType::MiniDumpWithFullMemory, const std::string& customPath = "");
   } // namespace DumpGenerator

   LONG WINAPI UnhandledExceptionHandler(EXCEPTION_POINTERS* exceptionInfo);

   void RegisterDumpHandler();

} // namespace Arcane
