#pragma once

#include "Cherenkov/Window.h"
#include "Cherenkov/Renderer/RendererContext.h"

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
	
		inline virtual void* getNativeWindow() const { return m_Window; }
		inline void setViewport(uint32_t width, uint32_t height) const override {
			m_Ctx->setViewport(width, height);
		}
	private:
		virtual void init(const WindowProperties &properties);
		virtual void shutDown();
		
		GLFWwindow* m_Window;
		RendererContext* m_Ctx;

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