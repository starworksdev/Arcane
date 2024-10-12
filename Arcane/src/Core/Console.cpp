#include "Console.h"

#include <iostream>

std::once_flag Arcane::Console::m_initFlag;
HANDLE Arcane::Console::m_hConsole;

bool Arcane::Console::Initialize(const std::wstring& title, int width, int height)
{
   static bool initialized = false;
   std::call_once(m_initFlag, [&]()
   {
      if (AllocConsole())
      {
         freopen_s((FILE**) stdout, "CONOUT$",  "w", stdout);
         freopen_s((FILE**) stderr, "CONOUT$",  "w", stderr);
         freopen_s((FILE**) stdin,  "CONIN$",   "r", stdin);
         m_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

         CONSOLE_SCREEN_BUFFER_INFO csbi;
         GetConsoleScreenBufferInfo(m_hConsole, &csbi);
         SMALL_RECT windowSize = { 0, 0, static_cast<SHORT>(width - 1), static_cast<SHORT>(height - 1) };
         SetConsoleWindowInfo(m_hConsole, TRUE, &windowSize);
         COORD bufferSize = { static_cast<SHORT>(width), static_cast<SHORT>(height) };
         SetConsoleScreenBufferSize(m_hConsole, bufferSize);

         initialized = true;
      }
   });
   return initialized;
}

void Arcane::Console::Output(const std::string& msg)
{
   std::cout << msg << std::endl;
}

void Arcane::Console::Output(const char* msg)
{
   std::cout << msg << std::endl;
}

void Arcane::Console::OutputW(const std::wstring& msg)
{
   std::wcout << msg << std::endl;
}

void Arcane::Console::OutputW(const wchar_t* msg)
{
   std::wcout << msg << std::endl;
}

void Arcane::Console::Error(const std::string& msg)
{
   std::cerr << msg << std::endl;
}

void Arcane::Console::Error(const char* msg)
{
   std::cerr << msg << std::endl;
}

void Arcane::Console::ErrorW(const std::wstring& msg)
{
   std::wcerr << msg << std::endl;
}

void Arcane::Console::ErrorW(const wchar_t* msg)
{
   std::wcerr << msg << std::endl;
}

void Arcane::Console::SetTitle(const std::wstring& title)
{
   if (m_hConsole)
      SetConsoleTitle(title.c_str());
}

void Arcane::Console::SetTextColor(WORD color)
{
   if (m_hConsole)
      SetConsoleTextAttribute(m_hConsole, color);
}
