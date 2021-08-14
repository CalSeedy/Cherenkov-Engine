#pragma once
#include "Scene.h"

#include "Cherenkov/Core/Core.h"

#include <filesystem>

namespace Cherenkov {

	class Serializer {

		Ref<Scene> m_Scene;

	public:

		Serializer(const Ref<Scene>& scene);

		void serialize(const std::filesystem::path& path);
		bool deserialize(const std::filesystem::path& path);

		void serializeRuntime(const std::filesystem::path& path);
		bool deserializeRuntime(const std::filesystem::path& path);
	};


}
