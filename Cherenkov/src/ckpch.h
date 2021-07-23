#pragma once

#include <algorithm>
#include <array>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <sstream>
#include <streambuf>
#include <string>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "Cherenkov/Core/Log.h"

#include "Profiling/Instrumentor.h"
#ifdef CK_PLATFORM_WINDOWS
	#include <Windows.h>
#endif