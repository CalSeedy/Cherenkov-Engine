#pragma once
#include "Cherenkov/Renderer/RendererAPI.h"

namespace Cherenkov {

	class OpenGLRendererAPI : public RendererAPI {

	public:
		virtual void init() override;
		virtual void clear(const glm::vec4& colour) override;
		virtual void drawIndexed(const Ref<VertexArray>& vertexArray) override;
		virtual void setViewport(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2) override;
	};
}