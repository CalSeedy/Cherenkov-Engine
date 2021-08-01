#pragma once

#include "Cherenkov/Events/Event.h"
#include "Cherenkov/Core/Input.h"

namespace Cherenkov {

	class KeyEvent : public Event {

	public:
		KeyCode getKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyBoard | EventCategoryInput)
	protected:
		KeyEvent(KeyCode code) : m_KeyCode(code) {}

		KeyCode m_KeyCode;
	};

	class KeyPressedEvent : public KeyEvent {
		int m_Repeats;
	public:
		KeyPressedEvent(KeyCode code, int repeats) 
			: KeyEvent(code), m_Repeats(repeats) {}

		int getRepeats() const { return m_Repeats; }

		std::string toStr() const override {
			std::stringstream stream;
			stream << "KeyPressedEvent: " << m_KeyCode << " (" << m_Repeats << " repeats)";
			return stream.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	};

	class KeyReleasedEvent : public KeyEvent {

	public:
		KeyReleasedEvent(KeyCode code) : KeyEvent(code) {}

		std::string toStr() const override {
			std::stringstream stream;
			stream << "KeyReleasedEvent: " << m_KeyCode;
			return stream.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

	class KeyTypedEvent : public KeyEvent {

	public:
		KeyTypedEvent(KeyCode code)
			: KeyEvent(code){}

		std::string toStr() const override {
			std::stringstream stream;
			stream << "KeyTypedEvent: " << m_KeyCode;
			return stream.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)
	};
}