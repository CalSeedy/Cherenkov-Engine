#include "ckpch.h"
#include "Texture.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLTexture.h"

namespace Cherenkov {
    Ref<Texture2D> Texture2D::init(const std::string& path)
    {
		switch (Renderer::getAPI()) {
		case RendererAPI::API::None:		return nullptr;
		case RendererAPI::API::OpenGL:		return CreateRef<OpenGLTexture2D>(path);
		default:
			CK_CORE_ASSERT(false, "Unknown Renderer!");
			return nullptr;
		}
    }

	Ref<Texture2D> Texture2D::init(uint32_t width, uint32_t height) {
		switch (Renderer::getAPI()) {
		case RendererAPI::API::None:		return nullptr;
		case RendererAPI::API::OpenGL:		return CreateRef<OpenGLTexture2D>(width, height);
		default:
			CK_CORE_ASSERT(false, "Unknown Renderer!");
			return nullptr;
		}
	}

}