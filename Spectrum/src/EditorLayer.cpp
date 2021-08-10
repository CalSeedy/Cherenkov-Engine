#include <Cherenkov.h>
#include "EditorLayer.h"
#include "Defaults/Defaults.h"

#include <stdio.h>
#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

bool switched = false;

namespace Cherenkov {
	EditorLayer::EditorLayer() : Layer("EditorLayer"), m_CameraController{ 1920.0f / 1080.0f } {}

	void EditorLayer::onAttach() {
		CK_PROFILE_FUNCTION();
		m_Texture = Texture2D::init("assets/Textures/checkerboardSq.png");

		FbSpecification defaultSpec;
		auto& window = Application::get().getWindow();
		defaultSpec.Width = window.getWidth();
		defaultSpec.Height = window.getHeight();
		m_Framebuffer = Framebuffer::init(defaultSpec);

		m_ActiveScene = CreateRef<Scene>();
		auto square = m_ActiveScene->createEntity("Square");
		square.add<SpriteComp>( 1.0f, 1.0f, 0.0f, 1.0f );
		m_Square = square;

		m_CameraFirst = m_ActiveScene->getPrimaryCamera();

		auto cam2 = m_ActiveScene->createEntity("Camera 2");
		cam2.add<CameraComp>();
		m_CameraOther = cam2;

		m_CameraFirst.add<ScriptComp>(ScriptLanguage::Native).bind<SimpleMovement>();
		m_CameraOther.add<ScriptComp>(ScriptLanguage::Native).bind<SimpleMovement>();


		m_SceneHierarchy.setContext(m_ActiveScene);
		m_Properties.setContext(m_ActiveScene);
	}

	void EditorLayer::onDetach() {}

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

		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
			ImGuiID dockID = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockID, ImVec2{ 0.0f, 0.0f }, dockingFlags);
		}

		if (ImGui::BeginMenuBar()) {
			if (ImGui::BeginMenu("File")) {
				if (ImGui::MenuItem("Exit")) Application::get().close();
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
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
		m_CameraController.onEvent(ev);
	}

}
