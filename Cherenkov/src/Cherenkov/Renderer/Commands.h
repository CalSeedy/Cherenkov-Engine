#pragma once
#include "Cherenkov/Renderer/RendererAPI.h"


namespace Cherenkov {
	class RenderCommand {

		static Scope<RendererAPI> s_RendererAPI;

	public:
		inline static void init() {
			s_RendererAPI->init();
		}

		inline static void clear(const glm::vec4& colour) {
			s_RendererAPI->clear(colour);
		}

		inline static void drawIndexed(const Ref<VertexArray>& vertexArray) {
			s_RendererAPI->drawIndexed(vertexArray);
		}

		inline static void setViewport(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2) {
			s_RendererAPI->setViewport(x1, y1, x2, y2);
		}
	};
}