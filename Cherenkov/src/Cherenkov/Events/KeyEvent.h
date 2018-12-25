#pragma once

#include "Event.h"

#include <sstream>

namespace Cherenkov {

	class CK_API KeyEvent : public Event {

	public:
		inline int getKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyBoard | EventCategoryInput)
	protected:
		KeyEvent(int code) : m_KeyCode(code) {}

		int m_KeyCode;
	};

	class CK_API KeyPressedEvent : public KeyEvent {

		KeyPressedEvent(int code, int repeats) 
			: KeyEvent(code), m_Repeats(repeats) {}

		inline int getRepeats() const { return m_Repeats; }

		std::string toStr() const override {
			std::stringstream stream;
			stream << "KeyPressedEvent: " << m_KeyCode << " (" << m_Repeats << " repeats)";
			return stream.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	private:
		int m_Repeats;
	};

	class CK_API KeyReleasedEvent : public KeyEvent {

	public:
		KeyReleasedEvent(int code) : KeyEvent(code) {}

		std::string toStr() const override {
			std::stringstream stream;
			stream << "KeyReleasedEvent: " << m_KeyCode;
			return stream.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};
}