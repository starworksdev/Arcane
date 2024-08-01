#pragma once

#include "Common.h"

namespace Arcane
{
	class UUID
	{
	public:
		UUID();
		UUID(uint64_t uuid);
		UUID(const UUID&) = default;

		operator uint64_t() const { return m_UUID; }
	private:
		uint64_t m_UUID;
	};
} // namespace Arcane

namespace std
{
	template  <typename T>
	struct hash;

	template <>
	struct hash<Arcane::UUID>
	{
		size_t operator()(const Arcane::UUID& uuid) const
		{
			return static_cast<uint64_t>(uuid);
		}
	};
} // namespace std
