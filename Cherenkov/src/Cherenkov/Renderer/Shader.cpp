#include "ckpch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Cherenkov {
	
	Ref<Shader> Shader::init(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath) {
		switch (Renderer::getAPI()) {
		case RendererAPI::API::None:		return nullptr;
		case RendererAPI::API::OpenGL:		return std::make_shared<OpenGLShader>(name, vertexPath, fragmentPath);
		default:
			CK_CORE_ASSERT(false, "Unknown Renderer!");
			return nullptr;
		}

	}

	Ref<Shader> Shader::init(const std::string& filepath) {
		switch (Renderer::getAPI()) {
		case RendererAPI::API::None:		return nullptr;
		case RendererAPI::API::OpenGL:		return std::make_shared<OpenGLShader>(filepath);
		default:
			CK_CORE_ASSERT(false, "Unknown Renderer!");
			return nullptr;
		}
		return nullptr;
	}

	void ShaderLibrary::add(const std::string& name, const Ref<Shader>& shader) {
		CK_CORE_ASSERT(m_Shaders.find(name) == m_Shaders.end(), "Shader already exists!");
		m_Shaders[name] = shader;
	}

	void ShaderLibrary::add(const Ref<Shader>& shader) {
		auto& name = shader->name();
		add(name, shader);
	}

	Ref<Shader> ShaderLibrary::load(const std::string& path) {
		auto shader = Shader::init(path);
		add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::load(const std::string& name, const std::string& path) {
		auto shader = Shader::init(path);
		add(name, shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::get(const std::string& name) {
		CK_CORE_ASSERT(m_Shaders.find(name) != m_Shaders.end(), "Shader not found!");
		return m_Shaders[name];
	}

}