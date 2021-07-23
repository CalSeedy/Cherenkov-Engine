#pragma once

#include "Cherenkov/Core/Core.h"

#include "Cherenkov/Core/KeyCodes.h"
#include "Cherenkov/Core/MouseCodes.h"

namespace Cherenkov {
	
	class Input {

	public:
		inline static bool isKeyPressed(KeyCode keyCode) { return s_Instance->isKeyPressedImp(keyCode); }
	
		inline static bool isMouseButtonPressed(MouseCode button) { return s_Instance->isMouseButtonPressedImp(button); }
		inline static float getMouseY() { return s_Instance->getMouseYImp(); }
		inline static float getMouseX() { return s_Instance->getMouseXImp(); }
		inline static std::pair<float, float> getMousePos() { return s_Instance->getMousePosImp(); }




	protected:
		virtual bool isKeyPressedImp(KeyCode keyCode) = 0;
		virtual bool isMouseButtonPressedImp(MouseCode button) = 0;
		virtual float getMouseYImp() = 0;
		virtual float getMouseXImp() = 0;
		virtual std::pair<float, float> getMousePosImp() = 0;
	private:
		static Scope<Input> s_Instance;
	};
}