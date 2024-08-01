#include "StringUtil.h"

#include <algorithm>
#include <cctype>
#include <cwctype>
#include <locale>
#include <string>
#include <vector>

#include "Common.h"

std::string Arcane::StringUtil::ToLower(const std::string& str)
{
   std::string lowerStr = str;
   std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
   return lowerStr;
}

std::wstring Arcane::StringUtil::ToLower(const std::wstring& str)
{
   std::wstring lowerStr = str;
   std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::towlower);
   return lowerStr;
}

std::string Arcane::StringUtil::ToUpper(const std::string& str)
{
   std::string upperStr = str;
   std::transform(upperStr.begin(), upperStr.end(), upperStr.begin(), ::toupper);
   return upperStr;
}

std::wstring Arcane::StringUtil::ToUpper(const std::wstring& str)
{
   std::wstring upperStr = str;
   std::transform(upperStr.begin(), upperStr.end(), upperStr.begin(), ::towupper);
   return upperStr;
}

int32_t Arcane::StringUtil::Compare(const std::string& str1, const std::string& str2)
{
   return str1.compare(str2);
}

int32_t Arcane::StringUtil::Compare(const std::wstring& str1, const std::wstring& str2)
{
   return str1.compare(str2);
}

std::string Arcane::StringUtil::Trim(const std::string& str)
{
   size_t first = str.find_first_not_of(' ');
   if (first == std::string::npos)
      return EMPTY_STRING;
   size_t last = str.find_last_not_of(' ');
   return str.substr(first, (last - first + 1));
}

std::wstring Arcane::StringUtil::Trim(const std::wstring& str)
{
   size_t first = str.find_first_not_of(L' ');
   if (first == std::wstring::npos)
      return EMPTY_WSTRING;
   size_t last = str.find_last_not_of(L' ');
   return str.substr(first, (last - first + 1));
}

char* Arcane::StringUtil::ToChar(const std::string& str)
{
   char* cstr = new char[str.length() + 1];
   std::strcpy(cstr, str.c_str());
   return cstr;
}

wchar_t* Arcane::StringUtil::ToWChar(const std::wstring& str)
{
   wchar_t* wcstr = new wchar_t[str.length() + 1];
   std::wcscpy(wcstr, str.c_str());
   return wcstr;
}

std::string Arcane::StringUtil::FromChar(const char* str)
{
   return std::string(str);
}

std::wstring Arcane::StringUtil::FromWChar(const wchar_t* str)
{
   return std::wstring(str);
}

std::vector<std::string> Arcane::StringUtil::Split(const std::string& str, const std::string& delimiters)
{
   std::vector<std::string> tokens;
   size_t start = 0, end = 0;
   while ((end = str.find_first_of(delimiters, start)) != std::string::npos)
   {
      if (end != start)
         tokens.push_back(str.substr(start, end - start));
      start = end + 1;
   }
   if (end != start)
      tokens.push_back(str.substr(start));
   return tokens;
}

std::vector<std::wstring> Arcane::StringUtil::Split(const std::wstring& str, const std::wstring& delimiters)
{
   std::vector<std::wstring> tokens;
   size_t start = 0, end = 0;
   while ((end = str.find_first_of(delimiters, start)) != std::wstring::npos)
   {
      if (end != start)
         tokens.push_back(str.substr(start, end - start));
      start = end + 1;
   }
   if (end != start)
      tokens.push_back(str.substr(start));
   return tokens;
}

std::string Arcane::StringUtil::Replace(const std::string& str, const std::string& find, const std::string& replace)
{
   std::string result = str;
   size_t pos = 0;
   while ((pos = result.find(find, pos)) != std::string::npos)
   {
      result.replace(pos, find.length(), replace);
      pos += replace.length();
   }
   return result;
}

std::wstring Arcane::StringUtil::Replace(const std::wstring& str, const std::wstring& find, const std::wstring& replace)
{
   std::wstring result = str;
   size_t pos = 0;
   while ((pos = result.find(find, pos)) != std::wstring::npos)
   {
      result.replace(pos, find.length(), replace);
      pos += replace.length();
   }
   return result;
}

std::string Arcane::StringUtil::ToString(const std::wstring& str)
{
   int32_t size = WideCharToMultiByte(CP_UTF8, 0, str.c_str(), -1, NULL, 0, NULL, NULL);
   char* buffer = new char[size];
   WideCharToMultiByte(CP_UTF8, 0, str.c_str(), -1, buffer, size, NULL, NULL);
   std::string result(buffer);
   delete[] buffer;
   return result;
}

std::wstring Arcane::StringUtil::ToWString(const std::string& str)
{
   int32_t size = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
   wchar_t* buffer = new wchar_t[size];
   MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, buffer, size);
   std::wstring result(buffer);
   delete[] buffer;
   return result;
}
