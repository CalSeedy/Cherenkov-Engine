#include "SceneHierarchy.h"

#include <imgui/imgui.h>

namespace Cherenkov {

	SceneHierarchy::SceneHierarchy(const Ref<Scene>& context) {
		setContext(context);
	}

	void SceneHierarchy::setContext(const Ref<Scene>& context) {
		m_Ctx = context;
	}

	void SceneHierarchy::onImGuiDraw() {
		ImGui::Begin("Hierarchy");
		m_Ctx->m_Registry.each([&](auto entityID) {
			Entity entity{ entityID, m_Ctx.get() };

			drawEntityNode(entity);
		});
		ImGui::End();
	}

	void SceneHierarchy::drawEntityNode(Entity entity) {
		auto& tag = entity.get<NameComp>().Name;
		ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | (m_Selected == entity ? ImGuiTreeNodeFlags_Selected : 0);
		bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, tag.c_str());
		if (ImGui::IsItemClicked()) {
			m_Selected = entity;
		}

		if (opened) ImGui::TreePop();
	}

}