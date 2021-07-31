#include "ckpch.h"
#include "Cherenkov/Core/Input.h"

#include "Cherenkov/Core/Application.h"

#include <GLFW/glfw3.h>

namespace Cherenkov {

	bool Input::isKeyPressed(KeyCode keyCode) {
		auto window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
		auto state = glfwGetKey(window, static_cast<int32_t>(keyCode));

		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool Input::isMouseButtonPressed(MouseCode button)	{
		auto window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
		auto state = glfwGetMouseButton(window, static_cast<int32_t>(button));
		return state == GLFW_PRESS;
	}

	std::pair<float, float> Input::getMousePos() {
		double xpos, ypos;
		auto window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
		glfwGetCursorPos(window, &xpos, &ypos);
		return std::pair<float, float>((float)xpos, (float)ypos);
	}

	float Input::getMouseX() {
		auto[x, y] = getMousePos();
		return x;
	}

	float Input::getMouseY() {
		auto[x, y] = getMousePos();
		return y;
	}
}