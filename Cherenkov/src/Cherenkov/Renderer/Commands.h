#pragma once
#include "Cherenkov/Renderer/RendererAPI.h"


namespace Cherenkov {
	class RenderCommand {

		static Scope<RendererAPI> s_RendererAPI;

	public:
		static void init() {
			s_RendererAPI->init();
		}

		static void clear(const glm::vec4& colour) {
			s_RendererAPI->clear(colour);
		}

		static void drawIndexed(const Ref<VertexArray>& vertexArray, uint32_t idxCount = 0) {
			s_RendererAPI->drawIndexed(vertexArray, idxCount);
		}

		static void setViewport(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2) {
			s_RendererAPI->setViewport(x1, y1, x2, y2);
		}
	};
}