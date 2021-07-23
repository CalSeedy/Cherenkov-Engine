#pragma once

#include "Cherenkov/Core/Input.h"

namespace Cherenkov {
	
	class WindowsInput : public Input {

	protected:
		virtual bool isKeyPressedImp(KeyCode keyCode) override;
		
		virtual bool isMouseButtonPressedImp(MouseCode button) override;
		virtual float getMouseXImp() override;
		virtual float getMouseYImp() override;
		virtual std::pair<float, float> getMousePosImp() override;


	};
}