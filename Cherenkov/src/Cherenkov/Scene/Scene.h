#pragma once
#include <entt/entt.hpp>

#include "Cherenkov/Core/TimeStep.h"

#include "Cherenkov/Scene/Entity.h"

namespace Cherenkov {
	class Scene {
		entt::registry m_Registry;
		Entity m_PrimaryCamera;
		uint32_t m_VpWidth = 0;
		uint32_t m_VpHeight = 0;

		friend class Entity;
		friend class SceneHierarchy;
	public:
		Scene();
		~Scene();

		void setPrimary(const Entity& cam);
		Entity& getPrimary() { return m_PrimaryCamera; }
		
		void onUpdate(Timestep dt);
		Entity createEntity(const std::string& name = "");

		void onViewportResize(uint32_t width, uint32_t height);
	};
}
