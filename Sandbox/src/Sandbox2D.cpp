#include "Sandbox2D.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdio.h>

Sandbox2D::Sandbox2D() : Layer("Sandbox2D"), m_CameraController{ 1920.0f / 1080.0f } {
}

void Sandbox2D::onUpdate(Cherenkov::Timestep dt) {
	CK_PROFILE_FUNCTION();
	m_CameraController.onUpdate(dt);

	{
		CK_PROFILE_SCOPE("Render Clear");
		Cherenkov::RenderCommand::clear({ 1.0f, 0.0f, 1.0f, 1.0f });
	}

	{
		CK_PROFILE_SCOPE("Draw Scene");
		Cherenkov::Renderer2D::beginScene(m_CameraController.getCamera());

		Cherenkov::Renderer2D::Quad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, { 1.0f, 1.0f, 0.0f, 1.0f });
		Cherenkov::Renderer2D::Quad({ -1.0f, 0.0f }, { 0.5f, 0.5f }, m_Texture, 30.0f);
		Cherenkov::Renderer2D::Quad({ 1.0f, -1.0f }, { 1.0f, 1.0f }, { 0.5f, 0.2f, 0.8f, 1.0f }, m_Texture, 10.0f);

		Cherenkov::Renderer2D::endScene();
	}
}

void Sandbox2D::onImGuiDraw() {
	CK_PROFILE_FUNCTION();
	ImGui::Begin("Settings");
	ImGui::ColorPicker4("Sq. Colour", glm::value_ptr(m_ObjColour));

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