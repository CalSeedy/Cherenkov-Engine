#pragma once
#include "RendererAPI.h"


namespace Cherenkov {
	class RenderCommand {

		static RendererAPI* s_RendererAPI;

	public:
		inline static void clear(const glm::vec4& colour) {
			s_RendererAPI->clear(colour);
		}

		inline static void drawIndexed(const Ref<VertexArray>& vertexArray) {
			s_RendererAPI->drawIndexed(vertexArray);
		}
	};
}