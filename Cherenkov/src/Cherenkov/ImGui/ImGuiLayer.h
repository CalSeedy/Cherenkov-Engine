#pragma once

#include "Cherenkov/Layer.h"

#include "Cherenkov/Events/ApplicationEvent.h"
#include "Cherenkov/Events/KeyEvent.h"
#include "Cherenkov/Events/MouseEvent.h"

namespace Cherenkov {

	class CK_API ImGuiLayer : public Layer {

	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void onAttach() override;
		virtual void onDetach() override;
		virtual void onImGuiDraw() override;

		void start();
		void stop();
	private:
		float m_Time = 0.0f;

	};
}