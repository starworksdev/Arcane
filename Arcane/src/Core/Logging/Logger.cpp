#include "Logger.h"
#include "Level.h"

#include <fstream>

Arcane::Logger::Logger(const std::wstring& name, const std::wstring& format) :
   ILogger(),
   m_name(name),
   m_level(Level::Trace),
   m_format(format)
{
}

void Arcane::Logger::Log(Level level, const std::wstring& message)
{
   if (level < m_level)
      return;

   std::lock_guard<std::mutex> lock(m_mutex);

   std::wstring levelStr = LevelToString(level);
   std::wstring formattedMessage = m_format.FormatMessageW(levelStr, m_name, message);
   OutputLog(formattedMessage);
}

void Arcane::Logger::OutputLog(const std::wstring& message) const
{
   std::wcout << message << std::endl;
}

void Arcane::Logger::SetFormat(const std::wstring& format)
{
   std::lock_guard<std::mutex> lock(m_mutex);  // Ensure thread safety
   m_format = Format(format);
}
