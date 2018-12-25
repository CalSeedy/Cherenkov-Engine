#include "Application.h"


namespace Cherenkov {

	Application::Application()
	{
	}


	Application::~Application()
	{
	}

	void Application::Run() {

		WindowResizeEvent e(1280, 720);
		CK_TRACE(e);
		while (true);
	}
}