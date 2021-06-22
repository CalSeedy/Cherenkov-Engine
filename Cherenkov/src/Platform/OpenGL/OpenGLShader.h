#pragma once
#include "Cherenkov/Renderer/Shader.h"

namespace Cherenkov {
	
	class OpenGLShader : public Shader {
		uint32_t m_ID;

	public:
		OpenGLShader(const std::string& vertexPath, const std::string& fragmentPath);
		virtual ~OpenGLShader();

		virtual void bind() const override;
		virtual void unbind() const override;
		
		void uniformInt(const std::string& id, int value) const;
		
		void uniformMat3(const std::string& id, const glm::mat3& matrix) const;
		void uniformMat4(const std::string& id, const glm::mat4& matrix) const;

		void uniformFloat(const std::string& id, float_t value) const;
		void uniformFloat2(const std::string& id, const glm::vec2& vector) const;
		void uniformFloat3(const std::string& id, const glm::vec3& vector) const;
		void uniformFloat4(const std::string& id, const glm::vec4& vector) const;
	};
}