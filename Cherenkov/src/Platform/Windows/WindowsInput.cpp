#include "ckpch.h"

#include "WindowsInput.h"
#include "Cherenkov/Application.h"

#include <GLFW/glfw3.h>

namespace Cherenkov {
	Input* Input::s_Instance = new WindowsInput(); //could use nullptr; and init elsewhere

	bool WindowsInput::isKeyPressedImp(int keyCode){
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().getNativeWindow());
		auto state = glfwGetKey(window, keyCode);

		return state == GLFW_PRESS || state == GLFW_RELEASE;
	}
	bool WindowsInput::isMouseButtonPressedImp(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().getNativeWindow());
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}
	std::pair<float, float> WindowsInput::getMousePosImp()
	{
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