#include "ckpch.h"
#include "Application.h"

#include "Log.h"
#include "Renderer/Renderer.h"
#include "Input.h"
#include <GLFW/glfw3.h>

namespace Cherenkov {

#define BIND_EVENT_FUNC(x) std::bind(&Application::x, this, std::placeholders::_1)
	
	Application* Application::s_Instance = nullptr;
	 
	Application::Application() {
		CK_CORE_ASSERT(!s_Instance, "Application already running!");
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->setEventCallBack(BIND_EVENT_FUNC(onEvent));
		m_Window->setVSync(true);


		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

	}


	Application::~Application()	{
	}

	void Application::PushLayer(Layer* layer) {
	
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay) {

		m_LayerStack.PushLayer(overlay);

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
			float_t time = (float_t)glfwGetTime();
			Timestep dt = time - m_FrameTime;
			m_FrameTime = time;

			for (Layer* layer : m_LayerStack) {
				layer->onUpdate(dt);
			}
			
			m_ImGuiLayer->start();
			for (Layer* layer : m_LayerStack) {
				layer->onImGuiDraw();
			}
			m_ImGuiLayer->stop();

			m_Window->onUpdate();
		}
	}

	bool Application::onWindowClose(WindowCloseEvent &event) {
		m_Running = false;
		return true;
	}
}