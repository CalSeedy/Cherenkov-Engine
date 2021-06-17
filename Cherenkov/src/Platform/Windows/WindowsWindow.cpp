#include "ckpch.h"
#include "WindowsWindow.h"
#include "Cherenkov/Log.h"

#include "Cherenkov/Events/KeyEvent.h"
#include "Cherenkov/Events/ApplicationEvent.h"
#include "Cherenkov/Events/MouseEvent.h"

#include <glad/glad.h>

namespace Cherenkov {

	static bool s_GLFWInit = false;

	static void GLFWErrorCallback(int error, const char* description) {
		CK_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

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
			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInit = true;
		}

		m_Window = glfwCreateWindow((int)properties.Width, (int)properties.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		CK_CORE_ASSERT(status, "Failed to initialise Glad!");
		glfwSetWindowUserPointer(m_Window, &m_Data);
		setVSync(true);

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow *window, int width, int height) {
			WindowData &data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.Width = width;
			data.Height = height;
			
			WindowResizeEvent event(width, height);
			data.EventCallback(event);
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow *window) {
			WindowData &data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.EventCallback(event);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow *window, int key, int scancode, int action, int mods) {
			WindowData &data = *(WindowData*)glfwGetWindowUserPointer(window);
			
			switch (action) {
			case GLFW_PRESS:
			{
				KeyPressedEvent event(key, 0);
				data.EventCallback(event);
				break;
			}
			case GLFW_REPEAT:
			{
				KeyPressedEvent event(key, 1);
				data.EventCallback(event);
				break;
			}
			case GLFW_RELEASE:
			{
				KeyReleasedEvent event(key);
				data.EventCallback(event);
				break;
			}
			}
		});

		glfwSetCharCallback(m_Window, [](GLFWwindow *window, unsigned int keycode) {
			WindowData &data = *(WindowData*)glfwGetWindowUserPointer(window);

			KeyTypedEvent event(keycode);
			data.EventCallback(event);

		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow *window, int button, int action, int mods) {
			WindowData &data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action) {
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow *window, double xOff, double yOff) {
		
			WindowData &data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrollEvent event((float)xOff, (float)yOff);
			data.EventCallback(event);
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow *window, double x, double y) {

			WindowData &data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float)x, (float)y);
			data.EventCallback(event);
		});
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