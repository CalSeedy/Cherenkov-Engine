#include "EntityProperties.h"

#include <imgui/imgui.h>
#include <glm/gtc/type_ptr.hpp>
#include "glm/gtx/matrix_decompose.hpp"
#include "glm/gtx/compatibility.hpp"
#include "glm/gtx/rotate_vector.hpp"

namespace Cherenkov {


	void EntityProperties::decomposeTransform(const glm::mat4& transform, glm::vec3& position, glm::vec3& rotation, glm::vec3& scale) {
		glm::quat orientation;
		glm::vec3 skew;
		glm::vec4 perspective;
		glm::decompose(transform, scale, orientation, position, skew, perspective);

		rotation = glm::degrees(glm::eulerAngles(orientation));

	}


	void EntityProperties::recalculateTransformation(glm::mat4& transform, const glm::vec3& position, glm::vec3& rotation, glm::vec3& scale) {
		if (scale.x < 0.0f) scale.x *= -1.0f;
		if (scale.y < 0.0f) scale.y *= -1.0f;
		if (scale.z < 0.0f) scale.z *= -1.0f;
		// assume angles are in degrees
		if (rotation.x > 90.0f) rotation.x -= 180.0f;
		if (rotation.y > 90.0f) rotation.y -= 180.0f;
		if (rotation.z > 180.0f) rotation.z -= 360.0f;

		if (rotation.x < -90.0f) rotation.x += 180.0f;
		if (rotation.y < -90.0f) rotation.y += 180.0f;
		if (rotation.z < -180.0f) rotation.z += 360.0f;

		glm::mat4 rotMatrix{ glm::rotate(glm::mat4{1.0f}, glm::radians(rotation.z), {0,0,1}) * glm::rotate(glm::mat4{1.0f}, glm::radians(rotation.y), {0,1,0}) * glm::rotate(glm::mat4{1.0f}, glm::radians(rotation.x), {1,0,0}) };
		transform = glm::translate(glm::mat4{ 1.0f }, position) * rotMatrix * glm::scale(glm::mat4{ 1.0f }, scale);
	}

	EntityProperties::EntityProperties(const Ref<Scene>& context) {
		setContext(context);
	}

	void EntityProperties::setContext(const Ref<Scene>& context) {
		m_Ctx = context;
	}

	void EntityProperties::onImGuiDraw() {
		ImGui::Begin("Properties");
		if (m_Ctx->getSelectedEntity()) drawComponents(m_Ctx->getSelectedEntity());
		else ImGui::Text("No entity selected!");
		ImGui::End();
	}

	void EntityProperties::drawCameraControls(Entity& camera) {
		ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_DefaultOpen;
		if (ImGui::TreeNodeEx((void*)typeid(CameraComp).hash_code(), flags, "Camera")) {

			auto& primaryCam = m_Ctx->getPrimaryCamera();
			bool primary = (camera == primaryCam);
			if (ImGui::Checkbox("Primary Camera: ", &primary)) {

				if (primary) m_Ctx->setPrimaryCamera(camera);

			}
			ImGui::SameLine();
			auto str = primaryCam.get<NameComp>().Name.c_str();
			ImGui::Text(str);

			auto& comp = camera.get<CameraComp>();
			bool& fixed = comp.fixedAspectRatio;
			SceneCamera& cam = comp.Camera;

			auto& type = cam.m_Type;
			const char* buff[] = { "Orthographic", "Perspective" };
			if (ImGui::BeginCombo("Projection", buff[(uint32_t)type])) {

				for (uint32_t i = 0; i < 2; i++) {

					bool selected = (i == (uint32_t)type);

					if (ImGui::Selectable(buff[i], selected)) {
						cam.setType((ProjectionType)i);
						if (!selected) {
							if (type == ProjectionType::Orthographic) cam.setOrthographic(cam.m_OrthographicSize, cam.m_OrthographicNear, cam.m_OrthographicFar);
							else if (type == ProjectionType::Perspective) cam.setPerspective(cam.m_PerspectiveFOV, cam.m_PerspectiveNear, cam.m_PerspectiveFar);
							else CK_CORE_ASSERT(false, "Unknown projection type!");
						}
					}

					if (selected) ImGui::SetItemDefaultFocus();
				}


				ImGui::EndCombo();
			}

			bool changed = false;
			if (ImGui::DragFloat("Aspect Ratio", &cam.m_AspectRatio)) changed = true;
			if (type == ProjectionType::Orthographic) {
				if (ImGui::DragFloat("Size", &cam.m_OrthographicSize)) changed = true;
				if (ImGui::DragFloat("Near", &cam.m_OrthographicNear)) changed = true;
				if (ImGui::DragFloat("Far", &cam.m_OrthographicFar)) changed = true;
			}
			else if (type == ProjectionType::Perspective) {
				if (ImGui::DragFloat("FOV", &cam.m_PerspectiveFOV)) changed = true;
				if (ImGui::DragFloat("Near", &cam.m_PerspectiveNear)) changed = true;
				if (ImGui::DragFloat("Far", &cam.m_PerspectiveFar)) changed = true;
			}

			if (changed) cam.recalculate();

			ImGui::Checkbox("Fixed Aspect Ratio", &fixed);

			ImGui::TreePop();
		}
	}

	void EntityProperties::drawComponents(Entity entity) {
		auto& tag = entity.get<NameComp>().Name;
		char buff[256];
		memset(buff, 0, sizeof(buff));
		strcpy_s(buff, tag.c_str());
		if (ImGui::InputText("Name", buff, sizeof(buff))) {
			tag = std::string(buff);
		}

		ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_OpenOnArrow;
		if (entity.has<CameraComp>()) {
			drawCameraControls(entity);
		}

		if (entity.has<SpriteComp>()) {
			if (ImGui::TreeNodeEx((void*)typeid(TransformComp).hash_code(), flags, "Sprite")) {
				auto& comp = entity.get<SpriteComp>();

				ImGui::ColorEdit4("Colour", glm::value_ptr(comp.Colour));

				ImGui::TreePop();
			}
		}

		if (entity.has<TransformComp>()) {
			

			if (ImGui::TreeNodeEx((void*)typeid(TransformComp).hash_code(), flags, "Transform")) {

				auto& transform = entity.get<TransformComp>().Transform;
				glm::vec3 pos, scale, angles;
				decomposeTransform(transform, pos, angles, scale);
				bool changed = false;

				if (ImGui::DragFloat2("Scale", glm::value_ptr(scale), 0.1f)) changed = true;

				if (ImGui::DragFloat3("Position", glm::value_ptr(pos), 0.1f)) changed = true;

				if (ImGui::DragFloat3("Rotation", glm::value_ptr(angles), 0.1f)) changed = true;

				if (changed) recalculateTransformation(transform, pos, angles, scale);

				ImGui::TreePop();
			}
		}
	}

}
