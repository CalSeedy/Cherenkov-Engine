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

		if (ImGui::IsMouseClicked(ImGuiMouseButton_Left) && ImGui::IsWindowHovered()) m_Ctx->setSelectedEntity(Entity());

		if (ImGui::BeginPopupContextWindow(0, ImGuiMouseButton_Right, false)) {
			
			if (ImGui::MenuItem("Add Entity")) m_Ctx->createEntity();

			ImGui::EndPopup();
		}

		ImGui::End();
	}

	void SceneHierarchy::drawEntityNode(Entity entity) {
		auto& tag = entity.get<NameComp>().Name;
		ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth | (m_Ctx->getSelectedEntity() == entity ? ImGuiTreeNodeFlags_Selected : 0);
		bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, tag.c_str());
		if (ImGui::IsItemClicked()) {
			m_Ctx->setSelectedEntity(entity);
		}

		bool deleted = false;
		if (ImGui::BeginPopupContextItem()) {

			char txt[256];
			sprintf_s(txt, "Delete '%s'", tag.c_str());
			if (ImGui::MenuItem(txt)) deleted = true;

			ImGui::EndPopup();

			if (deleted) {
				if (m_Ctx->getSelectedEntity() == entity) m_Ctx->setSelectedEntity(Entity());
				m_Ctx->destroyEntity(entity);
			}
		}

		if (opened) ImGui::TreePop();
	}

}
