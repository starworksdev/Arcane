#pragma once

#include <string>
#include <unordered_map>

namespace Arcane
{
   enum class Level
   {
      Trace,
      Debug,
      Info,
      Warn,
      Error,
      Fatal,
      Off
   };

   inline const std::unordered_map<Level, std::wstring> LevelToStringMap =
   {
      { Level::Trace, L"TRACE" },
      { Level::Debug, L"DEBUG" },
      { Level::Info,  L"INFO"  },
      { Level::Warn,  L"WARN"  },
      { Level::Error, L"ERROR" },
      { Level::Fatal, L"FATAL" },
      { Level::Off,   L"OFF"   }
   };

   inline const std::unordered_map<std::wstring, Level> StringToLevelMap =
   {
      { L"TRACE", Level::Trace },
      { L"DEBUG", Level::Debug },
      { L"INFO",  Level::Info  },
      { L"WARN",  Level::Warn  },
      { L"ERROR", Level::Error },
      { L"FATAL", Level::Fatal },
      { L"OFF",   Level::Off   }
   };

   inline std::wstring LevelToString(Level level)
   {
      auto it = LevelToStringMap.find(level);
      if (it != LevelToStringMap.end())
         return it->second;
      return L"UNKNOWN";
   }

   inline Level StringToLevel(const std::wstring& levelStr)
   {
      auto it = StringToLevelMap.find(levelStr);
      if (it != StringToLevelMap.end())
         return it->second;
      return Level::Off;
   }
}
