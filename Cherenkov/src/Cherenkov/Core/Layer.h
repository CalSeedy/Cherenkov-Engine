#pragma once

#include "Cherenkov/Core/Core.h"
#include "Cherenkov/Events/Event.h"
#include "Cherenkov/Core/TimeStep.h"

namespace Cherenkov {

	class CK_API Layer {

	public:
		Layer(const std::string &name = "Layer");
		virtual ~Layer();

		virtual void onAttach() {}
		virtual void onDetach() {}
		virtual void onUpdate(Timestep dt) {}
		virtual void onImGuiDraw() {}
		virtual void onEvent(Event &event) {}

		inline const std::string &getName() const { return m_DebugName; }

	protected:
		std::string m_DebugName;
	};

}