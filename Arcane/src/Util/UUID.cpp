#include "UUID.h"

#include <cstdlib>
#include <random>

static std::random_device s_randomDevice;
static std::mt19937_64 s_engine(s_randomDevice());
static std::uniform_int_distribution<uint64_t> s_uniformDistribution;

Arcane::UUID::UUID() : m_UUID(s_uniformDistribution(s_engine)) {}

Arcane::UUID::UUID(uint64_t uuid) : m_UUID(uuid) {}

std::string Arcane::UUID::UUID::ToString() const
{
   char buffer[17]; // 16 hex digits + null terminator
   _ui64toa_s(m_UUID, buffer, sizeof(buffer), 16); // Convert to hexadecimal string
   return std::string(buffer);
}
