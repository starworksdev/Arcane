#include "CommandLineParser.h"
#include <iostream>
#include <memory>

void Loom::AddOption(OptionHandlers& handlers, const std::wstring& option, OptionHandler handler)
{
   handlers[option] = handler;
}

void Loom::ParseCommandLine(int argc, LPWSTR* argv, const OptionHandlers& handlers, PositionalArguments& positionalArgs, std::wstring& errorMsg)
{
   for (int i = 0; i < argc; ++i)
   {
      std::wstring arg = argv[i];
      if (arg[0] == L'-')
      {
         auto it = handlers.find(arg);
         if (it != handlers.end())
         {
            if (i + 1 < argc)
            {
               it->second(argv[++i]);
            }
            else
            {
               errorMsg = L"Option " + arg + L" requires an argument.";
               return;
            }
         }
         else
         {
            errorMsg = L"Unknown option: " + arg;
            return;
         }
      }
      else
      {
         positionalArgs.push(arg);
      }
   }

   if (positionalArgs.empty())
   {
      errorMsg = L"No positional arguments provided.";
      return;
   }
}

const std::wstring Loom::PopPositionalArgument(PositionalArguments& args)
{
   if (args.empty())
   {
      throw std::out_of_range("No more positional arguments.");
   }

   std::wstring arg = args.top();
   args.pop();
   return arg;
}

size_t Loom::GetPositionalArgumentCount(const PositionalArguments& args)
{
   return args.size();
}

bool Loom::ProcessCommandLine(LPWSTR lpCmdLine, OptionHandlers& handlers, PositionalArguments& positionalArgs, std::wstring& errorMsg)
{
   int argc;
   LPWSTR* argv = CommandLineToArgvW(lpCmdLine, &argc);
   if (!argv)
   {
      errorMsg = L"Failed to parse command line.";
      return false;
   }
   std::unique_ptr<LPWSTR, decltype(&LocalFree)> argvGuard(argv, LocalFree);

   ParseCommandLine(argc, argv, handlers, positionalArgs, errorMsg);
   return errorMsg.empty();
}

int Loom::TryPopPositionalArgument(PositionalArguments& args, std::wstring& resultVar, const wchar_t* errorMsg)
{
   try
   {
      resultVar = Loom::PopPositionalArgument(args);
   }
   catch (const std::out_of_range&)
   {
      MessageBox(NULL, errorMsg, L"Error", MB_OK);
      return 1;
   }
   return 0;
}