#pragma once

#include <optional>
#include <string>

namespace Arcane
{
   namespace StackTrace
   {
      struct CaptureDef
      {
         int maxFrames           = 16;
         bool resolveSymbols     = true;
         bool includeModuleInfo  = true;
         bool includeLineInfo    = true;
      };

      [[nodiscard]] std::optional<std::string> Capture(CaptureDef captureDef);
      [[nodiscard]] std::optional<std::string> Capture(int maxFrames = 16, bool resolveSymbols = true, bool includeModuleInfo = true, bool includeLineInfo = true);
   } // namespace StackTrace
} // namespace Arcane
