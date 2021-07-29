#pragma once

#include "Cherenkov/Core/Window.h"
#include "Cherenkov/Renderer/RendererContext.h"

#include <glfw/glfw3.h>

namespace Cherenkov {

	class WindowsWindow : public Window {
		virtual void init(const WindowProperties& properties);
		virtual void shutDown();

		GLFWwindow* m_Window;
		Scope<RendererContext> m_Ctx;

		struct WindowData
		{
			std::string Title;
			uint32_t Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	public:
		WindowsWindow(const WindowProperties &properties);
		virtual ~WindowsWindow();

		void onUpdate() override;

		uint32_t getWidth() const override { return m_Data.Width; }
		uint32_t getHeight() const override { return m_Data.Height; }

		inline void setEventCallBack(const EventCallbackFn &callback) override { m_Data.EventCallback = callback; }
		void setVSync(bool enabled) override;
		bool isVSync() const override;
	
		virtual void* getNativeWindow() const { return m_Window; }

	};
}