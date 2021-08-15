#pragma once

#include <string>
#include <filesystem>

namespace Cherenkov {

	class FileDialogue {

	public:
		static std::string open(const char* filter);
		static std::string save(const char* filter);
	};
}
