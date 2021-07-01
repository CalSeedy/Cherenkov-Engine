#pragma once

#include "Cherenkov/Core/Input.h"

namespace Cherenkov {
	
	class WindowsInput : public Input {

	protected:
		virtual bool isKeyPressedImp(int keyCode) override;
		
		virtual bool isMouseButtonPressedImp(int button) override;
		virtual float getMouseXImp() override;
		virtual float getMouseYImp() override;
		virtual std::pair<float, float> getMousePosImp() override;


	};
}