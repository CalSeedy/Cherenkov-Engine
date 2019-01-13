#pragma once

#include "Cherenkov/Layer.h"
#include "Cherenkov/Events/ApplicationEvent.h"

#include "Cherenkov/Events/MouseEvent.h"
#include "Cherenkov/Events/KeyEvent.h"

namespace Cherenkov {

	class CK_API ImGuiLayer : public Layer {

	public:
		ImGuiLayer();
		~ImGuiLayer();

		void onAttach();
		void onDetatch();
		void onUpdate();
		void onEvent(Event& event);
	private:
		float m_Time = 0.0f;

		bool onMouseButtonPressedEvent(MouseButtonPressedEvent& event);
		bool onMouseButtonReleasedEvent(MouseButtonReleasedEvent& event);
		bool onMouseMovedEvent(MouseMovedEvent& event);
		bool onMouseScrollEvent(MouseScrollEvent& event);

		bool onKeyTypedEvent(KeyTypedEvent& event);
		bool onKeyReleasedEvent(KeyReleasedEvent& event);
		bool onKeyPressedEvent(KeyPressedEvent& event);
		bool onWindowResizedEvent(WindowResizeEvent& event);

	};
}