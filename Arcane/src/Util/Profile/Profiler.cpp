#include "Profiler.h"

#include <sstream>
#include <iomanip>
#include <thread>

#include "Core/Logging/Logging.h"

void Arcane::Profiler::BeginSession(const std::string& name, const std::string& filepath)
{
	auto& instance = GetInstance();

	std::lock_guard lock(instance.m_Mutex);
	if (instance.m_CurrentSession)
	{
		if (LoggerManager::HasCoreLogger()) // Edge case: BeginSession() might be before Log::Init()
		{
			//ARC_CORE_ERROR("Profiler::BeginSession('{}') when session '{}' already open.", name, instance.m_CurrentSession->name);
		}
		instance.InternalEndSession();
	}
	instance.m_OutputStream.open(filepath);

	if (instance.m_OutputStream.is_open())
	{
		instance.m_CurrentSession = new InstrumentationSession({name});
		instance.WriteHeader();
	}
	else if (LoggerManager::HasCoreLogger()) // Edge case: BeginSession() might be before Log::Init()
	{
		//ARC_CORE_ERROR("Profiler could not open results file '{}'.", filepath);
	}
}

void Arcane::Profiler::EndSession()
{
	auto& instance = GetInstance();

	std::lock_guard lock(instance.m_Mutex);
	instance.InternalEndSession();
}

void Arcane::Profiler::WriteProfile(const ProfileResult& result)
{
	std::stringstream json;
	json << std::setprecision(3) << std::fixed;
	json << ",{";
	json << "\"cat\":\"function\",";
	json << "\"dur\":"		<< (result.elapsedTime.count()) << ',';
	json << "\"name\":\""	<< result.name << "\",";
	json << "\"ph\":\"X\",";
	json << "\"pid\":0,";
	json << "\"tid\":"		<< result.threadID << ",";
	json << "\"ts\":"			<< result.start.count();
	json << "}";

	auto& instance = GetInstance();

	std::lock_guard lock(instance.m_Mutex);
	if (instance.m_CurrentSession)
	{
		instance.m_OutputStream << json.str();
		instance.m_OutputStream.flush();
	}
}

Arcane::Profiler::Profiler() : m_CurrentSession(nullptr) {}

Arcane::Profiler::~Profiler() { EndSession(); }

void Arcane::Profiler::InternalEndSession()
{
	if (m_CurrentSession)
	{
		WriteFooter();
		m_OutputStream.close();
		delete m_CurrentSession;
		m_CurrentSession = nullptr;
	}
}

void Arcane::Profiler::WriteHeader()
{
	m_OutputStream << "{\"otherData\": {},\"traceEvents\":[{}";
	m_OutputStream.flush();
}

void Arcane::Profiler::WriteFooter()
{
	m_OutputStream << "]}";
	m_OutputStream.flush();
}
