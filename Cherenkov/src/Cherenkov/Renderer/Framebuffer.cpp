#include "ckpch.h"
#include "Cherenkov/Renderer/Framebuffer.h"
#include "Cherenkov/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLFramebuffer.h"

namespace Cherenkov {
    Ref<Framebuffer> Framebuffer::init(const Specification spec) {
		switch (Renderer::getAPI()){
		case RendererAPI::API::None:	CK_CORE_ASSERT(false, "RendererAPI::None not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:	return CreateRef<OpenGLFramebuffer>(spec);
		default:						CK_CORE_ASSERT(false, "Unknown RendererAPI"); return nullptr;
		}
    }
}