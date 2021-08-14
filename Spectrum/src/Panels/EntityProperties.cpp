#include "EntityProperties.h"
#include "../Defaults/Defaults.h"

#include <glm/gtc/type_ptr.hpp>
#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>

namespace Cherenkov {
#define BOLD 1
#define ITALIC 2

	EntityProperties::EntityProperties(const Ref<Scene>& context) {
		setContext(context);
	}

	void EntityProperties::setContext(const Ref<Scene>& context) {
		m_Ctx = context;
	}

	void EntityProperties::onImGuiDraw() {
		ImGui::Begin("Properties");
		if (m_Ctx->getSelectedEntity()) {
			drawComponents(m_Ctx->getSelectedEntity()); 
		}
		else ImGui::Text("No entity selected!");
		ImGui::End();
	}

	void EntityProperties::drawCameraControls(Entity& camera) {
		ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_DefaultOpen;

		auto& primaryCam = m_Ctx->getPrimaryCamera();
		bool primary = (camera == primaryCam);
		if (ImGui::Checkbox("Primary Camera: ", &primary)) {

			if (primary) m_Ctx->setPrimaryCamera(camera);

		}
		ImGui::SameLine();
		if ((entt::entity)primaryCam != entt::null) {
			auto str = primaryCam.get<NameComp>().Name.c_str();
			ImGui::Text(str);
		}
		else {

			ImGui::Text("No camera entities in scene!");
		}

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

	}

#define HEX2FLOAT(val) 0x##val / 256.0f
	static bool drawVec3Controls(const std::string& label, glm::vec3& vector, float_t resetValue = 0.0f, float_t colWidth = 100.0f) {
		ImGuiIO& io = ImGui::GetIO();
		bool notDefault = std::strcmp(ImGuiLayer::font.path.c_str(), "") && !ImGuiLayer::fontChange;
		bool changed = false;
		ImGui::PushID(label.c_str());
		ImGui::Columns(2);

		ImGui::SetColumnWidth(0, colWidth);
		ImGui::Text(label.c_str());
		
		ImGui::NextColumn();
		ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0.0f, 0.0f });

		float_t lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		float_t padding = 2.0f;
		ImVec2 buttonSize = { lineHeight + padding, lineHeight };
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ HEX2FLOAT(F5), HEX2FLOAT(33), HEX2FLOAT(3E), 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ HEX2FLOAT(F1), HEX2FLOAT(08), HEX2FLOAT(15), 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ HEX2FLOAT(C0), HEX2FLOAT(06), HEX2FLOAT(11), 1.0f });
		if (notDefault) ImGui::PushFont(io.Fonts->Fonts[BOLD]);
		if (ImGui::Button("X", buttonSize))	vector.x = resetValue; changed = true;
		if (notDefault) ImGui::PopFont();
		ImGui::SameLine();
		if (ImGui::DragFloat("##X", &vector.x, 0.1f)) changed = true;
		ImGui::PopItemWidth();
		ImGui::SameLine(); ImGui::Dummy({ 3.0f, lineHeight }); ImGui::SameLine();
		ImGui::PopStyleColor(3);

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ HEX2FLOAT(18), HEX2FLOAT(A7), HEX2FLOAT(3E), 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ HEX2FLOAT(1E), HEX2FLOAT(D3), HEX2FLOAT(4F), 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ HEX2FLOAT(14), HEX2FLOAT(B2), HEX2FLOAT(3E), 1.0f });
		if (notDefault) ImGui::PushFont(io.Fonts->Fonts[BOLD]);
		if (ImGui::Button("Y", buttonSize))	vector.y = resetValue; changed = true;
		if (notDefault) ImGui::PopFont();
		ImGui::SameLine();
		if (ImGui::DragFloat("##Y", &vector.y, 0.1f)) changed = true;
		ImGui::PopItemWidth();
		ImGui::SameLine(); ImGui::Dummy({ 3.0f, lineHeight }); ImGui::SameLine();
		ImGui::PopStyleColor(3);

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ HEX2FLOAT(20), HEX2FLOAT(4A), HEX2FLOAT(EB), 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ HEX2FLOAT(18), HEX2FLOAT(67), HEX2FLOAT(E7), 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ HEX2FLOAT(14), HEX2FLOAT(4B), HEX2FLOAT(EB), 1.0f });
		if (notDefault) ImGui::PushFont(io.Fonts->Fonts[BOLD]);
		if (ImGui::Button("Z", buttonSize))	vector.z = resetValue; changed = true;
		if (notDefault) ImGui::PopFont();
		ImGui::SameLine();
		if(ImGui::DragFloat("##Z", &vector.z, 0.1f)) changed = true;
		ImGui::PopItemWidth();
		ImGui::PopStyleColor(3);

		ImGui::PopStyleVar();
		ImGui::Columns(1);
		ImGui::PopID();
		return changed;
	}
	
	template<typename T, typename Func>
	static void drawComponent(const std::string& title, Entity& entity, Func function) {
		if (entity.has<T>()) {
			const float_t padding{ 1.0f };
			ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding;
			const float availWidth = ImGui::GetContentRegionAvailWidth();
			bool deleted = false;
			auto& comp = entity.get<T>();
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4, 4 });
			ImGui::Separator();
			bool open = ImGui::TreeNodeEx((void*)typeid(T).hash_code(), flags, title.c_str());
			float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
			ImGui::PopStyleVar();

			const ImVec2 buttonSize{ lineHeight , lineHeight };
			ImGui::SameLine(availWidth - lineHeight * 0.5f); if (ImGui::Button("-", buttonSize)) ImGui::OpenPopup("ComponentDelete");
			if (ImGui::BeginPopup("ComponentDelete")) {

				if (ImGui::MenuItem("Remove component")) deleted = true;

				ImGui::EndPopup();
			}

			if (open) {
				function(entity);
				ImGui::TreePop();
			}
			if (deleted) entity.remove<T>();
			
		}
	}


	void EntityProperties::drawComponents(Entity& entity) {
		const float_t padding{ 1.0f };
		const float_t defaultColumnWidth = 100.0f;
		auto& tag = entity.get<NameComp>().Name;
		char buff[256];
		memset(buff, 0, sizeof(buff));
		strcpy_s(buff, tag.c_str());
		if (ImGui::InputText("##Name", buff, sizeof(buff))) {
			tag = std::string(buff);
		}
		
		drawAddComponents(entity);

		drawComponent<CameraComp>("Camera", entity, [&](Entity& ent) {
			drawCameraControls(ent);
		});

		drawComponent<SpriteComp>("Sprite/Texture", entity, [](Entity& ent) {
			auto& component = ent.get<SpriteComp>();
			ImGui::ColorEdit4("Colour", glm::value_ptr(component.Colour));
		});
		const float availWidth = ImGui::GetContentRegionAvailWidth();
		drawComponent<TransformComp>("Transform", entity, [&](Entity& ent) {
			auto& component = ent.get<TransformComp>();
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4, 4 });
			float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
			ImGui::SameLine(availWidth - lineHeight * 1.5f); if (ImGui::Button("+", ImVec2{ lineHeight, lineHeight})) ImGui::OpenPopup("ComponentSettings");
			ImGui::PopStyleVar();
			if (ImGui::BeginPopup("ComponentSettings")) {

				if (ImGui::MenuItem("Reset to default")) component = TransformComp::getDefault();

				ImGui::EndPopup();
			}
			drawVec3Controls("Scale", component.Scale, 1.0f);
			drawVec3Controls("Position", component.Position);

			glm::vec3 rotDeg{ glm::degrees(component.Rotation) };
			if (drawVec3Controls("Rotation", rotDeg)) component.Rotation = glm::radians(rotDeg);
		});

		drawComponent<ScriptComp>("Script", entity, [&](Entity& ent) {
			auto& component = ent.get<ScriptComp>();
			ImGui::Columns(2);
			ImGui::SetColumnWidth(0, defaultColumnWidth);
			ImGui::Text("Language:");
			ImGui::NextColumn();
			ImGui::Text(component.getLanguage());
			ImGui::Columns(1);

			ImGui::Columns(2);
			ImGui::SetColumnWidth(0, defaultColumnWidth);
			ImGui::Text("Name:");
			ImGui::NextColumn();

			char buff[256];
			memset(buff, 0, sizeof(buff));
			strcpy_s(buff, component.Name.c_str());
			if (ImGui::InputText("##name", buff, sizeof(buff))) component.Name = std::string(buff);
			ImGui::Columns(1);

			ImGui::Columns(2);
			ImGui::SetColumnWidth(0, defaultColumnWidth);
			ImGui::Text("Path:");
			ImGui::NextColumn();
			ImGui::Text(((std::filesystem::path)component).string().c_str());
			ImGui::Columns(1);
		});

	}

	void loadCustomScript(Entity& entity, ScriptLanguage language) {
		entity.add<ScriptComp>(language).bind<EmptyScript>();
	}

	void EntityProperties::drawAddComponents(Entity& entity) {
		ImGui::SameLine(); ImGui::PushItemWidth(-1);
		if (ImGui::Button("+")) ImGui::OpenPopup("AddComponent");

		if (ImGui::BeginPopup("AddComponent")) {
			bool noneLeft = true;
			if (!(entity.has<CameraComp>())) {
				noneLeft = false;
				if (ImGui::Selectable("Camera Component")) entity.add<CameraComp>();
			}

			if (!(entity.has<TransformComp>())) {
				noneLeft = false;
				if (ImGui::Selectable("Transform Component")) entity.add<TransformComp>();
			}

			if (!(entity.has<ScriptComp>())) {
				noneLeft = false;
				if (ImGui::BeginMenu("Script Component")) {
					if (ImGui::BeginMenu("Native (C++)")) {
						if (ImGui::Selectable("Empty (default)")) entity.add<ScriptComp>(ScriptLanguage::Native).bind<EmptyScript>();
						if (ImGui::Selectable("Simple Movement")) entity.add<ScriptComp>(ScriptLanguage::Native).bind<SimpleMovement>();
						if (ImGui::Selectable("Custom")) loadCustomScript(entity, ScriptLanguage::Native);
						ImGui::EndMenu();
					}

					if (ImGui::BeginMenu("Python")) {
						if (ImGui::Selectable("Empty (default)")) entity.add<ScriptComp>(ScriptLanguage::Python).bind<EmptyScript>();
						if (ImGui::Selectable("Custom")) loadCustomScript(entity, ScriptLanguage::Python);
						ImGui::EndMenu();
					}

					ImGui::EndMenu();
				}
			}

			if (!(entity.has<SpriteComp>())) {
				noneLeft = false;
				if (ImGui::Selectable("Sprite Component")) entity.add<SpriteComp>();
			}

			if (noneLeft) ImGui::Text("No available components.");
			ImGui::EndPopup();
		}
		ImGui::PopItemWidth();
	}
}
