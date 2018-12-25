#pragma once

#include "Cherenkov/Core.h"
#include "Events/Event.h"
#include "Log.h"
#include "Window.h"

namespace Cherenkov {

	class CK_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;

	};

	Application* createApplication();
}