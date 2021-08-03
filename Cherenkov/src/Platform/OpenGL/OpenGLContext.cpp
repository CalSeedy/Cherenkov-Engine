#include "ckpch.h"
#include "Platform/OpenGL/OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Cherenkov {

	OpenGLContext::OpenGLContext(GLFWwindow* window) : m_Window {window} {
		CK_CORE_ASSERT(window, "Null window!");
	}

	void OpenGLContext::init() {
		CK_PROFILE_FUNCTION();
		glfwMakeContextCurrent(m_Window);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		CK_CORE_ASSERT(status, "Failed to initialise Glad!");

		CK_CORE_INFO("Renderer (OpenGL): {0} {1} (Version: {2})", glGetString(GL_VENDOR), glGetString(GL_RENDERER), glGetString(GL_VERSION));
		CK_CORE_ASSERT(GLVersion.major > 4 || (GLVersion.major == 4 && GLVersion.minor >= 5), "Cherenkov requires at least OpenGL version 4.5!");
	}

	void OpenGLContext::swapBuffers() {
		CK_PROFILE_FUNCTION();
		glfwSwapBuffers(m_Window);
	}


}
