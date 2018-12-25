#include "ckpch.h"
#include "WindowsWindow.h"
#include "Cherenkov/Log.h"

namespace Cherenkov {

	static bool s_GLFWInit = false;

	Window* Window::Create(const WindowProperties &properties) {
	
		return new WindowsWindow(properties);
	}

	WindowsWindow::WindowsWindow(const WindowProperties &properties){
	
		init(properties);
	}

	WindowsWindow::~WindowsWindow() { shutDown(); }

	void WindowsWindow::init(const WindowProperties &properties) {
	
		m_Data.Title = properties.Title;
		m_Data.Width = properties.Width;
		m_Data.Height = properties.Height;

		CK_CORE_INFO("Creating a {0} x {1} window: \'{2}\'", properties.Width, properties.Height, properties.Title);

		if (!s_GLFWInit) {
		
			int success = glfwInit();
			CK_CORE_ASSERT(success, "Could not successfully initialise GLFW!");

			s_GLFWInit = true;
		}

		m_Window = glfwCreateWindow((int)properties.Width, (int)properties.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);
		setVSync(true);
	}

	void WindowsWindow::shutDown() {
	
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::onUpdate() {
	
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void WindowsWindow::setVSync(bool enabled) {
	
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	bool WindowsWindow::isVSync() const {
	
		return m_Data.VSync;
	}
}