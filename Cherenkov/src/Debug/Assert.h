#pragma once

#include "Cherenkov/Core/Core.h"
#include "Cherenkov/Core/Log.h"

#include <filesystem>

#ifdef CK_ASSERTS

#define CK_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { CK##type##ERROR(msg, __VA_ARGS__); CK_DEBUGBREAK(); } }
#define CK_INTERNAL_ASSERT_WITH_MSG(type, check, ...) CK_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
#define CK_INTERNAL_ASSERT_NO_MSG(type, check) CK_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", CK_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

#define CK_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
#define CK_INTERNAL_ASSERT_GET_MACRO(...) CK_EXPAND_MACRO( CK_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, CK_INTERNAL_ASSERT_WITH_MSG, CK_INTERNAL_ASSERT_NO_MSG) )

#define CK_ASSERT(...) CK_EXPAND_MACRO( CK_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
#define CK_CORE_ASSERT(...) CK_EXPAND_MACRO( CK_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )
#else
#define CK_ASSERT(...)
#define CK_CORE_ASSERT(...)
#endif
