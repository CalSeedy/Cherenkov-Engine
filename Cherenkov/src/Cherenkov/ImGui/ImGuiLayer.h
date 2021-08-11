#pragma once

#include "Cherenkov/Core/Layer.h"

#include "Cherenkov/Events/ApplicationEvent.h"
#include "Cherenkov/Events/KeyEvent.h"
#include "Cherenkov/Events/MouseEvent.h"

namespace Cherenkov {

	class ImGuiLayer : public Layer {
		bool	m_Blocking = true;
		float	m_Time = 0.0f;

	public:
		struct Font {
			std::string path;
			float_t size;
		};

		ImGuiLayer();
		~ImGuiLayer() = default;

		static bool fontChange;
		static Font font;

		virtual void onAttach() override;
		virtual void onDetach() override;
		virtual void onEvent(Event& e) override;

		void start();
		void stop();
		void blockingEvents(bool blocking) { m_Blocking = blocking; }

		static void changeFonts();
	};
}
