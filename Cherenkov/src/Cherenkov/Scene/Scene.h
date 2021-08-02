#pragma once
#include <entt/entt.hpp>

#include "Cherenkov/Core/TimeStep.h"

namespace Cherenkov {
	class Entity;

	class Scene {
		entt::registry m_Registry;
		friend class Entity;
	public:
		Scene();
		~Scene();

		void onUpdate(Timestep dt);
		Entity createEntity(const std::string& name = "");
	};
}