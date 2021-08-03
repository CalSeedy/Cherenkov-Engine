#include "ckpch.h"
#include "Cherenkov/Core/Input.h"

#include "Cherenkov/Core/Application.h"

#include <GLFW/glfw3.h>

namespace Cherenkov {

	bool Input::isKeyPressed(const KeyCode keyCode) {
		auto window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
		auto state = glfwGetKey(window, static_cast<int32_t>(keyCode));

		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool Input::isMouseButtonPressed(const MouseCode button)	{
		auto window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
		auto state = glfwGetMouseButton(window, static_cast<int32_t>(button));
		return state == GLFW_PRESS;
	}

	glm::vec2 Input::getMousePos() {
		double xpos, ypos;
		auto window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
		glfwGetCursorPos(window, &xpos, &ypos);
		return { (float)xpos, (float)ypos };
	}

	float Input::getMouseX() {
		return getMousePos().x;
	}

	float Input::getMouseY() {
		return getMousePos().y;
	}
}
