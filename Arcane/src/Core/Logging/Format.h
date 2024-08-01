#pragma once

#include <string>
#include <vector>
#include <ctime>

namespace Arcane
{
   class Format
   {
   public:
      static constexpr const wchar_t* TOKEN_TIMESTAMP = L"{timestamp}";
      static constexpr const wchar_t* TOKEN_LEVEL     = L"{level}";
      static constexpr const wchar_t* TOKEN_NAME      = L"{name}";
      static constexpr const wchar_t* TOKEN_MESSAGE   = L"{message}";

      Format(const std::wstring& format);
      ~Format() = default;

      std::wstring FormatMessageW(const std::wstring& level, const std::wstring& name, const std::wstring& message) const;

   private:
      static std::wstring GetCurrentTimestamp(const std::wstring& format);
      void ParseFormatString();

      struct Placeholder
      {
         std::wstring name;
         std::wstring customFormat;
         size_t position;
      };

      std::wstring m_format;
      std::vector<Placeholder> m_placeholders;
   };
}
