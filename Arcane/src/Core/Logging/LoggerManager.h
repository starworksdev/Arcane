#pragma once

#include <functional>
#include <memory>
#include <string>

#include "ILogger.h"
#include "Util/Singleton.h"
#include "Util/StringUtil.h"

namespace Arcane
{
   class LoggerManager : public Singleton<LoggerManager>
   {
   public:
      static constexpr const wchar_t* DEFAULT_CORE_LOGGER_NAME = L"main";
      static constexpr const wchar_t* DEFAULT_APPLICATION_LOGGER_NAME = L"app";

      using LoggerPtr = std::unique_ptr<ILogger, std::function<void(ILogger*)>>;

      static bool Initialize()
      {
         if (!AllocConsole())
            return false;
         freopen_s((FILE**) stdout, "CONOUT$", "w", stdout);
         freopen_s((FILE**) stderr, "CONOUT$", "w", stderr);
         freopen_s((FILE**) stdin, "CONIN$", "r", stdin);
         return true;
      }

      static ILogger& GetCoreLogger() { return *(GetInstance().m_coreLogger); }

      template <typename Deleter = LoggerDeleter>
      static void SetCoreLogger(ILogger* newLogger, Deleter deleter = Deleter())
      {
         GetInstance().m_coreLogger = LoggerPtr(newLogger, deleter);
      }

      static bool HasCoreLogger() { return GetInstance().m_coreLogger != nullptr; }

      static ILogger& GetApplicationLogger() { return *(GetInstance().m_applicationLogger); }

      template <typename Deleter = LoggerDeleter>
      static void SetApplicationLogger(ILogger* newLogger, Deleter deleter = Deleter())
      {
         GetInstance().m_applicationLogger = LoggerPtr(newLogger, deleter);
      }

      static bool HasApplicationLogger() { return GetInstance().m_applicationLogger != nullptr; }

      static void Shutdown()
      {
         auto& instance = GetInstance();
         instance.m_coreLogger.reset();
         instance.m_applicationLogger.reset();
         FreeConsole();
      }

   private:
      LoggerManager();
      virtual ~LoggerManager() = default;

      LoggerManager(const LoggerManager&) = delete;
      LoggerManager& operator=(const LoggerManager&) = delete;

      LoggerPtr m_coreLogger;
      LoggerPtr m_applicationLogger;

      friend class Singleton<LoggerManager>;
   };
}

#define ARC_CORE_TRACE(message)   ::Arcane::LoggerManager::GetCoreLogger().Log(Arcane::Level::Trace,   ::Arcane::StringUtil::ToWString(message))
#define ARC_CORE_DEBUG(message)   ::Arcane::LoggerManager::GetCoreLogger().Log(Arcane::Level::Debug,   ::Arcane::StringUtil::ToWString(message))
#define ARC_CORE_INFO(message)    ::Arcane::LoggerManager::GetCoreLogger().Log(Arcane::Level::Info,    ::Arcane::StringUtil::ToWString(message))
#define ARC_CORE_WARN(message)    ::Arcane::LoggerManager::GetCoreLogger().Log(Arcane::Level::Warn,    ::Arcane::StringUtil::ToWString(message))
#define ARC_CORE_ERROR(message)   ::Arcane::LoggerManager::GetCoreLogger().Log(Arcane::Level::Error,   ::Arcane::StringUtil::ToWString(message))
#define ARC_CORE_FATAL(message)   ::Arcane::LoggerManager::GetCoreLogger().Log(Arcane::Level::Fatal,   ::Arcane::StringUtil::ToWString(message))

#define ARC_TRACE(message)        ::Arcane::LoggerManager::GetApplicationLogger().Log(Arcane::Level::Trace,  ::Arcane::StringUtil::ToWString(message))
#define ARC_DEBUG(message)        ::Arcane::LoggerManager::GetApplicationLogger().Log(Arcane::Level::Debug,  ::Arcane::StringUtil::ToWString(message))
#define ARC_INFO(message)         ::Arcane::LoggerManager::GetApplicationLogger().Log(Arcane::Level::Info,   ::Arcane::StringUtil::ToWString(message))
#define ARC_WARN(message)         ::Arcane::LoggerManager::GetApplicationLogger().Log(Arcane::Level::Warn,   ::Arcane::StringUtil::ToWString(message))
#define ARC_ERROR(message)        ::Arcane::LoggerManager::GetApplicationLogger().Log(Arcane::Level::Error,  ::Arcane::StringUtil::ToWString(message))
#define ARC_FATAL(message)        ::Arcane::LoggerManager::GetApplicationLogger().Log(Arcane::Level::Fatal,  ::Arcane::StringUtil::ToWString(message))