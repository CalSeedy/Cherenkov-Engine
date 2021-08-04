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
		if (m_Ctx->getSelected()) drawComponents(m_Ctx->getSelected());
		else ImGui::Text("No entity selected!");
		ImGui::End();
	}

	void EntityProperties::drawComponents(Entity entity) {
		auto& tag = entity.get<NameComp>().Name;
		char buff[256];
		memset(buff, 0, sizeof(buff));
		strcpy_s(buff, tag.c_str());
		if (ImGui::InputText("Name", buff, sizeof(buff))) {
			tag = std::string(buff);
		}

		if (entity.has<TransformComp>()) {
			ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_DefaultOpen;

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
