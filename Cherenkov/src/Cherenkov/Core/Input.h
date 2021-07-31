#pragma once

#include "Cherenkov/Core/Core.h"
#include "Cherenkov/Core/KeyCodes.h"
#include "Cherenkov/Core/MouseCodes.h"

namespace Cherenkov {
	
	class Input {
	public:
		static bool isKeyPressed(KeyCode keyCode);

		static bool isMouseButtonPressed(MouseCode button);
		static float getMouseY();
		static float getMouseX();
		static std::pair<float, float> getMousePos();
	};
}