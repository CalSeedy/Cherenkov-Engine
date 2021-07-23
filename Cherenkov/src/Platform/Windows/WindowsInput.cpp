#include "ckpch.h"

#include "WindowsInput.h"
#include "Cherenkov/Core/Application.h"

#include <GLFW/glfw3.h>

namespace Cherenkov {

	bool WindowsInput::isKeyPressedImp(KeyCode keyCode) {
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().getNativeWindow());
		auto state = glfwGetKey(window, static_cast<int32_t>(keyCode));

		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::isMouseButtonPressedImp(MouseCode button)	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().getNativeWindow());
		auto state = glfwGetMouseButton(window, static_cast<int32_t>(button));
		return state == GLFW_PRESS;
	}

	std::pair<float, float> WindowsInput::getMousePosImp() {
		double xpos, ypos;
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().getNativeWindow());
		glfwGetCursorPos(window, &xpos, &ypos);
		return std::pair<float, float>((float)xpos, (float)ypos);
	}

	float WindowsInput::getMouseXImp()
	{
		auto[x, y] = getMousePosImp();
		return x;
	}

	float WindowsInput::getMouseYImp()
	{
		auto[x, y] = getMousePosImp();
		return y;
	}
}