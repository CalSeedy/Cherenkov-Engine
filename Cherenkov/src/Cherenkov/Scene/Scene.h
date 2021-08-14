#pragma once

#include "Cherenkov/Core/TimeStep.h"

#include <entt/entt.hpp>

namespace Cherenkov {
	class Entity;

	class Scene {
		entt::registry m_Registry;
		uint32_t m_VpWidth = 0;
		uint32_t m_VpHeight = 0;
		entt::entity m_PrimaryCamera{ entt::null };
		entt::entity m_SelectedEntity{ entt::null };

		template<typename T>
		void onComponentAdded(Entity& entity, T& component);

		template<typename T>
		void onComponentRemoved(Entity& entity);

		friend class Entity;
		friend class SceneHierarchy;
		friend class Serializer;
	public:
		Scene();
		~Scene();

		size_t cameraCount();

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
