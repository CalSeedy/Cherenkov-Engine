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
		inline void setViewport(uint32_t width, uint32_t height) const override {
			glViewport(0, 0, width, height);
		}
	};
}