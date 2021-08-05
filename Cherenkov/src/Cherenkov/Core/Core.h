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
	#define CK_ASSERTS
#else
	#define CK_DEBUGBREAK() 
#endif // CK_DEBUG

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

#define CK_STRINGIFY_MACRO(x) #x
#define CK_EXPAND_MACRO(x) x
