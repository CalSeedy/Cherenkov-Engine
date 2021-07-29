#pragma once

#include "Cherenkov/Events/Event.h"

namespace Cherenkov {

	class WindowResizeEvent : public Event {
		uint32_t m_Width, m_Height;
	public:
		WindowResizeEvent(uint32_t width, uint32_t height)
			: m_Width(width), m_Height(height) {}

		uint32_t getWidth() const { return m_Width; }
		uint32_t getHeight() const { return m_Height; }

		std::string toStr() const override {
			std::stringstream stream;
			stream << "WindowResizeEvent: " << m_Width << ", " << m_Height;
			return stream.str();
		}

		EVENT_CLASS_CATEGORY(EventCategoryApplication)
		EVENT_CLASS_TYPE(WindowResized)		
	};

	class WindowCloseEvent : public Event {

	public:
		WindowCloseEvent() {}

		EVENT_CLASS_CATEGORY(EventCategoryApplication)
		EVENT_CLASS_TYPE(WindowClosed)
	};

	class AppTickEvent : public Event {

	public:
		AppTickEvent() {}

		EVENT_CLASS_CATEGORY(EventCategoryApplication)
		EVENT_CLASS_TYPE(AppTick)
	};


	class AppUpdateEvent : public Event {

	public:
		AppUpdateEvent() {}

		EVENT_CLASS_CATEGORY(EventCategoryApplication)
		EVENT_CLASS_TYPE(AppUpdate)
	};

	class AppRenderEvent : public Event {

	public:
		AppRenderEvent() {}

		EVENT_CLASS_CATEGORY(EventCategoryApplication)
		EVENT_CLASS_TYPE(AppRender)
	};
}
