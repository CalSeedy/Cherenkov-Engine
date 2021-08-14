#pragma once

#include "Cherenkov/Core/Layer.h"

#include "Cherenkov/Events/ApplicationEvent.h"
#include "Cherenkov/Events/KeyEvent.h"
#include "Cherenkov/Events/MouseEvent.h"

struct ImVec4;

namespace Cherenkov {

	class ImGuiLayer : public Layer {
		bool	m_Blocking = true;
		float	m_Time = 0.0f;
	public:
		struct Theme;

		enum class ColourStyle : uint32_t {
			Default,
			LightMode,
			DarkMode,
			COUNT
		};

		struct Font {
			std::string path = "";
			float_t size = 18.0f;
		};

		
		ImGuiLayer();
		~ImGuiLayer() = default;

		static bool fontChange;
		static Font font;
		static ColourStyle style;

		virtual void onAttach() override;
		virtual void onDetach() override;
		virtual void onEvent(Event& e) override;

		void start();
		void stop();
		void blockingEvents(bool blocking) { m_Blocking = blocking; }

		static void changeFonts();
		static void setTheme(ColourStyle style);
		static void initStyles();
		static std::vector<std::vector<ImVec4>> colourStyles;
		static Theme theme;
		
		static ImVec4 mixColours(const ImVec4& first, const ImVec4& second, const float mixAmount = 0.5f);
	};
}
