#include "ckpch.h"
#include "Application.h"


namespace Cherenkov {

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}


	Application::~Application()
	{
	}

	void Application::Run() {

		while (m_Running){

			m_Window->onUpdate();
		}
	}
}