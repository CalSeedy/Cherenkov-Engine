#pragma once

#include <memory>

#include "Cherenkov/Core/PlatformDetector.h"

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
#define CK_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

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
