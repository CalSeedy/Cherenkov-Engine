#pragma once

#ifdef CK_PLATFORM_WINDOWS
	#ifdef CK_BUILD_DLL
		#define CK_API __declspec(dllexport)
	#else
		#define CK_API __declspec(dllimport)
	#endif
#else
	#error Engine only supports Windows!
#endif