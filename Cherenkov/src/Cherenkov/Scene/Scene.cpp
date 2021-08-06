#include "ckpch.h"
#include "Cherenkov/Scene/Scene.h"

#include "Cherenkov/Scene/Components.h"

#include "Cherenkov/Renderer/Renderer2D.h"

#include "Cherenkov/Scene/Entity.h"
#include <glm/glm.hpp>

namespace Cherenkov {

	Scene::Scene() {
		Entity cam = createEntity("Scene Camera");
		cam.add<CameraComp>();
		m_PrimaryCamera = (entt::entity)cam;
		
	}

	Scene::~Scene() {

	}


	Entity Scene::getPrimaryCamera() {
		return { m_PrimaryCamera, this };
	}


	void Scene::setPrimaryCamera(Entity& camera) {
		CK_CORE_ASSERT(camera.has<CameraComp>(), "Entity does not have a CameraComp!");
		m_PrimaryCamera = camera;
	}

	Cherenkov::Entity Scene::getSelectedEntity() {
		return { m_SelectedEntity, this };
	}

	void Scene::setSelectedEntity(Entity& entity)	{
		m_SelectedEntity = entity;
	}

	void Scene::onUpdate(Timestep dt) {

		{
			m_Registry.view<ScriptComp>().each([=](auto entity, auto& script) {
				if (!script.Instance) {
					script.Instance = script.instantiateScript();
					script.Instance->m_Entity = Entity{ entity, this };
					script.Instance->onCreate();
				}

				script.Instance->onUpdate(dt);
			});
		}



		Camera* primaryCam = nullptr;
		glm::mat4 primaryTransform;
		auto group = m_Registry.group<CameraComp>(entt::get<TransformComp>);
		for (auto ent : group) {
			auto [camera, transform] = group.get<CameraComp, TransformComp>(ent);
			if (m_PrimaryCamera == Entity{ent, this}) {
				primaryCam = &camera.Camera;
				primaryTransform = transform.getTransform();
				break;
			}
		}

		if (primaryCam) {

			Renderer2D::beginScene(*primaryCam, primaryTransform);
			auto group = m_Registry.group<TransformComp>(entt::get<SpriteComp>);
			for (auto ent : group) {
				auto [transform, sprite] = group.get<TransformComp, SpriteComp>(ent);
				Renderer2D::Quad(transform.getTransform(), sprite.Colour);
			}
			Renderer2D::endScene();  
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

	void Scene::onViewportResize(uint32_t width, uint32_t height) {
		
		m_VpWidth = width;
		m_VpHeight = height;
		
		auto view = m_Registry.view<CameraComp>();
		for (auto ent : view) {
			auto& comp = view.get<CameraComp>(ent);
			if (!comp.fixedAspectRatio) {
				comp.Camera.setViewport(width, height);
			}
		}
	}

}
