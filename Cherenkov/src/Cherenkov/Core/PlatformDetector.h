#pragma once
#ifdef _WIN32
	#ifdef _WIN64
		#ifndef CK_PLATFORM_WINDOWS
			#define CK_PLATFORM_WINDOWS
		#endif
	#else
		#error "x86 Builds not supported!" 
	#endif
#elif definied(__APPLE__) || defined(__MACH__)
	#include <TargetConditionals.h>
	#if TARGET_IPHONE_SIMULATOR == 1
		#error "IOS Simulation not supported."
	#elif TARGET_OS_IPHONE == 1
		#ifndef CK_PLATFORM_IOS
			#define CK_PLATFORM_IOS
		#endif		
		#error "IOS not supported!"
	#elif TARGET_OS_MAC == 1
		#ifndef CK_PLATFORM_MACOS
			#define CK_PLATFORM_MACOS
		#endif	
		#error "MacOS not supported!"
	#else
		#error "Unsupported Apple platform!"
	#endif
#elif defined(__ANDROID__)
	#ifndef CK_PLATFORM_ANDROID
		#define CK_PLATFORM_ANDROID
	#endif
	#error "Android not supported!"
#elif defined(__linux__)
	#ifndef CK_PLATFORM_LINUX
		#define CK_PLATFORM_LINUX
	#endif
	#error "Linux not supported!"
#else
	#error "Unknown platform!"
#endif
