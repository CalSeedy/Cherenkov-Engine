#pragma once

#include "Cherenkov/Core.h"
#include "Cherenkov/Events/Event.h"

namespace Cherenkov {

	struct CK_API WindowProperties
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProperties(const std::string &title = "Cherenkov Engine",
			unsigned int width = 1280,
			unsigned int height = 720) : Title(title), Width(width), Height(height)
		{
		}
	};

	class CK_API Window {

	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}
		virtual void onUpdate() = 0;

		virtual unsigned int getWidth() const = 0;
		virtual unsigned int getHeight() const = 0;

		virtual void setEventCallBack(const EventCallbackFn &callback) = 0;
		virtual void setVSync(bool enabled) = 0;
		virtual bool isVSync() const = 0;

		virtual void* getNativeWindow() const = 0;
		virtual void setViewport(uint32_t width, uint32_t height) const = 0;

		static Window* Create(const WindowProperties &properties = WindowProperties());
	}; 

}