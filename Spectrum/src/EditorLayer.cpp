#include <Cherenkov.h>
#include "EditorLayer.h"
#include "Defaults/Defaults.h"

#include <stdio.h>
#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imguizmo.h>

namespace Cherenkov {
	EditorLayer::EditorLayer() : Layer("EditorLayer") {}

	void EditorLayer::newScene() {
		m_ActiveScene = CreateRef<Scene>();
		m_ActiveScene->onViewportResize((uint32_t)m_VpSize.x, (uint32_t)m_VpSize.y);
		m_SceneHierarchy.setContext(m_ActiveScene);
		m_Properties.setContext(m_ActiveScene);
		m_SavePath = {};
	}

	void EditorLayer::saveScene() {
		if (!m_SavePath.empty()) {
			Serializer serializer(m_ActiveScene);
			serializer.serialize(m_SavePath);
		}
		else {
			saveAs();
		}
	}

	void EditorLayer::openScene() {
		std::string path = FileDialogue::open("Cherenkov Scene File (*.cherenkov)\0*.cherenkov\0");

		if (!path.empty()) {
			newScene();

			Serializer serializer(m_ActiveScene);
			serializer.deserialize(path);
		}

		m_SavePath = path;
	}

	void EditorLayer::saveAs() {
		m_SavePath = FileDialogue::save("Cherenkov Scene File (*.cherenkov)\0*.cherenkov\0");
		if (!m_SavePath.empty()) {
			Serializer serializer(m_ActiveScene);
			serializer.serialize(m_SavePath);
		}
	}

	void EditorLayer::onAttach() {
		CK_PROFILE_FUNCTION();
		m_Texture = Texture2D::init("assets/Textures/checkerboardSq.png");

		FbSpecification defaultSpec;
		defaultSpec.Attachments = { FbTextureFormat::RGBA8, FbTextureFormat::Depth, FbTextureFormat::RED_INT };
		defaultSpec.Width = 1280;
		defaultSpec.Height = 720;
		m_Framebuffer = Framebuffer::init(defaultSpec);

		m_ActiveScene = CreateRef<Scene>();
		m_EditorCamera = EditorCamera(30.0f, 1.778f, 0.1f, 1000.0f);

		m_SceneHierarchy.setContext(m_ActiveScene);
		m_Properties.setContext(m_ActiveScene);

	}

	void EditorLayer::onDetach() {
		
	}

	void EditorLayer::onUpdate(Timestep dt) {
		CK_PROFILE_FUNCTION();
		FbSpecification spec = m_Framebuffer->getSpecification();
		if (m_VpSize.x > 0.0f && m_VpSize.y > 0.0f && (spec.Width != m_VpSize.x || spec.Height != m_VpSize.y)) {
			m_Framebuffer->resize((uint32_t)m_VpSize.x, (uint32_t)m_VpSize.y);
			m_EditorCamera.setViewport(m_VpSize.x, m_VpSize.y);
			m_ActiveScene->onViewportResize((uint32_t)m_VpSize.x, (uint32_t)m_VpSize.y);
		}

		m_EditorCamera.onUpdate(dt);
		
		Renderer2D::resetStats();
		{
			CK_PROFILE_SCOPE("Render Clear");
			m_Framebuffer->bind();
			RenderCommand::clear({ 1.0f, 0.0f, 1.0f, 1.0f });
			m_Framebuffer->clearColourAttachment(1, -1);
		}
		
		{
			CK_PROFILE_SCOPE("Draw Scene");

			m_ActiveScene->onUpdateEditor(m_EditorCamera, dt);

			m_Framebuffer->unbind();
		}
	}

	void EditorLayer::onImGuiDraw() {
		CK_PROFILE_FUNCTION();

		static bool open = true;
		static bool persist = true;
		bool fullscreen = true;
		static ImGuiDockNodeFlags dockingFlags = ImGuiDockNodeFlags_None;

		ImGuiWindowFlags windowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

		if (fullscreen) {
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->Pos);
			ImGui::SetNextWindowSize(viewport->Size);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			windowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}

