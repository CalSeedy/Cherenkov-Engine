#pragma once
#include "Cherenkov/Core/PlatformDetector.h"

#ifdef CK_PLATFORM_WINDOWS
	#ifndef NOMINMAX
		#define NOMINMAX
	#endif
#endif

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <sstream>
#include <array>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "Cherenkov/Core/Core.h"

#include "Cherenkov/Core/Log.h"

#include "Profiling/Instrumentor.h"
#ifdef CK_PLATFORM_WINDOWS
	#include <Windows.h>
#endif
