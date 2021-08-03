#pragma once
#include "Cherenkov/Core/Core.h"
#include "Cherenkov/Events/Event.h"

#include <sstream>

namespace Cherenkov {

	struct WindowProperties
	{
		std::string Title;
		uint32_t Width;
		uint32_t Height;

		WindowProperties(const std::string& title = "Cherenkov Engine",
			uint32_t width = 1280,
			uint32_t height = 720) : Title(title), Width(width), Height(height)
		{
		}
	};

	class Window {

	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}
		virtual void onUpdate() = 0;

		virtual uint32_t getWidth() const = 0;
		virtual uint32_t getHeight() const = 0;

		virtual void setEventCallBack(const EventCallbackFn &callback) = 0;
		virtual void setVSync(bool enabled) = 0;
		virtual bool isVSync() const = 0;

		virtual void* getNativeWindow() const = 0;

		static Scope<Window> Create(const WindowProperties& properties = WindowProperties());
	}; 

}
