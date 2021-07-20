#include "Sandbox2D.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D() : Layer("Sandbox2D"), m_CameraController{ 1920.0f / 1080.0f } {
}

void Sandbox2D::onUpdate(Cherenkov::Timestep dt) {
	m_CameraController.onUpdate(dt);

	Cherenkov::RenderCommand::clear({ 1.0f, 0.0f, 1.0f, 1.0f });

	Cherenkov::Renderer::beginScene(m_CameraController.getCamera());

	std::dynamic_pointer_cast<Cherenkov::OpenGLShader>(m_Shader)->bind();
	std::dynamic_pointer_cast<Cherenkov::OpenGLShader>(m_Shader)->uniformFloat4("colour", m_ObjColour);

	Cherenkov::Renderer::submit(m_VertexArray, m_Shader, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	Cherenkov::Renderer::endScene();
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
	m_VertexArray = Cherenkov::VertexArray::init();

	float verts[4 * 5] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};

	Cherenkov::Ref<Cherenkov::VertexBuffer> vertexBuffer;
	vertexBuffer.reset(Cherenkov::VertexBuffer::init(verts, sizeof(verts) / sizeof(float_t)));

	Cherenkov::BufferLayout layout = {
		{Cherenkov::ShaderDataType::Vec3f, "a_Pos"}
	};
	vertexBuffer->layout(layout);
	m_VertexArray->addVertexBuffer(vertexBuffer);

	uint32_t idxs[6] = { 0, 1, 2, 2, 3, 0 };
	Cherenkov::Ref<Cherenkov::IndexBuffer> indexBuffer;
	indexBuffer.reset(Cherenkov::IndexBuffer::init(idxs, sizeof(idxs) / sizeof(uint32_t)));
	m_VertexArray->setIndexBuffer(indexBuffer);

	std::string vertIn("../Cherenkov/src/Cherenkov/Shaders/shader.vert");
	std::string fragIn("../Cherenkov/src/Cherenkov/Shaders/shader.frag");

	m_Shader = Cherenkov::Shader::init("SquareColourShader", vertIn, fragIn);
}

void Sandbox2D::onDetach() {

}
