#include <Cherenkov.h>
#include "imgui/imgui.h"

class ExampleLayer : public Cherenkov::Layer {
	Cherenkov::OrthographicCamera				m_Camera;
	glm::vec3									m_CameraPos;
	float										m_CameraRotation = 0.0f;
	const float									m_CameraPanSpeed = 0.1f;
	const float									m_CameraRotSpeed = 1.0f;

	std::shared_ptr<Cherenkov::Shader>			m_Shader;
	std::shared_ptr<Cherenkov::VertexArray>		m_VertexArray;
public:
	ExampleLayer() : Layer("Test!"), m_Camera{ -1.6f, 1.6f, -0.9f, 0.9f }, m_CameraPos{ 0.0f } {
		m_VertexArray.reset(Cherenkov::VertexArray::init());

		float verts[4 * 3] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		std::shared_ptr<Cherenkov::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Cherenkov::VertexBuffer::init(verts, sizeof(verts) / sizeof(float_t)));

		Cherenkov::BufferLayout layout = {
			{Cherenkov::ShaderDataType::Vec3f, "a_Pos"}
		};
		vertexBuffer->layout(layout);
		m_VertexArray->addVertexBuffer(vertexBuffer);

		uint32_t idxs[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Cherenkov::IndexBuffer> indexBuffer;
		indexBuffer.reset(Cherenkov::IndexBuffer::init(idxs, sizeof(idxs) / sizeof(uint32_t)));
		m_VertexArray->setIndexBuffer(indexBuffer);

		const char* vertIn("../Cherenkov/src/Cherenkov/Shaders/shader.vert");
		const char* fragIn("../Cherenkov/src/Cherenkov/Shaders/shader.frag");

		m_Shader.reset(new Cherenkov::OpenGLShader(vertIn, fragIn));
	}

	void onUpdate() override {
		
		if (Cherenkov::Input::isKeyPressed(CK_KEY_W))
			m_CameraPos.y += m_CameraPanSpeed;

		else if (Cherenkov::Input::isKeyPressed(CK_KEY_S))
			m_CameraPos.y -= m_CameraPanSpeed;

		if (Cherenkov::Input::isKeyPressed(CK_KEY_A))
			m_CameraPos.x -= m_CameraPanSpeed;

		else if (Cherenkov::Input::isKeyPressed(CK_KEY_D))
			m_CameraPos.x += m_CameraPanSpeed;
		
		if (Cherenkov::Input::isKeyPressed(CK_KEY_Q))
			m_CameraRotation += m_CameraRotSpeed;

		else if (Cherenkov::Input::isKeyPressed(CK_KEY_E))
			m_CameraRotation -= m_CameraRotSpeed;

		Cherenkov::RenderCommand::clear({ 1.0f, 0.0f, 1.0f, 1.0f });

		m_Camera.setPosition(m_CameraPos);
		m_Camera.setRotation(m_CameraRotation);

		Cherenkov::Renderer::beginScene(m_Camera);

		Cherenkov::Renderer::submit(m_VertexArray, m_Shader);

		Cherenkov::Renderer::endScene();
	}

	void onEvent(Cherenkov::Event &event) override {
		Cherenkov::EventDispatcher dispatcher(event);
		dispatcher.Dispatch<Cherenkov::KeyPressedEvent>(CK_BIND_EVENT_FN(ExampleLayer::onKeyPressedEvent));
	}

	bool onKeyPressedEvent(Cherenkov::KeyPressedEvent& event) {
		switch (event.getKeyCode()) {
		case CK_KEY_ENTER:
			m_CameraPos = { 0.0f, 0.0f, 0.0f };
			m_CameraRotation = 0.0f;
			break;
		default:
			break;
		}
		return false;
	}
	void onImGuiDraw() override	{

	}
};


class Sandbox : public Cherenkov::Application {

public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{
	}
};


Cherenkov::Application* Cherenkov::createApplication() {
	return new Sandbox();
}