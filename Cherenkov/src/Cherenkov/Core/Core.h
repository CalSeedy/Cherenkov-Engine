#pragma once

#include <memory>

#ifdef _WIN32
	#ifdef _WIN64
		#define CK_PLATOFRM_WINDOWS
	#else
		#error "x86 Builds not supported!" 
	#endif
#elif definied(__APPLE__) || defined(__MACH__)
	#include <TargetConditionals.h>
	#if TARGET_IPHONE_SIMULATOR == 1
		#error "IOS Simulation not supported."
	#elif TARGET_OS_IPHONE == 1
		#define CK_PLATFORM_IOS
		#error "IOS not supported!"
	#elif TARGET_OS_MAC == 1
		#define CK_PLATFORM_MACOS
		#error "MacOS not supported!"
	#else
		#error "Unsupported Apple platform!"
	#endif
#elif defined(__ANDROID__)
	#define CK_PLATFORM_ANDROID
	#error "Android not supported!"
#elif defined(__linux__)
	#define CK_PLATFORM_LINUX
	#error "Linux not supported!"
#else
	#error "Unknown platform!"
#endif

#ifdef CK_DEBUG
	#if defined(CK_PLATFORM_WINDOWS)
		#define CK_DEBUGBREAK() __debugbreak()
	#elif defined(CK_PLATFORM_LINUX)
		#include <signal.h>
		#define CK_DEBUGBREAK() raise(SIGTRAP)
	#else
		#error "Platform debugbreak is not supported!"
	#endif
#else
	#define CK_DEBUGBREAK() 
#endif // CK_DEBUG


#ifdef CK_ENABLE_ASSERTS
	#define CK_ASSERT(x, ...){if (!(x)){CK_ERROR("Assertion Failed!: (0)", __VA_ARGS__); CK_DEBUGBREAK();}}
	#define CK_CORE_ASSERT(x, ...){if (!(x)){CK_CORE_ERROR("Assertion Failed!: (0)", __VA_ARGS__); CK_DEBUGBREAK();}}
#else
	#define CK_ASSERT(x, ...)
	#define CK_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)
#define CK_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Cherenkov {
	template <typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args) {
		return std::make_unique<T>(std::forward<Args>(args)...);
	}
	template <typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args) {
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}