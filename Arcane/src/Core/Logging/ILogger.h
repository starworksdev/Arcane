#pragma once

#include <string>

#include "Level.h"

namespace Arcane
{
   class ILogger
   {
   public:
      virtual ~ILogger() = default;
      virtual void Log(Level level, const std::wstring& message) = 0;
      virtual void SetLevel(Level level) = 0;
   };

   struct LoggerDeleter
   {
      void operator()(ILogger* ptr) const { delete ptr; }
   };
}
