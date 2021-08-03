#pragma once

#include "Cherenkov/Core/KeyCodes.h"
#include "Cherenkov/Core/MouseCodes.h"

#include <glm/glm.hpp>

namespace Cherenkov {
	
	class Input {
	public:
		static bool isKeyPressed(KeyCode keyCode);

		static bool isMouseButtonPressed(MouseCode button);
		static float getMouseY();
		static float getMouseX();
		static glm::vec2 getMousePos();
	};
}
