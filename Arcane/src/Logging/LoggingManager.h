#pragma once

#include <functional>
#include <memory>
#include <string>

#include "LoggingService.h"
#include "Util/Singleton.h"
#include "Util/StringUtil.h"

namespace Arcane
{
   class LoggingManager : public Singleton<LoggingManager>
   {
   public:
      static constexpr const wchar_t* DEFAULT_CORE_LOGGER_NAME = L"ARCANE";
      static constexpr const wchar_t* DEFAULT_APPLICATION_LOGGER_NAME = L"APP";

      using LoggerPtr = std::unique_ptr<LoggingService, std::function<void(LoggingService*)>>;

      static LoggingService& GetCoreLogger() { return *(GetInstance().m_coreLogger); }

      template <typename Deleter = LoggerDeleter>
      static void SetCoreLogger(LoggingService* newLogger, Deleter deleter = Deleter())
      {
         GetInstance().m_coreLogger = LoggerPtr(newLogger, deleter);
      }

      static bool HasCoreLogger() { return GetInstance().m_coreLogger != nullptr; }

      static LoggingService& GetApplicationLogger() { return *(GetInstance().m_applicationLogger); }

      template <typename Deleter = LoggerDeleter>
      static void SetApplicationLogger(LoggingService* newLogger, Deleter deleter = Deleter())
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
      LoggingManager();
      virtual ~LoggingManager() = default;

      LoggingManager(const LoggingManager&) = delete;
      LoggingManager& operator=(const LoggingManager&) = delete;

      LoggerPtr m_coreLogger;
      LoggerPtr m_applicationLogger;

      friend class Singleton<LoggingManager>;
   };
}

#define ARC_CORE_TRACE(message) \
   ARC_EXPAND_MACRO(ARC_ASSERT(&::Arcane::LoggingManager::GetCoreLogger(), "Invalid core logger; initialize logging system first.")); \
   ::Arcane::LoggingManager::GetCoreLogger().Log(Arcane::Level::Trace,    ::Arcane::StringUtil::ToWString(message))
#define ARC_CORE_DEBUG(message) \
   ARC_EXPAND_MACRO(ARC_ASSERT(&::Arcane::LoggingManager::GetCoreLogger(), "Invalid core logger; initialize logging system first.")); \
   ::Arcane::LoggingManager::GetCoreLogger().Log(Arcane::Level::Debug,    ::Arcane::StringUtil::ToWString(message))
#define ARC_CORE_INFO(message) \
   ARC_EXPAND_MACRO(ARC_ASSERT(&::Arcane::LoggingManager::GetCoreLogger(), "Invalid core logger; initialize logging system first.")); \
   ::Arcane::LoggingManager::GetCoreLogger().Log(Arcane::Level::Info,    ::Arcane::StringUtil::ToWString(message))
#define ARC_CORE_WARN(message) \
   ARC_EXPAND_MACRO(ARC_ASSERT(&::Arcane::LoggingManager::GetCoreLogger(), "Invalid core logger; initialize logging system first.")); \
   ::Arcane::LoggingManager::GetCoreLogger().Log(Arcane::Level::Warn,    ::Arcane::StringUtil::ToWString(message))
#define ARC_CORE_ERROR(message) \
   ARC_EXPAND_MACRO(ARC_ASSERT(&::Arcane::LoggingManager::GetCoreLogger(), "Invalid core logger; initialize logging system first.")); \
   ::Arcane::LoggingManager::GetCoreLogger().Log(Arcane::Level::Error,    ::Arcane::StringUtil::ToWString(message))
#define ARC_CORE_FATAL(message) \
   ARC_EXPAND_MACRO(ARC_ASSERT(&::Arcane::LoggingManager::GetCoreLogger(), "Invalid core logger; initialize logging system first.")); \
   ::Arcane::LoggingManager::GetCoreLogger().Log(Arcane::Level::Fatal,    ::Arcane::StringUtil::ToWString(message))

#define ARC_TRACE(message) \
   ARC_EXPAND_MACRO(ARC_ASSERT(&::Arcane::LoggingManager::GetApplicationLogger(), "Invalid application logger; initialize logging system first.")); \
   ::Arcane::LoggingManager::GetApplicationLogger().Log(Arcane::Level::Trace, ::Arcane::StringUtil::ToWString(message))
#define ARC_DEBUG(message) \
   ARC_EXPAND_MACRO(ARC_ASSERT(&::Arcane::LoggingManager::GetApplicationLogger(), "Invalid application logger; initialize logging system first.")); \
   ::Arcane::LoggingManager::GetApplicationLogger().Log(Arcane::Level::Debug, ::Arcane::StringUtil::ToWString(message))
#define ARC_INFO(message) \
   ARC_EXPAND_MACRO(ARC_ASSERT(&::Arcane::LoggingManager::GetApplicationLogger(), "Invalid application logger; initialize logging system first.")); \
   ::Arcane::LoggingManager::GetApplicationLogger().Log(Arcane::Level::Info,  ::Arcane::StringUtil::ToWString(message))
#define ARC_WARN(message) \
   ARC_EXPAND_MACRO(ARC_ASSERT(&::Arcane::LoggingManager::GetApplicationLogger(), "Invalid application logger; initialize logging system first.")); \
   ::Arcane::LoggingManager::GetApplicationLogger().Log(Arcane::Level::Warn,  ::Arcane::StringUtil::ToWString(message))
#define ARC_ERROR(message) \
   ARC_EXPAND_MACRO(ARC_ASSERT(&::Arcane::LoggingManager::GetApplicationLogger(), "Invalid application logger; initialize logging system first.")); \
   ::Arcane::LoggingManager::GetApplicationLogger().Log(Arcane::Level::Error, ::Arcane::StringUtil::ToWString(message))
#define ARC_FATAL(message) \
   ARC_EXPAND_MACRO(ARC_ASSERT(&::Arcane::LoggingManager::GetApplicationLogger(), "Invalid application logger; initialize logging system first.")); \
   ::Arcane::LoggingManager::GetApplicationLogger().Log(Arcane::Level::Fatal, ::Arcane::StringUtil::ToWString(message))
