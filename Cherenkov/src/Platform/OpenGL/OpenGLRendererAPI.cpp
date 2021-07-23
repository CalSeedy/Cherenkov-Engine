#include "ckpch.h"
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>
namespace Cherenkov {
	void OpenGLRendererAPI::init() {
		CK_PROFILE_FUNCTION();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);
	}

	void OpenGLRendererAPI::clear(const glm::vec4& colour) {
		glClearColor(colour.r, colour.g, colour.b, colour.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::drawIndexed(const Ref<VertexArray>& vertexArray) {
		glDrawElements(GL_TRIANGLES, vertexArray->getIndexBuffer()->count(), GL_UNSIGNED_INT, nullptr);
	}
	void OpenGLRendererAPI::setViewport(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2)	{
		glViewport(x1, y1, x2, y2);
	}
}