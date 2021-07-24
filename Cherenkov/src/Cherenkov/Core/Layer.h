#pragma once

#include "Cherenkov/Core/Core.h"
#include "Cherenkov/Core/TimeStep.h"
#include "Cherenkov/Events/Event.h"

namespace Cherenkov {

	class Layer {

	public:
		Layer(const std::string &name = "Layer");
		virtual ~Layer() = default;

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