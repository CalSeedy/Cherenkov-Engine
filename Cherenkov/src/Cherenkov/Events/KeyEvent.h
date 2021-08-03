#pragma once

#include "Cherenkov/Events/Event.h"
#include "Cherenkov/Core/KeyCodes.h"

namespace Cherenkov {

	class KeyEvent : public Event {

	public:
		KeyCode getKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyBoard | EventCategoryInput)
	protected:
		KeyEvent(const KeyCode code) : m_KeyCode(code) {}

		KeyCode m_KeyCode;
	};

	class KeyPressedEvent : public KeyEvent {
		uint16_t m_Repeats;
	public:
		KeyPressedEvent(const KeyCode code, uint16_t repeats) 
			: KeyEvent(code), m_Repeats(repeats) {}

		uint16_t getRepeats() const { return m_Repeats; }

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
		KeyTypedEvent(const KeyCode code)
			: KeyEvent(code){}

		std::string toStr() const override {
			std::stringstream stream;
			stream << "KeyTypedEvent: " << m_KeyCode;
			return stream.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)
	};
}
