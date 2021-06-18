#include "ckpch.h"
#include "Application.h"
#include "Log.h"
#include "Input.h"

#include "Platform/OpenGL/OpenGLShader.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

#include <glad/glad.h>


namespace Cherenkov {

#define BIND_EVENT_FUNC(x) std::bind(&Application::x, this, std::placeholders::_1)
	
	Application* Application::s_Instance = nullptr;

	static GLenum getBaseType(ShaderDataType type) {
		switch (type)
		{
		case Cherenkov::ShaderDataType::None:			return GL_NONE;
		case Cherenkov::ShaderDataType::Float:			return GL_FLOAT;
		case Cherenkov::ShaderDataType::Int:			return GL_INT;
		case Cherenkov::ShaderDataType::Bool:			return GL_BOOL;
		//case Cherenkov::ShaderDataType::Struct:			break;
		case Cherenkov::ShaderDataType::Vec2f:			return GL_FLOAT;
		case Cherenkov::ShaderDataType::Vec3f:			return GL_FLOAT;
		case Cherenkov::ShaderDataType::Vec4f:			return GL_FLOAT;
		case Cherenkov::ShaderDataType::Mat2f:			return GL_FLOAT;
		case Cherenkov::ShaderDataType::Mat3f:			return GL_FLOAT;
		case Cherenkov::ShaderDataType::Mat4f:			return GL_FLOAT;
		case Cherenkov::ShaderDataType::Vec2i:			return GL_INT;
		case Cherenkov::ShaderDataType::Vec3i:			return GL_INT;
		case Cherenkov::ShaderDataType::Vec4i:			return GL_INT;
		case Cherenkov::ShaderDataType::Mat2i:			return GL_INT;
		case Cherenkov::ShaderDataType::Mat3i:			return GL_INT;
		case Cherenkov::ShaderDataType::Mat4i:			return GL_INT;
		default:
			CK_CORE_ASSERT(false, "Unknown DataType {0}!", type);
			return 0;
		}
	}

	Application::Application()
	{
		CK_CORE_ASSERT(!s_Instance, "Application already running!");
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->setEventCallBack(BIND_EVENT_FUNC(onEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		float verts[3 * 7] = {
			-0.7f, -0.7f, 0.0f,	1.0f, 0.5f, 0.63f, 1.0f,
			 0.7f, -0.7f, 0.0f,	1.0f, 0.5f, 0.63f, 1.0f,
			  0.0f, 0.7f, 0.0f,	1.0f, 0.5f, 0.63f, 1.0f
		};

		m_VertexBuffer.reset(VertexBuffer::init(verts, sizeof(verts)/ sizeof(float_t)));

		BufferLayout layout = {
			{ShaderDataType::Vec3f, "a_Pos"},
			{ShaderDataType::Vec4f, "a_Col"}
		};

		m_VertexBuffer->layout(layout);
		uint32_t idx = 0;
		for (auto& element : m_VertexBuffer->getLayout()) {
			glEnableVertexAttribArray(idx);
			glVertexAttribPointer(idx, element.count(), getBaseType(element.Type), element.Normalised ? GL_TRUE : GL_FALSE, layout.stride(), (const void*)element.Offset);
			idx++;
		}
		//glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);		

		uint32_t idxs[3] = { 0, 1, 2 };
		m_IndexBuffer.reset(IndexBuffer::init(idxs, sizeof(idxs)/sizeof(uint32_t)));

		const char* vertIn("../Cherenkov/src/Cherenkov/Shaders/shader.vert");
		const char* fragIn("../Cherenkov/src/Cherenkov/Shaders/shader.frag");

		m_Shader.reset(new OpenGLShader(vertIn, fragIn));
	}


	Application::~Application()
	{
	}

	void Application::PushLayer(Layer* layer) {
	
		m_LayerStack.PushLayer(layer);
		layer->onAttach();
	}

	void Application::PushOverlay(Layer* overlay) {

		m_LayerStack.PushLayer(overlay);
		overlay->onAttach();

	}

	void Application::onEvent(Event &event) {
	
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FUNC(onWindowClose));
		//CK_CORE_TRACE("{0}", event);

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
		
			(*--it)->onEvent(event);
			if (event.isHandled())
				break;
		}

	}

	void Application::Run() {

		while (m_Running){

			glClearColor(0.27f, 0.27f, 0.27f, 1.0);
			glClear(GL_COLOR_BUFFER_BIT);

			m_Shader->bind();
			glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, m_IndexBuffer->count(), GL_UNSIGNED_INT, nullptr);

			for (Layer* layer : m_LayerStack) {
				layer->onUpdate();
			}
			
			m_ImGuiLayer->start();
			for (Layer* layer : m_LayerStack) {
				layer->onImGuiDraw();
			}
			m_ImGuiLayer->stop();

			m_Window->onUpdate();
		}
	}

	bool Application::onWindowClose(WindowCloseEvent &event)
	{
		m_Running = false;
		return true;
	}
}