		if (dockingFlags & ImGuiDockNodeFlags_PassthruCentralNode) windowFlags |= ImGuiWindowFlags_NoBackground;

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0.0f, 0.0f });

		ImGui::Begin("Dockspace", &open, windowFlags);
		ImGui::PopStyleVar();

		if (fullscreen)	ImGui::PopStyleVar(2);

		ImGuiIO& io = ImGui::GetIO();
		ImGuiStyle& style = ImGui::GetStyle();
		float currMinWinX = style.WindowMinSize.x;
		style.WindowMinSize.x = 360.0f;
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
			ImGuiID dockID = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockID, ImVec2{ 0.0f, 0.0f }, dockingFlags);
		}
		style.WindowMinSize.x = currMinWinX;
		bool openFont = false;

		if (ImGui::BeginMenuBar()) {
			if (ImGui::BeginMenu("File")) {
				
				if (ImGui::MenuItem("New", "Ctrl + N")) newScene();

				if (ImGui::MenuItem("Open...", "Ctrl + O")) openScene();

				if (ImGui::MenuItem("Save", "Ctrl + S")) saveScene();

				if (ImGui::MenuItem("Save As...", "Ctrl + Shift + S")) saveAs();

				ImGui::Separator();
				if (ImGui::MenuItem("Serialize")) { Serializer serializer(m_ActiveScene); serializer.serialize("assets/Scenes/test.cherenkov"); }
				if (ImGui::MenuItem("Deserialize")) { Serializer serializer(m_ActiveScene); serializer.deserialize("assets/Scenes/test.cherenkov"); }
				ImGui::Separator();
				if (ImGui::MenuItem("Exit")) Application::get().close();
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Settings")) {
			
				if (ImGui::MenuItem("Font")) openFont = true;
				
				if (ImGui::BeginMenu("Theme")) {
					if (ImGui::MenuItem("Dear ImGui")) ImGuiLayer::setTheme(ImGuiLayer::ColourStyle::Default);
					if (ImGui::MenuItem("Light Mode")) ImGuiLayer::setTheme(ImGuiLayer::ColourStyle::LightMode);
					if (ImGui::MenuItem("Dark Mode")) ImGuiLayer::setTheme(ImGuiLayer::ColourStyle::DarkMode);
					ImGui::EndMenu();
				}
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		ImVec2 center = ImGui::GetMainViewport()->GetCenter();
		ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
		
		if (openFont) ImGui::OpenPopup("Font Selection");

		if (ImGui::BeginPopupModal("Font Selection", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
			static bool changed = false;
			const char* fonts[] = {"Source Sans Pro (Default)", "Dear ImGui", "Open Sans"};
			const char* fontPaths[] = {"assets/Fonts/Source Sans Pro/SourceSansPro-", "", "assets/Fonts/Open Sans/OpenSans-"};

			static uint32_t currentFont = 0;
			static ImGuiLayer::Font tempFont = { "", 18.0f };

			if (ImGui::BeginCombo("##fontstyle", fonts[currentFont])) {

				for (int i = 0; i < IM_ARRAYSIZE(fonts); i++) {
					const bool selected = (currentFont == i);

					if (ImGui::Selectable(fonts[i], selected)) {
						currentFont = i;
						changed = true;
					}

					if (selected) ImGui::SetItemDefaultFocus();
					tempFont.path = fontPaths[currentFont];
				}

				ImGui::EndCombo();
			}

			ImGui::Text("Font size: "); ImGui::SameLine(); if (ImGui::DragFloat("##fontsize", &tempFont.size, 1.0f, 1.0f, 50.0f)) changed = true;

			if (ImGui::Button("Apply")) {
				if (changed) {
					if (!tempFont.path.empty()) {
						
						if (!strcmp(strrchr(tempFont.path.c_str(), '\0') - 4, ".ttf")) {
							size_t idx = tempFont.path.rfind("-");
							tempFont.path = tempFont.path.substr(0, idx + 1);
						}
						tempFont.path.shrink_to_fit();
					}

					ImGuiLayer::fontChange = true;
					ImGuiLayer::font = tempFont;
				}
				ImGui::CloseCurrentPopup();
			}
			ImGui::SameLine(); if (ImGui::Button("Close")) ImGui::CloseCurrentPopup();

			ImGui::EndPopup();
		}

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
		ImGuiWindowClass window_class;
		window_class.DockNodeFlagsOverrideSet = ImGuiDockNodeFlags_AutoHideTabBar;
		ImGui::SetNextWindowClass(&window_class);
		ImGui::Begin("Viewport");
		ImVec2 vpOffset = ImGui::GetCursorPos();
		m_VpFocused = ImGui::IsWindowFocused();
		m_VpHovered = ImGui::IsWindowHovered();
		Application::get().getImGuiLayer()->blockingEvents(!m_VpFocused && !m_VpHovered);
		ImVec2 vpSize = ImGui::GetContentRegionAvail();
		m_VpSize = { vpSize.x, vpSize.y };

		uint64_t tID = m_Framebuffer->getColourAttachment();
		ImGui::Image(reinterpret_cast<void*>(tID), ImVec2{ m_VpSize.x, m_VpSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

		ImVec2 windowSize = ImGui::GetWindowSize();
		ImVec2 minBound = ImGui::GetWindowPos();
		minBound.x += vpOffset.x;	minBound.y += vpOffset.y;
		ImVec2 maxBound = minBound;
		maxBound.x += windowSize.x;	maxBound.y += windowSize.y;

		m_VpBounds[0] = { minBound.x, minBound.y };
		m_VpBounds[1] = { maxBound.x, maxBound.y };

		Entity currentSelection = m_ActiveScene->getSelectedEntity();
		if (currentSelection && m_GuizmoOp != -1) {
			ImGuizmo::SetOrthographic(false);
			ImGuizmo::SetDrawlist();

			float windowWidth = (float)ImGui::GetWindowWidth(), windowHeight = (float)ImGui::GetWindowHeight();
			ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, windowWidth, windowHeight);

			/*auto& cameraEnt = m_ActiveScene->getPrimaryCamera();
			const auto& camera = cameraEnt.get<CameraComp>().Camera;
			const auto& projection = camera.getProjection();
			glm::mat4 viewMat = glm::inverse(cameraEnt.get<TransformComp>().getTransform());*/

			const glm::mat4& camProjection = m_EditorCamera.getProjection();
			glm::mat4 camView = m_EditorCamera.getView();

			auto& selectedTC = currentSelection.get<TransformComp>();
			glm::mat4 selectedTransform = selectedTC.getTransform();

			bool snap = Input::isKeyPressed(Key::Left_Control);
			float snapValue;
			switch (m_GuizmoOp) {
			case ImGuizmo::OPERATION::ROTATE: {snapValue = 15.0f; break; }
			case ImGuizmo::OPERATION::TRANSLATE: {snapValue = 0.5f; break; }
			case ImGuizmo::OPERATION::SCALE: { snapValue = 0.1f; break; }
			default: CK_CORE_ASSERT(false, "Unknown ImGuizmo operation."); break;
			}
			float snapVals[3] = { snapValue, snapValue, snapValue };
			ImGuizmo::Manipulate(glm::value_ptr(camView), glm::value_ptr(camProjection), (ImGuizmo::OPERATION)m_GuizmoOp, ImGuizmo::LOCAL, glm::value_ptr(selectedTransform), nullptr, snap ? snapVals : nullptr);

			if (ImGuizmo::IsUsing()) {
				glm::vec3 newPos, newRot, newScale;
				Maths::decomposeMat4(selectedTransform, newPos, newRot, newScale);
				glm::vec3 deltaRot = newRot - selectedTC.Rotation;

				selectedTC.Position = newPos;
				selectedTC.Rotation += deltaRot;
				selectedTC.Scale = newScale;
			}
		}

		ImGui::End();
		ImGui::PopStyleVar();

		m_SceneHierarchy.onImGuiDraw();
		m_Properties.onImGuiDraw();

		auto stats = Renderer2D::getStats();
		ImGui::Begin("Stats");

		ImGui::Text("Renderer2D Stats:");
		ImGui::Text("Draw Calls: %d", stats.draws);
		ImGui::Text("Quads: %d", stats.quads);
		ImGui::Text("Vertices: %d", stats.getTotalVertices());
		ImGui::Text("Indices: %d", stats.getTotalIndices());

		ImGui::End();


		ImGui::End();
	}

	void EditorLayer::onEvent(Event& ev) {
		CK_PROFILE_FUNCTION();
		//m_CameraController.onEvent(ev);
		m_EditorCamera.onEvent(ev);


		EventDispatcher dp(ev);
		dp.Dispatch<KeyPressedEvent>(CK_BIND_EVENT_FN(EditorLayer::onKeyPressed));
		dp.Dispatch<MouseButtonPressedEvent>(CK_BIND_EVENT_FN(EditorLayer::onMouseButtonPressed));
	}

	bool EditorLayer::onKeyPressed(KeyPressedEvent& ev) {
		

		// Shortcuts
		if (ev.getRepeats() > 0) return false;
		bool ctrl = Input::isKeyPressed(Key::Left_Control) || Input::isKeyPressed(Key::Right_Control);
		bool shift = Input::isKeyPressed(Key::Left_Shift) || Input::isKeyPressed(Key::Right_Shift);

		switch (ev.getKeyCode()) {

		case Key::O: {
			if (ctrl) openScene();
			break;
		}
		case Key::N: {
			if (ctrl) newScene();
			break;
		}
		case Key::S: {
			if (ctrl && shift) saveAs();
			else if (ctrl) saveScene();
			break;
		}

		case Key::Q: {
			m_GuizmoOp = -1;
			break;
		}
		case Key::W: {
			m_GuizmoOp = ImGuizmo::OPERATION::TRANSLATE;
			break;
		}
		case Key::E: {
			m_GuizmoOp = ImGuizmo::OPERATION::ROTATE;
			break;
		}
		case Key::R: {
			m_GuizmoOp = ImGuizmo::OPERATION::SCALE;
			break;
		}

		default: 	break;
		}
		return false;
	}

	bool EditorLayer::onMouseButtonPressed(MouseButtonPressedEvent& ev) {
		
		switch (ev.getMouseButton()) {
		case Mouse::Button_Left:
			if (m_VpHovered) {
				auto [mx, my] = ImGui::GetMousePos();
				mx -= m_VpBounds[0].x;
				my -= m_VpBounds[0].y;
				glm::vec2 vpSize = m_VpBounds[1] - m_VpBounds[0];
				my = vpSize.y - my;
				int mouseX = (int)mx;
				int mouseY = (int)my;

				if (mouseX >= 0 && mouseX < (int)vpSize.x && mouseY >= 0 && mouseY < (int)vpSize.y) {
					m_Framebuffer->bind();
					int val = m_Framebuffer->readPixel(1, mouseX, mouseY);
					m_Framebuffer->unbind();
					if (val > -1) {
						Entity ent((entt::entity)val, m_ActiveScene.get());
						m_ActiveScene->setSelectedEntity(ent);
					}
				}
			}
			break;
		default :			break;
		}
		return false;
	}
}
