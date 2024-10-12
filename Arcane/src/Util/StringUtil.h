#pragma once

#include <format>
#include <string>
#include <vector>

#include "Common.h"

namespace Arcane
{
   namespace StringUtil
   {
      const std::string EMPTY_STRING = "";
      const std::wstring EMPTY_WSTRING = L"";

      std::string ToLower(const std::string& str);
      std::wstring ToLower(const std::wstring& str);

      std::string ToUpper(const std::string& str);
      std::wstring ToUpper(const std::wstring& str);

      int32_t Compare(const std::string& str1, const std::string& str2);
      int32_t Compare(const std::wstring& str1, const std::wstring& str2);

      std::string Trim(const std::string& str);
      std::wstring Trim(const std::wstring& str);

      char* ToChar(const std::string& str);
      wchar_t* ToWChar(const std::wstring& str);

      std::string FromChar(const char* str);
      std::wstring FromWChar(const wchar_t* str);

      std::vector<std::string> Split(const std::string& str, const std::string& delimiters);
      std::vector<std::wstring> Split(const std::wstring& str, const std::wstring& delimiters);

      std::string Replace(const std::string& str, const std::string& find, const std::string& replace);
      std::wstring Replace(const std::wstring& str, const std::wstring& find, const std::wstring& replace);

      template <typename T>
      std::string ToString(T value)
      {
         if constexpr (std::is_same_v<T, std::wstring>)
         {
            int32_t size = WideCharToMultiByte(CP_UTF8, 0, value.c_str(), -1, NULL, 0, NULL, NULL);
            std::string result(size, 0);
            WideCharToMultiByte(CP_UTF8, 0, value.c_str(), -1, result.data(), size, NULL, NULL);
            return result;
         }
         else if constexpr (std::is_floating_point_v<T>)
         {
            return std::format("{:.{}g}", value, std::numeric_limits<T>::max_digits10);
         }
         else if constexpr (std::is_same_v<T, const char*>)
         {
            return std::string(value);
         }
         else if constexpr (std::is_same_v<T, std::string>)
         {
            return value;
         }
         else
         {
            return std::format("{}", value);
         }
      }

      template <typename T>
      std::wstring ToWString(T value)
      {
         if constexpr (std::is_same_v<T, std::string>)
         {
            int32_t size = MultiByteToWideChar(CP_UTF8, 0, value.c_str(), -1, NULL, 0);
            std::wstring result(size, 0);
            MultiByteToWideChar(CP_UTF8, 0, value.c_str(), -1, result.data(), size);
            return result;
         }
         else if constexpr (std::is_floating_point_v<T>)
         {
            return std::format(L"{:.{}g}", value, std::numeric_limits<T>::max_digits10);
         }
         else if constexpr (std::is_same_v<T, const char*>)
         {
            int32_t size = MultiByteToWideChar(CP_UTF8, 0, value, -1, NULL, 0);
            std::wstring result(size, 0);
            MultiByteToWideChar(CP_UTF8, 0, value, -1, result.data(), size);
            return result;
         }
         else if constexpr (std::is_same_v<T, std::wstring>)
         {
            return value;
         }
         else
         {
            return std::format(L"{}", value);
         }
      }
   } // namespace StringUtil
} // namespace Arcane
