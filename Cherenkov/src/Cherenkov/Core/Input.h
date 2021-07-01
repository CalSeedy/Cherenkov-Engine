#pragma once

#include "Cherenkov/Core/Core.h"

namespace Cherenkov {
	
	class CK_API Input {

	public:
		inline static bool isKeyPressed(int keyCode) { return s_Instance->isKeyPressedImp(keyCode); }
	
		inline static bool isMouseButtonPressed(int button) { return s_Instance->isMouseButtonPressedImp(button); }
		inline static float getMouseY() { return s_Instance->getMouseYImp(); }
		inline static float getMouseX() { return s_Instance->getMouseXImp(); }
		inline static std::pair<float, float> getMousePos() { return s_Instance->getMousePosImp(); }




	protected:
		virtual bool isKeyPressedImp(int keyCode) = 0;
		virtual bool isMouseButtonPressedImp(int button) = 0;
		virtual float getMouseYImp() = 0;
		virtual float getMouseXImp() = 0;
		virtual std::pair<float, float> getMousePosImp() = 0;
	private:
		static Input* s_Instance;
	};
}