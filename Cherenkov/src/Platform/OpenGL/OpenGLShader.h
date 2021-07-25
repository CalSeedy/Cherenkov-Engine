#pragma once
#include "Cherenkov/Renderer/Shader.h"
#include <glm/glm.hpp>

typedef unsigned int GLenum;

namespace Cherenkov {
	
	class OpenGLShader : public Shader {
		uint32_t m_ID;
		std::string m_Name;

		static std::string readFile(const char* filepath);
		void compile(const std::unordered_map<GLenum, std::string>& shaders);
		std::unordered_map<GLenum, std::string> preProcess(const std::string& src);
	public:
		OpenGLShader(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath);
		OpenGLShader(const std::string& filepath);
		virtual ~OpenGLShader();

		void bind() const override;
		void unbind() const override;

		void setInt(const std::string& name, int32_t vector) override;
		void setFloat(const std::string& name, float_t vector) override;
		void setFloat2(const std::string& name, const glm::vec2& vector) override;
		void setFloat3(const std::string& name, const glm::vec3& vector) override;
		void setFloat4(const std::string& name, const glm::vec4& vector) override;
		void setMat3(const std::string& name, const glm::mat3& matrix) override;
		void setMat4(const std::string& name, const glm::mat4& matrix) override;

		const std::string& name() const override { return m_Name; }
		
		void uploadUniformInt(const std::string& id, int32_t value) const;
		
		void uploadUniformMat3(const std::string& id, const glm::mat3& matrix) const;
		void uploadUniformMat4(const std::string& id, const glm::mat4& matrix) const;

		void uploadUniformFloat(const std::string& id, float_t value) const;
		void uploadUniformFloat2(const std::string& id, const glm::vec2& vector) const;
		void uploadUniformFloat3(const std::string& id, const glm::vec3& vector) const;
		void uploadUniformFloat4(const std::string& id, const glm::vec4& vector) const;
	};
}