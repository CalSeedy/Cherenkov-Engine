#include "ckpch.h"
#include "Cherenkov/Core/Application.h"

#include "Cherenkov/Core/Log.h"

#include "Cherenkov/Renderer/Renderer.h"

#include "Cherenkov/Core/Input.h"

#include <GLFW/glfw3.h>
 
namespace Cherenkov {
	
	Application* Application::s_Instance = nullptr;
	 
	Application::Application() {
		CK_PROFILE_FUNCTION();
		CK_CORE_ASSERT(!s_Instance, "Application already running!");
		s_Instance = this;
		{
			CK_PROFILE_SCOPE("Window Creation");
			m_Window = Window::Create();
			m_Window->setEventCallBack(CK_BIND_EVENT_FN(Application::onEvent));
			m_Window->setVSync(false);
		}

		Renderer::init();

		m_ImGuiLayer = new ImGuiLayer();
		pushOverlay(m_ImGuiLayer);

	}

	Application::~Application()	{
		CK_PROFILE_FUNCTION();
		Renderer::shutdown();
	}

	void Application::pushLayer(Layer* layer) {
		CK_PROFILE_FUNCTION();
		m_LayerStack.PushLayer(layer);
		layer->onAttach();
	}

	void Application::pushOverlay(Layer* overlay) {
		CK_PROFILE_FUNCTION();
		m_LayerStack.PushLayer(overlay);
		overlay->onAttach();
	}

	void Application::close() {
		m_Running = false;
	}

	void Application::onEvent(Event& event) {
		CK_PROFILE_FUNCTION();
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(CK_BIND_EVENT_FN(Application::onWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(CK_BIND_EVENT_FN(Application::onWindowResize));
		//CK_CORE_TRACE("{0}", event);

		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it) {
		
			if (event.m_Handled)
				break;
			(*it)->onEvent(event);
		}

	}

	void Application::run() {
		CK_PROFILE_FUNCTION();
		while (m_Running){
			CK_PROFILE_SCOPE("Run Loop");
			float_t time = (float_t)glfwGetTime();
			Timestep dt = time - m_FrameTime;
			m_FrameTime = time;

			if (!m_Minimized) {
				CK_PROFILE_SCOPE("App Layers onUpdate");
				for (Layer* layer : m_LayerStack)
					layer->onUpdate(dt);
			}
			{
				CK_PROFILE_SCOPE("ImGUI Layer");
				m_ImGuiLayer->start();
				for (Layer* layer : m_LayerStack) {
					layer->onImGuiDraw();
				}
				m_ImGuiLayer->stop(); 
			}
			{
				CK_PROFILE_SCOPE("Window Update");
				m_Window->onUpdate();
			}
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