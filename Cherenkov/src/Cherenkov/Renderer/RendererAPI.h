#pragma once
#include <glm/glm.hpp>

#include "VertexArray.h"

namespace Cherenkov {
	class RendererAPI {
	public:
		enum class API {
			None = 0, OpenGL = 1
		};
		virtual void clear(const glm::vec4& colour) = 0;
		virtual void drawIndexed(const Ref<VertexArray>& vertexArray) = 0;
		inline static API getAPI() { return s_API; }

	private:
		static API s_API;
	};

}