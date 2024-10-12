#pragma once

#include <string>

// Version components
#define LOOM_VERSION_MAJOR 1
#define LOOM_VERSION_MINOR 0
#define LOOM_VERSION_PATCH 0

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

#define LOOM_VERSION_STRING "v" TOSTRING(LOOM_VERSION_MAJOR) "." TOSTRING(LOOM_VERSION_MINOR) "." TOSTRING(LOOM_VERSION_PATCH)

#define LOOM_VERSION_AT_LEAST(major, minor, patch) \
    ((LOOM_VERSION_MAJOR > (major)) || \
    (LOOM_VERSION_MAJOR == (major) && LOOM_VERSION_MINOR > (minor)) || \
    (LOOM_VERSION_MAJOR == (major) && LOOM_VERSION_MINOR == (minor) && LOOM_VERSION_PATCH >= (patch)))

inline int GetLoomVersionMajor() { return LOOM_VERSION_MAJOR; }
inline int GetLoomVersionMinor() { return LOOM_VERSION_MINOR; }
inline int GetLoomVersionPatch() { return LOOM_VERSION_PATCH; }

inline std::string GetLoomVersionString() { return LOOM_VERSION_STRING; }
