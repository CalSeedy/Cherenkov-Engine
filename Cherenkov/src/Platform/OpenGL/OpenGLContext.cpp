#include "ckpch.h"
#include "OpenGLContext.h"

#include "Cherenkov/Core/Log.h"

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
	#ifdef CK_ENABLE_ASSERTS
		int versMaj;
		int versMin;
		glGetIntegerv(GL_MAJOR_VERSION, &versMaj);
		glGetIntegerv(GL_MINOR_VERSION, &versMin);
		CK_CORE_ASSERT(versMaj > 4 || (versMaj == 4 && versMin >= 5), "Require OpenGL version >= 4.5");
	#endif
	}
	void OpenGLContext::swapBuffers() {
		CK_PROFILE_FUNCTION();
		glfwSwapBuffers(m_Window);
	}


}