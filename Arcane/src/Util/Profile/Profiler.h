#pragma once

#include <fstream>
#include <mutex>
#include <string>

#include "Instrumentor.h"
#include "../Singleton.h"

namespace Arcane
{
	class Profiler : public Singleton<Profiler>
	{
	public:
		Profiler(const Profiler&) = delete;
		Profiler(Profiler&&) = delete;

		static void BeginSession(const std::string& name, const std::string& filepath = "results.json");
		static void EndSession();

		static void WriteProfile(const ProfileResult& result);

	private:
		Profiler();
		~Profiler();

		void InternalEndSession();

		void WriteHeader();
		void WriteFooter();

		std::mutex m_Mutex;
		InstrumentationSession* m_CurrentSession;
		std::ofstream m_OutputStream;

		friend class Singleton<Profiler>;
	};
}
