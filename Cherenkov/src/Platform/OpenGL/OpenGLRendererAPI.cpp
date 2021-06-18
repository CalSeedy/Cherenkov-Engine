#include "ckpch.h"
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>
namespace Cherenkov {
	void OpenGLRendererAPI::clear(const glm::vec4& colour) {
		glClearColor(colour.r, colour.g, colour.b, colour.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::drawIndexed(const std::shared_ptr<VertexArray>& vertexArray) {
		glDrawElements(GL_TRIANGLES, vertexArray->getIndexBuffer()->count(), GL_UNSIGNED_INT, nullptr);
	}
}