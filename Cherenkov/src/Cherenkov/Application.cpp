#include "ckpch.h"
#include "Application.h"
#include "Log.h"

#include <GLFW/glfw3.h>

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

	void Application::onEvent(Event &event) {
	
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FUNC(onWindowClose));
		CK_CORE_TRACE("{0}", event);
	}

	void Application::Run() {

		while (m_Running){

			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->onUpdate();
		}
	}

	bool Application::onWindowClose(WindowCloseEvent &event)
	{
		m_Running = false;
		return true;
	}
}