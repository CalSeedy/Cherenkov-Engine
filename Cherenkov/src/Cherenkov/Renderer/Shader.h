#pragma once
#include "Cherenkov/Core.h"
#include <glm/glm.hpp>

namespace Cherenkov {

	class Shader {

	public:
		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual void uniformMat4(const std::string& id, const glm::mat4& matrix) const = 0;
	};
}