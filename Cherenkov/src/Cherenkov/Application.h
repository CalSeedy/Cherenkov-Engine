#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Window.h"

namespace Cherenkov {

	class CK_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void onEvent(Event &event);
	private:
		bool onWindowClose(WindowCloseEvent &event);
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;

	};

	Application* createApplication();
}