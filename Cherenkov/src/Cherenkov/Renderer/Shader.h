#pragma once
#include "Cherenkov/Core.h"
#include <glm/glm.hpp>

namespace Cherenkov {

	class Shader {

	public:
		virtual ~Shader() = default;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

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