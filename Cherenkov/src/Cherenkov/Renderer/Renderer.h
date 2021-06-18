#pragma once
#include "Cherenkov/Core.h"
namespace Cherenkov {

	enum class RendererAPI {
		None = 0, OpenGL = 1
	};

	class Renderer {
		static RendererAPI s_RendererAPI;
	public:
		inline static RendererAPI getAPI() { return s_RendererAPI; }
	};
	
}