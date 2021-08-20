#include "ckpch.h"
#include "Cherenkov/Scene/Scene.h"

#include "Cherenkov/Scene/Components.h"

#include "Cherenkov/Renderer/Renderer2D.h"

#include "Cherenkov/Scene/Entity.h"
#include <glm/glm.hpp>

namespace Cherenkov {

	Scene::Scene(const std::string& name) : m_Name{name} {}

	Scene::~Scene() {}

	size_t Scene::cameraCount() {
		auto view = m_Registry.view<CameraComp>();
		return view.size();
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

	void Scene::onUpdateRuntime(Timestep dt) {

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
				//Renderer2D::Quad(transform.getTransform(), sprite.Colour);
				Renderer2D::Sprite(transform.getTransform(), sprite, (int)ent);
			}
			Renderer2D::endScene();  
		}
	}

	static uint32_t counter = 0;

	Entity Scene::createEntity(const std::string& name) {
		Entity ent = { m_Registry.create(), this };
		name.empty() ? ent.add<NameComp>("Entity #" + std::to_string(counter)) : ent.add<NameComp>(name);
		ent.add<TransformComp>();
		counter++;
		return ent;
	}

	void Scene::destroyEntity(Entity entity) {
		m_Registry.destroy(entity);
	}

	void Scene::onUpdateEditor(EditorCamera& camera, Timestep dt) {
		Renderer2D::beginScene(camera);
			auto group = m_Registry.group<TransformComp>(entt::get<SpriteComp>);
			for (auto ent : group) {
				auto [transform, sprite] = group.get<TransformComp, SpriteComp>(ent);
				//Renderer2D::Quad(transform.getTransform(), sprite.Colour);
				Renderer2D::Sprite(transform.getTransform(), sprite, (int)ent);
			}
			Renderer2D::endScene();  
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


	template<typename T>
	void Scene::onComponentAdded(Entity& entity, T& component) { static_assert(false); }

	template<>
	void Scene::onComponentAdded<NameComp>(Entity& entity, NameComp& component) {

	}

	template<>
	void Scene::onComponentAdded<CameraComp>(Entity& entity, CameraComp& component) {
		if (cameraCount() == 1) m_PrimaryCamera = entity;
		if (m_VpWidth > 0 && m_VpHeight > 0)
			component.Camera.setViewport(m_VpWidth, m_VpHeight);
	}

	template<>
	void Scene::onComponentAdded<TransformComp>(Entity& entity, TransformComp& component) {
		onViewportResize(m_VpWidth, m_VpHeight);
	}

	template<>
	void Scene::onComponentAdded<SpriteComp>(Entity& entity, SpriteComp& component) {

	}

	template<>
	void Scene::onComponentAdded<ScriptComp>(Entity& entity, ScriptComp& component) {

	}

	template<typename T>
	void Scene::onComponentRemoved(Entity& entity) { static_assert(false); }

	template<>
	void Scene::onComponentRemoved<NameComp>(Entity& entity) {

	}

	template<>
	void Scene::onComponentRemoved<CameraComp>(Entity& entity) {
		if (cameraCount() == 0) m_PrimaryCamera = entt::null;
	}

	template<>
	void Scene::onComponentRemoved<TransformComp>(Entity& entity) {

	}

	template<>
	void Scene::onComponentRemoved<SpriteComp>(Entity& entity) {

	}

	template<>
	void Scene::onComponentRemoved<ScriptComp>(Entity& entity) {

	}

}
