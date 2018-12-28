#pragma once
#include "Cherenkov/Core.h"

namespace Cherenkov {
	
	enum class EventType {
		None = 0,
		WindowClosed, WindowResized, WindowFocused, WindowDefocused, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyReleased, KeyPressed,
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

#define EVENT_CLASS_TYPE(type) static EventType getStaticType() { return EventType::##type;}\
	virtual EventType getEventType() const override { return getStaticType(); }\
	virtual const char* getEventName() const override { return #type; }


#define EVENT_CLASS_CATEGORY(category) virtual int getCategoryFlags() const override { return category; }

	class CK_API Event {

		friend class EventDispatcher;
	public:
		virtual EventType getEventType() const = 0;
		virtual const char* getEventName() const = 0;
		virtual int getCategoryFlags() const = 0;
		virtual std::string toStr() const { return getEventName(); }

		inline bool inCategory(EventCategory category){
			
			return getCategoryFlags() & category;
		}

		bool m_Handled = false;
	};

	class EventDispatcher {

		template<typename T>
		using EventFn = std::function<bool(T&)>;

	public:

		EventDispatcher(Event& event) : m_Event(event) {
		}

		template<typename T>
		bool Dispatch(EventFn<T> func) {
		
			if (m_Event.getEventType() == T::getStaticType()) {
			
				m_Event.m_Handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}

	private:
		Event& m_Event;

	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.toStr();
	}


}