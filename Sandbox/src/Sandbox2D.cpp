#include "Sandbox2D.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdio.h>

Sandbox2D::Sandbox2D() : Layer("Sandbox2D"), m_CameraController{ 1920.0f / 1080.0f } {
}

void Sandbox2D::onUpdate(Cherenkov::Timestep dt) {
	CK_PROFILE_FUNCTION();
	m_CameraController.onUpdate(dt);
	Cherenkov::Renderer2D::resetStats();
	{
		CK_PROFILE_SCOPE("Render Clear");
		m_Framebuffer->bind();
		Cherenkov::RenderCommand::clear({ 1.0f, 0.0f, 1.0f, 1.0f });
	}
	Cherenkov::QuadProperties q1, q2, q3;
	q1.Position = m_SqPos;
	q1.Colour = m_ObjColour;
	q1.Angle = 30.0f;

	q2.Position = { 0.0f, 0.0f, -0.5f };
	q2.TileFactor = 4.0f;

	static float rotation = 0.0f;
	rotation += dt * 5.0f;
	q3.Position = { -1.0f, -1.0f };
	q3.Colour = { 1.0f, 0.2f, 0.2f, 1.0f };
	q3.Angle = rotation;
	q3.TileFactor = 5.0f;
	{
		CK_PROFILE_SCOPE("Draw Scene");
		
		Cherenkov::Renderer2D::beginScene(m_CameraController.getCamera());

		Cherenkov::Renderer2D::Quad({ 2.0f, 2.0f }, q1);

		Cherenkov::Renderer2D::Quad({ 10.0f, 10.0f }, m_Texture, q2);
		Cherenkov::Renderer2D::Quad({ 6.0f, 6.0f }, m_Texture, q3);

		Cherenkov::Renderer2D::endScene();
		
		Cherenkov::QuadProperties p;
		Cherenkov::Renderer2D::beginScene(m_CameraController.getCamera());
		for (float x = -5.0; x < 5.0f; x += 0.5f) {
			for (float y = -5.0; y < 5.0f; y += 0.5f) {
				p.Colour = { (x + 5.0f) / 5.0f, (y + 5.0f) / 5.0f, 0.4f, 1.0f };
				p.Position = { x, y };
				Cherenkov::Renderer2D::Quad({ 0.45f, 0.45f }, p);
			}
		}

		Cherenkov::Renderer2D::endScene();
		m_Framebuffer->unbind();
	}
}

void Sandbox2D::onImGuiDraw() {
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
			if (ImGui::MenuItem("Exit")) Cherenkov::Application::get().close();
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}
	ImGui::Begin("Renderer");
	auto& window = Cherenkov::Application::get().getWindow();
	uint32_t tID = m_Framebuffer->getColourAttachment();
	ImGui::Image((void*)tID, ImVec2{ (float)window.getWidth(), (float)window.getHeight() });
	ImGui::End();

	ImGui::Begin("Settings");
	ImGui::ColorPicker4("Sq. Colour", glm::value_ptr(m_ObjColour));
	ImGui::DragFloat3("Sq. Position", glm::value_ptr(m_SqPos), 0.01f);
	ImGui::End();


	auto stats = Cherenkov::Renderer2D::getStats();
	ImGui::Begin("Stats");

	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("Draw Calls: %d", stats.draws);
	ImGui::Text("Quads: %d", stats.quads);
	ImGui::Text("Vertices: %d", stats.getTotalVertices());
	ImGui::Text("Indices: %d", stats.getTotalIndices());
	ImGui::End();
	ImGui::End();
}

void Sandbox2D::onEvent(Cherenkov::Event& ev) {
	CK_PROFILE_FUNCTION();
	m_CameraController.onEvent(ev);
}

void Sandbox2D::onAttach() {
	CK_PROFILE_FUNCTION();
	m_Texture = Cherenkov::Texture2D::init("assets/Textures/checkerboardSq.png");

	Cherenkov::Specification defaultSpec;
	auto& window = Cherenkov::Application::get().getWindow();
	defaultSpec.Width = window.getWidth();
	defaultSpec.Height = window.getHeight();
	m_Framebuffer = Cherenkov::Framebuffer::init(defaultSpec);
}

void Sandbox2D::onDetach() {

}
