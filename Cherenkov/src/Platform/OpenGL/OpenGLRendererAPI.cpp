#include "ckpch.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

#include <glad/glad.h>
namespace Cherenkov {

	void OpenGLCallback(unsigned source, unsigned type, unsigned id, unsigned severity, int length, const char* message, const void* userParam) {
		switch (severity){
		case GL_DEBUG_SEVERITY_HIGH:			CK_CORE_FATAL(message); return;
		case GL_DEBUG_SEVERITY_MEDIUM:			CK_CORE_ERROR(message); return;
		case GL_DEBUG_SEVERITY_LOW:				CK_CORE_WARN(message); return;
		case GL_DEBUG_SEVERITY_NOTIFICATION:	CK_CORE_TRACE(message); return;
		default:								CK_CORE_ASSERT(false, "Unknown severity!"); return;
		}
	}


	void OpenGLRendererAPI::init() {
		CK_PROFILE_FUNCTION();

		#ifdef CK_DEBUG
			glEnable(GL_DEBUG_OUTPUT);
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
			glDebugMessageCallback(OpenGLCallback, nullptr);
			glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
		#endif

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);
	}

	void OpenGLRendererAPI::clear(const glm::vec4& colour) {
		glClearColor(colour.r, colour.g, colour.b, colour.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::drawIndexed(const Ref<VertexArray>& vertexArray, uint32_t idxCount) {
		uint32_t count = idxCount ?  idxCount : vertexArray->getIndexBuffer()->count();
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	void OpenGLRendererAPI::setViewport(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2)	{
		glViewport(x1, y1, x2, y2);
	}
}