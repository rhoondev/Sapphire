#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"

// Core log macros
#define SAPPHIRE_CORE_TRACE(...)    ::Sapphire::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define SAPPHIRE_CORE_INFO(...)     ::Sapphire::Log::GetCoreLogger()->info(__VA_ARGS__)
#define SAPPHIRE_CORE_WARN(...)     ::Sapphire::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define SAPPHIRE_CORE_ERROR(...)    ::Sapphire::Log::GetCoreLogger()->error(__VA_ARGS__)
#define SAPPHIRE_CORE_CRITICAL(...) ::Sapphire::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define SAPPHIRE_TRACE(...)         ::Sapphire::Log::GetClientLogger()->trace(__VA_ARGS__)
#define SAPPHIRE_INFO(...)          ::Sapphire::Log::GetClientLogger()->info(__VA_ARGS__)
#define SAPPHIRE_WARN(...)          ::Sapphire::Log::GetClientLogger()->warn(__VA_ARGS__)
#define SAPPHIRE_ERROR(...)         ::Sapphire::Log::GetClientLogger()->error(__VA_ARGS__)
#define SAPPHIRE_CRITICAL(...)      ::Sapphire::Log::GetClientLogger()->critical(__VA_ARGS__)

namespace Sapphire
{
	class SAPPHIRE_API Log
	{
	public:
		static void Init();
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

