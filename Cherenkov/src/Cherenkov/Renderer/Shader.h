#pragma once
#include <string>
#include <unordered_map>

#include <glm/glm.hpp>

namespace Cherenkov {

	class Shader {

	public:
		virtual ~Shader() = default;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual void setInt(const std::string& name, int32_t vector) = 0;
		virtual void setIntArray(const std::string& name, int32_t* values, uint32_t count) = 0;
		virtual void setFloat(const std::string& name, float_t vector) = 0;
		virtual void setFloat2(const std::string& name, const glm::vec2& vector) = 0;
		virtual void setFloat3(const std::string& name, const glm::vec3& vector) = 0;
		virtual void setFloat4(const std::string& name, const glm::vec4& vector) = 0;
		virtual void setMat3(const std::string& name, const glm::mat3& matrix) = 0;
		virtual void setMat4(const std::string& name, const glm::mat4& matrix) = 0;

		virtual const std::string& name() const = 0;

		static Ref<Shader> init(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath);
		static Ref<Shader> init(const std::string& filepath);
	};


	class ShaderLibrary {
		std::unordered_map<std::string, Ref<Shader>> m_Shaders;

	public: 
		void add(const std::string& name, const Ref<Shader>& shader);
		void add(const Ref<Shader>& shader);
		Ref<Shader> load(const std::string& path);
		Ref<Shader> load(const std::string& name, const std::string& path);

		Ref<Shader> get(const std::string& name);
	};
}