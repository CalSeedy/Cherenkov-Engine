#pragma once

#include "Cherenkov/Core/Layer.h"
#include "Cherenkov/Events/ApplicationEvent.h"
#include "Cherenkov/Events/KeyEvent.h"
#include "Cherenkov/Events/MouseEvent.h"

namespace Cherenkov {

	class CK_API ImGuiLayer : public Layer {
		float m_Time = 0.0f;
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void onAttach() override;
		virtual void onDetach() override;

		void start();
		void stop();
	};
}