#include "Sandbox2D.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D() : Layer("Sandbox2D"), m_CameraController{ 1920.0f / 1080.0f } {
}

void Sandbox2D::onUpdate(Cherenkov::Timestep dt) {
	m_CameraController.onUpdate(dt);

	Cherenkov::RenderCommand::clear({ 1.0f, 0.0f, 1.0f, 1.0f });

	Cherenkov::Renderer2D::beginScene(m_CameraController.getCamera());

	Cherenkov::Renderer2D::Quad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, { 1.0f, 1.0f, 0.0f, 1.0f});
	Cherenkov::Renderer2D::Quad({ -1.0f, 0.0f }, { 0.5f, 0.5f }, m_Texture, 30.0f);
	Cherenkov::Renderer2D::Quad({ 1.0f, -1.0f }, { 1.0f, 1.0f }, {0.5f, 0.2f, 0.8f, 1.0f}, m_Texture, 10.0f);

	Cherenkov::Renderer2D::endScene();
}

void Sandbox2D::onImGuiDraw() {
	ImGui::Begin("Settings");
	ImGui::ColorPicker4("Sq. Colour", glm::value_ptr(m_ObjColour));
	ImGui::End();
}

void Sandbox2D::onEvent(Cherenkov::Event& ev) {
	m_CameraController.onEvent(ev);
}

void Sandbox2D::onAttach() {
	m_Texture = Cherenkov::Texture2D::init("assets/Textures/checkerboardSq.png");
}

void Sandbox2D::onDetach() {

}
