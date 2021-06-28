#include <Cherenkov.h>
#include "imgui/imgui.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public Cherenkov::Layer {
	Cherenkov::OrthographicCameraController		m_CameraController;
	
	float										m_ObjAngle{ 0.0f };
	glm::vec4									m_ObjColour{ 0.906f, 0.227f, 0.137f, 1.0f };
	float										m_ObjScale{ 1.0f };
	glm::vec3									m_ObjTranslate{ 0.0f };

	const float									m_PanSpeed = 5.0f;
	const float									m_RotSpeed = 70.0f;

	Cherenkov::Ref<Cherenkov::Shader>			m_Shader;
	Cherenkov::Ref<Cherenkov::ShaderLibrary>	m_ShaderLibrary;
	Cherenkov::Ref<Cherenkov::Texture2D>		m_Texture;
	Cherenkov::Ref<Cherenkov::Texture2D>		m_Texture2;
	Cherenkov::Ref<Cherenkov::Shader>			m_TextureShader;
	Cherenkov::Ref<Cherenkov::VertexArray>		m_VertexArray;

public:
	ExampleLayer() : Layer("Test!"), m_CameraController { 1920.0f / 1080.0f } {

		m_VertexArray.reset(Cherenkov::VertexArray::init());

		float verts[4 * 5] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Cherenkov::Ref<Cherenkov::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Cherenkov::VertexBuffer::init(verts, sizeof(verts) / sizeof(float_t)));

		Cherenkov::BufferLayout layout = {
			{Cherenkov::ShaderDataType::Vec3f, "a_Pos"},
			{Cherenkov::ShaderDataType::Vec2f, "a_TexCoord"}
		};
		vertexBuffer->layout(layout);
		m_VertexArray->addVertexBuffer(vertexBuffer);

		uint32_t idxs[6] = { 0, 1, 2, 2, 3, 0 };
		Cherenkov::Ref<Cherenkov::IndexBuffer> indexBuffer;
		indexBuffer.reset(Cherenkov::IndexBuffer::init(idxs, sizeof(idxs) / sizeof(uint32_t)));
		m_VertexArray->setIndexBuffer(indexBuffer);

		std::string vertIn("../Cherenkov/src/Cherenkov/Shaders/shader.vert");
		std::string fragIn("../Cherenkov/src/Cherenkov/Shaders/shader.frag");
		std::string texShader("assets/Shaders/Texture.glsl");

		m_Shader = Cherenkov::Shader::init("SquareColourShader",vertIn, fragIn);
		m_TextureShader = Cherenkov::Shader::init(texShader);

		m_Texture = Cherenkov::Texture2D::init ("assets/Textures/checkerboardSq.png");
		m_Texture2 = Cherenkov::Texture2D::init("assets/Textures/ChernoLogo.png");

		std::dynamic_pointer_cast<Cherenkov::OpenGLShader>(m_TextureShader)->bind();
		std::dynamic_pointer_cast<Cherenkov::OpenGLShader>(m_TextureShader)->uniformInt("tex", 0);
	}

	void onUpdate(Cherenkov::Timestep dt) override {
		//CK_TRACE("dt: {0} s ({1} FPS)", dt.getSeconds(), dt.toFPS());

		m_CameraController.onUpdate(dt);
		/* --------------- Object Transform ---------------*/
		if (Cherenkov::Input::isKeyPressed(CK_KEY_U))
			m_ObjAngle += m_RotSpeed * dt;

		else if (Cherenkov::Input::isKeyPressed(CK_KEY_O))
			m_ObjAngle -= m_RotSpeed * dt;


		if (Cherenkov::Input::isKeyPressed(CK_KEY_PAGE_UP))
			m_ObjScale += 1.0f * dt;

		else if (Cherenkov::Input::isKeyPressed(CK_KEY_PAGE_DOWN))
			m_ObjScale -= 1.0f * dt;

		Cherenkov::RenderCommand::clear({ 1.0f, 0.0f, 1.0f, 1.0f });

		Cherenkov::Renderer::beginScene(m_CameraController.getCamera());

		std::dynamic_pointer_cast<Cherenkov::OpenGLShader>(m_Shader)->bind();
		std::dynamic_pointer_cast<Cherenkov::OpenGLShader>(m_Shader)->uniformFloat4("colour", m_ObjColour);

		for (int i = -10; i < 10; ++i) {
			for (int j = -10; j < 10; ++j) {
				glm::vec3 pos = {i * (m_ObjScale * 1.1f), j * (m_ObjScale * 1.1f), 0.0f};
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * glm::rotate(glm::mat4(1.0f), glm::radians(m_ObjAngle), { 0.0f, 0.0f, 1.0f }) * glm::scale(glm::mat4(1.0f), glm::vec3(m_ObjScale));
				Cherenkov::Renderer::submit(m_VertexArray, m_Shader, transform);
			}
		}

		m_Texture->bind();
		Cherenkov::Renderer::submit(m_VertexArray, m_TextureShader, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f*m_ObjScale)));

		m_Texture2->bind();
		Cherenkov::Renderer::submit(m_VertexArray, m_TextureShader, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f * m_ObjScale)));

		Cherenkov::Renderer::endScene();
	}

	void onEvent(Cherenkov::Event &ev) override {
		m_CameraController.onEvent(ev);
	}

	void onImGuiDraw() override	{
		ImGui::Begin("Settings");
		ImGui::ColorPicker4("Sq. Colour", glm::value_ptr(m_ObjColour));
		ImGui::End();
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