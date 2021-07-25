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
	Cherenkov::QuadProperties q1, q2, q3;
	q1.Position = m_SqPos;
	q1.Colour = { 0.0f, 1.0f, 0.0f, 1.0f };
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
		//glm::vec2 scale = { 1.0f, 1.0f };
		//
		//for (int i = 0; i < 20; i++) {
		//	for (int j = 0; j < 20; j++) {
		//		Cherenkov::QuadProperties props;
		//		props.Position.setPos({ (i * scale.x * 1.1f),(j * scale.y * 1.1f), 0.0f });
		//
		//		props.Colour = { 10.0f * props.Position.x / 256, 1.0f, 0.0f, 1.0f };
		//
		//		Cherenkov::Renderer2D::Quad(scale, props);
		//	}
		//}



		Cherenkov::Renderer2D::endScene();
	}
}

void Sandbox2D::onImGuiDraw() {
	CK_PROFILE_FUNCTION();
	ImGui::Begin("Settings");
	ImGui::ColorPicker4("Sq. Colour", glm::value_ptr(m_ObjColour));
	ImGui::DragFloat3("Sq. Position", glm::value_ptr(m_SqPos), 0.01f);
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
