#include "ckpch.h"
#include "Application.h"
#include "Log.h"

#include <glad/glad.h>


namespace Cherenkov {

#define BIND_EVENT_FUNC(x) std::bind(&Application::x, this, std::placeholders::_1)
	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->setEventCallBack(BIND_EVENT_FUNC(onEvent));
	}


	Application::~Application()
	{
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
			if (event.Handled)
				break;
		}

	}

	void Application::Run() {

		while (m_Running){

			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : m_LayerStack) {
				layer->onUpdate();
			}

			m_Window->onUpdate();
		}
	}

	bool Application::onWindowClose(WindowCloseEvent &event)
	{
		m_Running = false;
		return true;
	}
}