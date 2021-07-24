#pragma once

#include "Cherenkov/Core/Core.h"

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>


namespace Cherenkov {

	class Log {
		static Ref<spdlog::logger> s_CoreLogger;
		static Ref<spdlog::logger> s_ClientLogger;
	public:
		static void init();
		inline static Ref<spdlog::logger>& getCoreLogger() { return s_CoreLogger; }
		inline static Ref<spdlog::logger>& getClientLogger() { return s_ClientLogger; }

	};

}

#define CK_CORE_TRACE(...)	::Cherenkov::Log::getCoreLogger()->trace(__VA_ARGS__)
#define CK_CORE_INFO(...)	::Cherenkov::Log::getCoreLogger()->info(__VA_ARGS__)
#define CK_CORE_WARN(...)	::Cherenkov::Log::getCoreLogger()->warn(__VA_ARGS__)
#define CK_CORE_ERROR(...)	::Cherenkov::Log::getCoreLogger()->error(__VA_ARGS__)
#define CK_CORE_FATAL(...)	::Cherenkov::Log::getCoreLogger()->critical(__VA_ARGS__)

#define CK_TRACE(...)		::Cherenkov::Log::getClientLogger()->trace(__VA_ARGS__)
#define CK_INFO(...)		::Cherenkov::Log::getClientLogger()->info(__VA_ARGS__)
#define CK_WARN(...)		::Cherenkov::Log::getClientLogger()->warn(__VA_ARGS__)
#define CK_ERROR(...)		::Cherenkov::Log::getClientLogger()->error(__VA_ARGS__)
#define CK_FATAL(...)		::Cherenkov::Log::getClientLogger()->critical(__VA_ARGS__)
