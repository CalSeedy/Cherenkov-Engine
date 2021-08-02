#include "ckpch.h"
#include "Cherenkov/Scene/Scene.h"

#include "Cherenkov/Scene/Components.h"
#include "Cherenkov/Scene/Entity.h"

#include "Cherenkov/Renderer/Renderer2D.h"

#include <glm/glm.hpp>

namespace Cherenkov {

	Scene::Scene() {
		entt::entity ent = m_Registry.create();

		m_Registry.emplace<TransformComp>(ent, glm::mat4(1.0f));
		if (m_Registry.all_of<TransformComp>(ent))
			TransformComp& transform = m_Registry.get<TransformComp>(ent);


		auto view = m_Registry.view<TransformComp>();
		for (auto entity : view)
		{
			TransformComp& transform = view.get<TransformComp>(entity);
		}
	}

	Scene::~Scene() {

	}

	void Scene::onUpdate(Timestep dt) {
		auto group = m_Registry.group<TransformComp>(entt::get<SpriteComp>);
		for (auto ent : group) {
			auto& [transform, sprite] = group.get<TransformComp, SpriteComp>(ent);
			Renderer2D::Quad(transform, sprite.Colour);
		}
	}
#define STR_IMPL(s)  #s
#define NO_NAME1(s)  STR_IMPL(s)
#define NO_NAME  NO_NAME1(__COUNTER__)
	Entity Scene::createEntity(const std::string& name) {
		Entity ent = { m_Registry.create(), this };
		name.empty() ? ent.add<NameComp>("Entity #" + std::string{NO_NAME}) : ent.add<NameComp>(name);
		ent.add<TransformComp>();
		return ent;
	}

}