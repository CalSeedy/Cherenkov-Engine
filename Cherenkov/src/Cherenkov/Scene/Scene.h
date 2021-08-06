#pragma once
#include <entt/entt.hpp>

#include "Cherenkov/Core/TimeStep.h"


namespace Cherenkov {
	class Entity;

	class Scene {
		entt::registry m_Registry;
		uint32_t m_VpWidth = 0;
		uint32_t m_VpHeight = 0;
		entt::entity m_PrimaryCamera;
		entt::entity m_SelectedEntity{ entt::null };

		friend class Entity;
		friend class SceneHierarchy;
	public:
		Scene();
		~Scene();

		Entity getPrimaryCamera();
		void setPrimaryCamera(Entity& camera);

		Entity getSelectedEntity();
		void setSelectedEntity(Entity& entity);

		Entity createEntity(const std::string& name = "");
		void destroyEntity(Entity entity);

		void onUpdate(Timestep dt);
		void onViewportResize(uint32_t width, uint32_t height);
	};
}
