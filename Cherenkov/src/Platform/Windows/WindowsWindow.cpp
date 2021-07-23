#include "ckpch.h"
#include "WindowsWindow.h"
#include "Cherenkov/Core/Log.h"

#include "Cherenkov/Events/KeyEvent.h"
#include "Cherenkov/Events/ApplicationEvent.h"
#include "Cherenkov/Events/MouseEvent.h"

#include "Platform/OpenGL/OpenGLContext.h"



namespace Cherenkov {

	static uint8_t s_GLFWCount = 0;

	static void GLFWErrorCallback(int error, const char* description) {
		CK_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	Scope<Window> Window::Create(const WindowProperties &properties) {
	
		return CreateScope<WindowsWindow>(properties);
	}

	WindowsWindow::WindowsWindow(const WindowProperties &properties){
		CK_PROFILE_FUNCTION();
		init(properties);
	}

	WindowsWindow::~WindowsWindow() { 
		CK_PROFILE_FUNCTION();
		shutDown();
	}

	void WindowsWindow::init(const WindowProperties& properties) {
		CK_PROFILE_FUNCTION();
		m_Data.Title = properties.Title;
		m_Data.Width = properties.Width;
		m_Data.Height = properties.Height;

		CK_CORE_INFO("Creating a {0} x {1} window: \'{2}\'", properties.Width, properties.Height, properties.Title);

		if (s_GLFWCount == 0) {
			int success = glfwInit();
			CK_CORE_ASSERT(success, "Could not successfully initialise GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
		}
		{
			CK_PROFILE_SCOPE("glfwCreateWindow");
			m_Window = glfwCreateWindow((int)properties.Width, (int)properties.Height, m_Data.Title.c_str(), nullptr, nullptr);
		}
		s_GLFWCount++;

		m_Ctx = RendererContext::create(m_Window);
		m_Ctx->init();
		
		glfwSetWindowUserPointer(m_Window, &m_Data);
		setVSync(false);

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.Width = width;
			data.Height = height;
			
			WindowResizeEvent event(width, height);
			data.EventCallback(event);
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
			WindowData &data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.EventCallback(event);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
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
		CK_PROFILE_FUNCTION();
		glfwPollEvents();
		m_Ctx->swapBuffers();
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