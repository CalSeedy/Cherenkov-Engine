#pragma once

#include "Cherenkov/Layer.h"

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
	};
}