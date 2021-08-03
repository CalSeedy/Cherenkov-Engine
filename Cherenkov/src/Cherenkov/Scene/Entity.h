#pragma once

#include <entt/entt.hpp>

namespace Cherenkov {
	class Scene;

	class Entity {
		entt::entity m_EntityID{ entt::null };
		Scene* m_Scene = nullptr;
	public:
		Entity() = default;
		Entity(entt::entity eID, Scene* scene) : m_EntityID{ eID }, m_Scene{ scene } {}
		Entity(const Entity& other) = default;
		~Entity() = default;

		const entt::entity getID() const { return m_EntityID; }

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

		operator bool() const { return m_EntityID != entt::null; }
		bool operator==(const Entity& other) { return m_EntityID == other.m_EntityID; }
		const bool operator==(const Entity& other) const { return m_EntityID == other.m_EntityID; }
	};

	class ScriptableEntity {
		Entity m_Entity;
		friend class Scene;
	protected:
		virtual void onCreate() {}
		virtual void onUpdate(Timestep dt) {}
		virtual void onDestroy() {}

	public:
		virtual ~ScriptableEntity() = default;

		template<typename... Ts>
		decltype(auto) get() {
			return m_Entity.get<Ts ...>();
		}
	};
}