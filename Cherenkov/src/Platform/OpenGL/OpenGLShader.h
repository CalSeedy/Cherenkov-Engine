#pragma once
#include "Cherenkov/Renderer/Shader.h"

namespace Cherenkov {
	
	class OpenGLShader : public Shader {
		uint32_t m_ID;

	public:
		OpenGLShader(const char* vertexPath, const char* fragmentPath);
		~OpenGLShader();

		void bind() const override;
		void unbind() const override;
		void uniformMat4(const std::string& id, const glm::mat4& matrix) const override;
	};
}