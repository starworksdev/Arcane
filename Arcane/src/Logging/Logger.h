#pragma once

#include <iostream>
#include <mutex>

#include "Common.h"
#include "Format.h"
#include "LoggingService.h"

namespace Arcane
{
   class Logger : public LoggingService
   {
   public:
      Logger(const std::wstring& name);
      virtual ~Logger() = default;

      void Log(Level level, const std::wstring& message, const std::source_location& location = std::source_location::current()) override;
      void SetLevel(Level level) override { m_level = level; }

   private:
      void OutputLog(const std::wstring& message) const;

      std::wstring m_name;
      Level m_level;
      Format m_format;
      bool m_colorizeMessages;
      mutable std::mutex m_mutex;
   };
}
