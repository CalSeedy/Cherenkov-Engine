#pragma once
#include "ckpch.h"

#include <memory>

#ifdef CK_PLATFORM_WINDOWS
#if CK_IS_DLL
	#ifdef CK_BUILD_DLL
		#define CK_API __declspec(dllexport)
	#else
		#define CK_API __declspec(dllimport)
	#endif
#else
	#define CK_API 
#endif
#else
	#error Engine only supports Windows!
#endif

#ifdef CK_ENABLE_ASSERTS
	#define CK_ASSERT(x, ...){if (!(x)){CK_ERROR("Assertion Failed!: (0)", __VA_ARGS__);__debugbreak();}}
	#define CK_CORE_ASSERT(x, ...){if (!(x)){CK_CORE_ERROR("Assertion Failed!: (0)", __VA_ARGS__);__debugbreak();}}
#else
	#define CK_ASSERT(x, ...)
	#define CK_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)
#define CK_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Cherenkov {
	template <typename T>
	using Scope = std::unique_ptr<T>;
	template <typename T>
	using Ref = std::shared_ptr<T>;
}