#pragma once

#include "Cherenkov/Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"


namespace Cherenkov {

	class CK_API Log
	{
	public:
		static void init();
		inline static std::shared_ptr<spdlog::logger>& getCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& getClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}


#define CK_CORE_TRACE(...)	::Cherenkov::Log::getCoreLogger()->trace(__VA_ARGS__)
#define CK_CORE_INFO(...)	::Cherenkov::Log::getCoreLogger()->info(__VA_ARGS__)
#define CK_CORE_WARN(...)	::Cherenkov::Log::getCoreLogger()->warn(__VA_ARGS__)
#define CK_CORE_ERROR(...)	::Cherenkov::Log::getCoreLogger()->error(__VA_ARGS__)
#define CK_CORE_FATAL(...)	::Cherenkov::Log::getCoreLogger()->fatal(__VA_ARGS__)

#define CK_TRACE(...)		::Cherenkov::Log::getClientLogger()->trace(__VA_ARGS__)
#define CK_INFO(...)		::Cherenkov::Log::getClientLogger()->info(__VA_ARGS__)
#define CK_WARN(...)		::Cherenkov::Log::getClientLogger()->warn(__VA_ARGS__)
#define CK_ERROR(...)		::Cherenkov::Log::getClientLogger()->error(__VA_ARGS__)
#define CK_FATAL(...)		::Cherenkov::Log::getClientLogger()->fatal(__VA_ARGS__)
