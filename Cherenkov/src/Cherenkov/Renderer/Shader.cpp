#include "ckpch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Cherenkov {
	
	Shader* Shader::init(const char* vertexPath, const char* fragmentPath) {
		switch (Renderer::getAPI()) {
		case RendererAPI::API::None:		return nullptr;
		case RendererAPI::API::OpenGL:		return new OpenGLShader(vertexPath, fragmentPath);
		default:
			CK_CORE_ASSERT(false, "Unknown Renderer!");
			return nullptr;
		}

	}

}