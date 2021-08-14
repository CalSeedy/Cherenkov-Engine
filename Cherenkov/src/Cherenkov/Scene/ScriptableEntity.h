#pragma once
#include "Cherenkov/Scene/Entity.h"

namespace Cherenkov {
	class ScriptableEntity {
		Entity m_Entity;
		friend class Scene;
	protected:
		virtual void onCreate() {}
		virtual void onUpdate(Timestep dt) {}
		virtual void onDestroy() {}

	public:
		virtual ~ScriptableEntity() = default;

		operator uint32_t() { return (uint32_t)m_Entity; }

		template<typename... Ts>
		decltype(auto) get() {
			return m_Entity.get<Ts ...>();
		}

		template<typename T>
		bool has() {
			return m_Entity.has<T>();
		}
	};
}
