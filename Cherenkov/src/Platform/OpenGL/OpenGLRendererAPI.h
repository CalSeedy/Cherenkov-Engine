#pragma once
#include "Cherenkov/Renderer/RendererAPI.h"

namespace Cherenkov {

	class OpenGLRendererAPI : public RendererAPI {

	public:
		virtual void init() override;
		virtual void clear(const glm::vec4& colour) override;
		virtual void drawIndexed(const Ref<VertexArray>& vertexArray) override;
	};
}