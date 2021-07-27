#pragma once
#include "ckpch.h"

#include "Cherenkov/Core/Core.h"

namespace Cherenkov {
	
	enum class EventType {
		None = 0,
		WindowClosed, WindowResized, WindowFocused, WindowDefocused, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyReleased, KeyPressed, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory {
	
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput       = BIT(1),
		EventCategoryKeyBoard    = BIT(2),
		EventCategoryMouse       = BIT(3),
		EventCategoryMouseButton = BIT(4)
	};

#define EVENT_CLASS_TYPE(type)	static EventType getStaticType() { return EventType::type;}\
								virtual EventType getEventType() const override { return getStaticType(); }\
								virtual const char* getEventName() const override { return #type; }


#define EVENT_CLASS_CATEGORY(category) virtual int getCategoryFlags() const override { return category; }

	class Event {
	public:
		virtual EventType getEventType() const = 0;
		virtual const char* getEventName() const = 0;
		virtual int getCategoryFlags() const = 0;
		virtual std::string toStr() const { return getEventName(); }

		bool inCategory(EventCategory category){ return getCategoryFlags() & category; }

		bool m_Handled = false;
	};

	class EventDispatcher {

		template<typename T>
		using EventFn = std::function<bool(T&)>;
		Event& m_Event;
	public:

		EventDispatcher(Event& event) : m_Event(event) {}

		template<typename T, typename F>
		bool Dispatch(const F& func) {
		
			if (m_Event.getEventType() == T::getStaticType()) {
			
				m_Event.m_Handled = func(static_cast<T&>(m_Event));
				return true;
			}
			return false;
		}

	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e){ return os << e.toStr(); }
}
