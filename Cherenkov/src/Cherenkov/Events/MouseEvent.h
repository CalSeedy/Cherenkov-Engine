#pragma once

#include "Event.h"

namespace Cherenkov {

	//Mouse Movement Events
	class CK_API MouseMovedEvent : public Event {

	public:
		MouseMovedEvent(float x, float y) : m_X(x), m_Y(y) {}

		inline float getX() const { return m_X; }
		inline float getY() const { return m_Y; }

		std::string toStr() const override {
			std::stringstream stream;
			stream << "MouseMoveEvent: " << m_X << ", "<< m_Y;
			return stream.str();
		}

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
		EVENT_CLASS_TYPE(MouseMoved)
	private:
		float m_X, m_Y;
	};


	//Mouse Scroll Events
	class CK_API MouseScrollEvent : public Event {

	public:
		MouseScrollEvent(float xOff, float yOff) : m_XOff(xOff), m_YOff(yOff) {}

		inline float getXOffset() const { return m_XOff; }
		inline float getYOffset() const { return m_YOff; }

		std::string toStr() const override {
			std::stringstream stream;
			stream << "MouseScrollEvent: " << getXOffset() << ", " << getYOffset();
			return stream.str();
		}

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
		EVENT_CLASS_TYPE(MouseScrolled)

	private:
		float m_XOff, m_YOff;
	};


	//Mouse Button Events
	class CK_API MouseButtonEvent : public Event {

	public:
		inline int getMouseButton() const { return m_Button; }

		EVENT_CLASS_CATEGORY(EventCategoryMouseButton | EventCategoryMouse | EventCategoryInput)
	
	protected:
		MouseButtonEvent(int button) : m_Button(button) {}

		int m_Button;
	};

	class CK_API MouseButtonPressedEvent : public MouseButtonEvent {

	public:
		MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {}

		std::string toStr() const override {
			std::stringstream stream;
			stream << "MouseButtonPressedEvent: " << m_Button;
			return stream.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class CK_API MouseButtonReleasedEvent : public MouseButtonEvent {

	public:
		MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {}

		std::string toStr() const override {
			std::stringstream stream;
			stream << "MouseButtonReleasedEvent: " << m_Button;
			return stream.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
}