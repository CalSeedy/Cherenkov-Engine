#pragma once
#include "Commands.h"

namespace Cherenkov {

	class Renderer {
	public:
		inline static RendererAPI::API getAPI() { return RendererAPI::getAPI(); }

		static void beginScene();
		static void endScene();
		static void submit(const std::shared_ptr<VertexArray>& vertexArray);
	};
	
}