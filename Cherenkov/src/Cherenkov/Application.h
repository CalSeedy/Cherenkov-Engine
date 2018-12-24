#pragma once

#include "core.h"

namespace Cherenkov {

	class CK_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	Application* createApplication();
}