#pragma once

#include "Cherenkov/Window.h"

#include <glfw/glfw3.h>

namespace Cherenkov {

	class WindowsWindow : public Window {

	public:
		WindowsWindow(const WindowProperties &properties);
		virtual ~WindowsWindow();

		void onUpdate() override;

		inline unsigned int getWidth() const override { return m_Data.Width; }
		inline unsigned int getHeight() const override { return m_Data.Height; }
		
		inline void setEventCallBack(const EventCallbackFn &callback) override { m_Data.EventCallback = callback; }
		void setVSync(bool enabled) override;
		bool isVSync() const override;
	
	private:
		virtual void init(const WindowProperties &properties);
		virtual void shutDown();
		
		GLFWwindow* m_Window;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};
}