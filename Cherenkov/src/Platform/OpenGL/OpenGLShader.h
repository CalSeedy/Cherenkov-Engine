#pragma once
#include "Cherenkov/Renderer/Shader.h"


typedef unsigned int GLenum;

namespace Cherenkov {
	
	class OpenGLShader : public Shader {
		uint32_t m_ID;
		std::string m_Name;

		void compile(const std::unordered_map<GLenum, std::string>& shaders);
		std::unordered_map<GLenum, std::string> parse(const std::string& src);
	public:
		OpenGLShader(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath);
		OpenGLShader(const std::string& filepath);
		virtual ~OpenGLShader();

		virtual void bind() const override;
		virtual void unbind() const override;
		virtual const std::string& name() const override { return m_Name; }
		
		void uniformInt(const std::string& id, int value) const;
		
		void uniformMat3(const std::string& id, const glm::mat3& matrix) const;
		void uniformMat4(const std::string& id, const glm::mat4& matrix) const;

		void uniformFloat(const std::string& id, float_t value) const;
		void uniformFloat2(const std::string& id, const glm::vec2& vector) const;
		void uniformFloat3(const std::string& id, const glm::vec3& vector) const;
		void uniformFloat4(const std::string& id, const glm::vec4& vector) const;
	};
}