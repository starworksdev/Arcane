#pragma once

#include <iostream>
#include <mutex>
#include <string>

#include "Common.h"
#include "Format.h"
#include "ILogger.h"

namespace Arcane
{
   class Logger : public ILogger
   {
   public:
      static constexpr const wchar_t* DEFAULT_FORMAT = L"[{timestamp %H:%M:%S}] [{level}] [{name}] {message}";

      Logger(const std::wstring& name, const std::wstring& format = DEFAULT_FORMAT);
      virtual ~Logger() = default;

      void Log(Level level, const std::wstring& message) override;
      void SetLevel(Level level) override { m_level = level; }
      void SetFormat(const std::wstring& format);

   private:
      void OutputLog(const std::wstring& message) const;

      std::wstring m_name;
      Level m_level;
      Format m_format;
      mutable std::mutex m_mutex;
   };
}
