#include "ckpch.h"
#include "RendererContext.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLContext.h"

namespace Cherenkov {

	Scope<RendererContext> RendererContext::create(void* window) {
		switch (Renderer::getAPI()){
		case RendererAPI::API::None:	CK_CORE_ASSERT(false, "None type RendererAPI not supported."); return nullptr;
		case RendererAPI::API::OpenGL:	return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
		default:						CK_CORE_ASSERT(false, "Unknown RendererAPI."); return nullptr;
		}
	}
}