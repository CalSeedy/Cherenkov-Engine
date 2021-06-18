#include "ckpch.h"
#include "OpenGLContext.h"

#include "Cherenkov/Log.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Cherenkov {

	OpenGLContext::OpenGLContext(GLFWwindow* window) : m_Window {window} {
		CK_CORE_ASSERT(window, "Null window!");
	}
	void OpenGLContext::init() {
		glfwMakeContextCurrent(m_Window);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		CK_CORE_ASSERT(status, "Failed to initialise Glad!");
	}
	void OpenGLContext::swapBuffers() {
		glfwSwapBuffers(m_Window);
	}


}