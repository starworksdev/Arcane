#include "Format.h"

#include <regex>

Arcane::Format::Format(const std::wstring& format) : m_format(format)
{
   ParseFormatString();
}

void Arcane::Format::ParseFormatString()
{
   std::wregex placeholderRegex(L"\\{([^\\{\\} ]+)(?: ([^\\{\\}]+))?\\}");
   std::wsmatch match;
   std::wstring::const_iterator searchStart(m_format.cbegin());

   while (std::regex_search(searchStart, m_format.cend(), match, placeholderRegex))
   {
      std::wstring placeholderName = match[1].str();
      std::wstring customFormat = match.size() > 2 ? match[2].str() : L"";
      std::wstring fullPlaceholder = L"{" + placeholderName + (customFormat.empty() ? L"" : L" " + customFormat) + L"}";

      m_placeholders.push_back(Placeholder(fullPlaceholder, customFormat, match.position()));
      searchStart = match.suffix().first;
   }
}

std::wstring Arcane::Format::FormatMessageW(const std::wstring& level, const std::wstring& name, const std::wstring& message) const
{
   std::wstring result = m_format;

   for (const auto& placeholder : m_placeholders)
   {
      std::wstring replacement;
      if (placeholder.name.find(L"{timestamp") != std::wstring::npos)
         replacement = GetCurrentTimestamp(placeholder.customFormat);
      else if (placeholder.name == TOKEN_LEVEL)
         replacement = level;
      else if (placeholder.name == TOKEN_NAME)
         replacement = name;
      else if (placeholder.name == TOKEN_MESSAGE)
         replacement = message;

      size_t pos = result.find(placeholder.name);
      while (pos != std::wstring::npos)
      {
         result.replace(pos, placeholder.name.length(), replacement);
         pos = result.find(placeholder.name, pos + replacement.length());
      }
   }

   return result;
}

std::wstring Arcane::Format::GetCurrentTimestamp(const std::wstring& format)
{
   std::time_t now = std::time(nullptr);
   std::tm* localTime = std::localtime(&now);
   wchar_t buffer[100];
   std::wcsftime(buffer, sizeof(buffer), format.empty() ? L"%Y-%m-%d %H:%M:%S" : format.c_str(), localTime);
   return buffer;
}