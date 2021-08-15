#include <Cherenkov.h>
#include "EditorLayer.h"
#include "Defaults/Defaults.h"

#include <stdio.h>
#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Cherenkov {
	EditorLayer::EditorLayer() : Layer("EditorLayer"), m_CameraController{ 1920.0f / 1080.0f } {}

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
		auto& window = Application::get().getWindow();
		defaultSpec.Width = window.getWidth();
		defaultSpec.Height = window.getHeight();
		m_Framebuffer = Framebuffer::init(defaultSpec);

		m_ActiveScene = CreateRef<Scene>();
#if 0
		auto square = m_ActiveScene->createEntity("Square");
		square.add<SpriteComp>( 1.0f, 1.0f, 0.0f, 1.0f );
		m_Square = square;

		m_CameraFirst = m_ActiveScene->getPrimaryCamera();

		auto cam2 = m_ActiveScene->createEntity("Camera 2");
		cam2.add<CameraComp>();
		m_CameraOther = cam2;

		m_CameraFirst.add<ScriptComp>(ScriptLanguage::Native).bind<SimpleMovement>();
		m_CameraOther.add<ScriptComp>(ScriptLanguage::Native).bind<SimpleMovement>();
#endif

		m_SceneHierarchy.setContext(m_ActiveScene);
		m_Properties.setContext(m_ActiveScene);

	}

	void EditorLayer::onDetach() {
		
	}

	void EditorLayer::onUpdate(Timestep dt) {
		CK_PROFILE_FUNCTION();

		if (FbSpecification spec = m_Framebuffer->getSpecification(); m_VpSize.x > 0.0f && m_VpSize.y > 0.0f && (spec.Width != m_VpSize.x || spec.Height != m_VpSize.y)) {
			m_Framebuffer->resize((uint32_t)m_VpSize.x, (uint32_t)m_VpSize.y);
			m_CameraController.resize(m_VpSize.x, m_VpSize.y);
			m_ActiveScene->onViewportResize((uint32_t)m_VpSize.x, (uint32_t)m_VpSize.y);
		}

		if (m_VpFocused) m_CameraController.onUpdate(dt);
		
		Renderer2D::resetStats();
		{
			CK_PROFILE_SCOPE("Render Clear");
			m_Framebuffer->bind();
			RenderCommand::clear({ 1.0f, 0.0f, 1.0f, 1.0f });
		}
		
		{
			CK_PROFILE_SCOPE("Draw Scene");

			m_ActiveScene->onUpdate(dt);

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

		m_VpFocused = ImGui::IsWindowFocused();
		m_VpHovered = ImGui::IsWindowHovered();
		Application::get().getImGuiLayer()->blockingEvents(!m_VpFocused || !m_VpHovered);
		ImVec2 vpSize = ImGui::GetContentRegionAvail();
		m_VpSize = { vpSize.x, vpSize.y };

		uint64_t tID = m_Framebuffer->getColourAttachment();
		ImGui::Image(reinterpret_cast<void*>(tID), ImVec2{ m_VpSize.x, m_VpSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
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

		EventDispatcher dp(ev);
		dp.Dispatch<KeyPressedEvent>(CK_BIND_EVENT_FN(EditorLayer::onKeyPressed));
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
		default: 	break;
		}
	}
}
