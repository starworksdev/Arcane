#include "Logger.h"

#include <fstream>

#include "Core/Console.h"
#include "Level.h"

Arcane::Logger::Logger(const std::wstring& name) :
   LoggingService(),
   m_name(name),
   m_level(Level::Trace),
   m_format(),
   m_colorizeMessages(true)
{
}

void Arcane::Logger::Log(Level level, const std::wstring& message, const std::source_location& location)
{
   if (level < m_level)
      return;

   std::lock_guard<std::mutex> lock(m_mutex);

   std::wstring levelStr = LevelToString(level);
   std::wstring formattedMessage = m_format(levelStr, m_name, message, location);
   
   if (m_colorizeMessages)
   {
      switch (level)
      {
         case Level::Trace:
            AnsiColor::FormatMessage(formattedMessage, AnsiColor::FG_CYAN<std::wstring>());
            break;
         case Level::Debug:
            AnsiColor::FormatMessage(formattedMessage, AnsiColor::FG_GREEN<std::wstring>());
            break;
         case Level::Warn:
            AnsiColor::FormatMessage(formattedMessage, AnsiColor::FG_YELLOW<std::wstring>());
            break;
         case Level::Error:
            AnsiColor::FormatMessage(formattedMessage, AnsiColor::FG_RED<std::wstring>());
            break;
         case Level::Fatal:
            AnsiColor::FormatMessage(formattedMessage, AnsiColor::FG_WHITE<std::wstring>(), AnsiColor::BG_RED<std::wstring>());
            break;
         case Level::Info: __fallthrough;
         default:
            break;
      }
   }

   OutputLog(formattedMessage);
}

void Arcane::Logger::OutputLog(const std::wstring& message) const
{
   Console::OutputW(message);
}

