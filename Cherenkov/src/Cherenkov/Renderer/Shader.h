#pragma once
#include "Cherenkov/Core.h"
#include <glm/glm.hpp>

namespace Cherenkov {

	class Shader {

	public:
		virtual ~Shader() = default;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		static Shader* init(const std::string& vertexPath, const std::string& fragmentPath);
		static Shader* init(const std::string& filepath);
	};
}