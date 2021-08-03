#pragma once

#include <glm/glm.hpp>
#include "Cherenkov/Scene/SceneCamera.h"

namespace Cherenkov {

	struct TransformComp {
		glm::mat4 Transform{ 1.0f };

		TransformComp() = default;
		TransformComp(const TransformComp&) = default;
		TransformComp(const glm::mat4 transform) : Transform{ transform } {}

		operator const glm::mat4& () { return Transform; }
		operator glm::mat4() { return Transform; }
	};
	
	struct SpriteComp {
		glm::vec4 Colour;

		SpriteComp() = default;
		SpriteComp(const SpriteComp&) = default;
		SpriteComp(const glm::vec4 rgba) : Colour{ rgba } {}
		SpriteComp(const glm::vec3 rgb) : Colour{ rgb.r, rgb.g, rgb.b, 1.0f } {}
		SpriteComp(float r, float g, float b, float a) : Colour{ r, g, b, a } {}
		SpriteComp(float r, float g, float b) : Colour{ r, g, b, 1.0f } {}

	};

	struct NameComp {
		std::string Name;

		NameComp() = default;
		NameComp(const NameComp&) = default;
		NameComp(const std::string& name) : Name{ name } {}

		operator const char* () { return Name.c_str(); }
	};

	struct CameraComp {

		Cherenkov::SceneCamera Camera;
		bool fixedAspectRatio = false;

		CameraComp() = default;
		CameraComp(const CameraComp&) = default;
	};

}