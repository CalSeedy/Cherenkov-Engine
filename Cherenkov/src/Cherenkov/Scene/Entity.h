#pragma once
#include "Cherenkov/Scene/Scene.h"

#include <entt/entt.hpp>

namespace Cherenkov { 

	class Entity {
		entt::entity m_EntityID{ 0 };
		Scene* m_Scene = nullptr;
	public:
		Entity() = default;
		Entity(entt::entity eID, Scene* scene) : m_EntityID{ eID }, m_Scene{ scene } {}
		Entity(const Entity& other) = default;
		~Entity() = default;

		template<typename... Ts>
		bool has() {
			return m_Scene->m_Registry.all_of<Ts ...>(m_EntityID);
		}

		template<typename T, typename... Args>
		T& add(Args&&... args) {
			CK_CORE_ASSERT(!has<T>(), "Entity already has component!");

			return m_Scene->m_Registry.emplace<T>(m_EntityID, std::forward<Args>(args)...);
		}

		template<typename... Ts>
		decltype(auto) get() {
			CK_CORE_ASSERT(has<Ts ...>(), "Entity does not have component(s)!");
			return m_Scene->m_Registry.get<Ts ...>(m_EntityID);
		}

		template<typename T>
		auto remove() {
			CK_CORE_ASSERT(has<T>(), "Entity does not have component(s)!");
			return m_Scene->m_Registry.remove<T>(m_EntityID);
		}

		operator bool() const { return (uint32_t)m_EntityID != 0; }
	};

}