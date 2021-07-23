#include "ckpch.h"
#include "Application.h"

#include "Log.h"
#include "Input.h"

#include "Cherenkov/Renderer/Renderer.h"
#include <GLFW/glfw3.h>

namespace Cherenkov {

#define BIND_EVENT_FUNC(x) std::bind(&Application::x, this, std::placeholders::_1)
	
	Application* Application::s_Instance = nullptr;
	 
	Application::Application() {
		CK_CORE_ASSERT(!s_Instance, "Application already running!");
		s_Instance = this;
		m_Window = Window::Create();
		m_Window->setEventCallBack(BIND_EVENT_FUNC(onEvent));
		m_Window->setVSync(true);

		Renderer::init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

	}

	Application::~Application()	{}

	void Application::PushLayer(Layer* layer) {
	
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay) {

		m_LayerStack.PushLayer(overlay);

	}

	void Application::onEvent(Event &event) {
	
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FUNC(onWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FUNC(onWindowResize));
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

			if (!m_Minimized) {
				for (Layer* layer : m_LayerStack)
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

	bool Application::onWindowResize(WindowResizeEvent &ev) {
		if (ev.getWidth() == 0 || ev.getHeight() == 0) m_Minimized = true;
		else m_Minimized = false;
		Renderer::onWindowResize(ev.getWidth(), ev.getHeight());
		return false;
	}

	bool Application::onWindowClose(WindowCloseEvent &ev) {
		m_Running = false;
		return true;
	}
}