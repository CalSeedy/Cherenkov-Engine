#pragma once
#include "Cherenkov/Renderer/RendererContext.h"
#include <glad/glad.h>


struct GLFWwindow;

namespace Cherenkov {
	class OpenGLContext : public RendererContext {
		GLFWwindow* m_Window;
	public:
		OpenGLContext(GLFWwindow* window);
		virtual void init() override;
		virtual void swapBuffers() override;
	};
}