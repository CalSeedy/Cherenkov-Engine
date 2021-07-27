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
		for (float x = -10.0; x < 10.0f; x += 0.5f) {
			for (float y = -10.0; y < 10.0f; y += 0.5f) {
				p.Colour = { (x + 10.0f) / 10.0f, (y + 10.0f) / 10.0f, 0.4f, 1.0f };
				p.Position = { x, y };
				Cherenkov::Renderer2D::Quad({ 0.45f, 0.45f }, p);
			}
		}

		Cherenkov::Renderer2D::endScene();
	}
}

void Sandbox2D::onImGuiDraw() {
	CK_PROFILE_FUNCTION();
	auto stats = Cherenkov::Renderer2D::getStats();
	ImGui::Begin("Settings");
	ImGui::ColorPicker4("Sq. Colour", glm::value_ptr(m_ObjColour));
	ImGui::DragFloat3("Sq. Position", glm::value_ptr(m_SqPos), 0.01f);

	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("Draw Calls: %d", stats.draws);
	ImGui::Text("Quads: %d", stats.quads);
	ImGui::Text("Vertices: %d", stats.getTotalVertices());
	ImGui::Text("Indices: %d", stats.getTotalIndices());
	ImGui::End();
}

void Sandbox2D::onEvent(Cherenkov::Event& ev) {
	CK_PROFILE_FUNCTION();
	m_CameraController.onEvent(ev);
}

void Sandbox2D::onAttach() {
	CK_PROFILE_FUNCTION();
	m_Texture = Cherenkov::Texture2D::init("assets/Textures/checkerboardSq.png");
}

void Sandbox2D::onDetach() {

}
