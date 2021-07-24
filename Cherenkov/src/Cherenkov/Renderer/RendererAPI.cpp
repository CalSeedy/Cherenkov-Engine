#include "ckpch.h"
#include "RendererAPI.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Cherenkov {
	RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

	Scope<RendererAPI> RendererAPI::Create() {
		switch (s_API){
		case RendererAPI::API::None:	CK_CORE_ASSERT(false, "RendererAPI::API::None is not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:	return CreateScope<OpenGLRendererAPI>();
		default:						CK_CORE_ASSERT(false, "Unknown RendererAPI!"); return nullptr;
		}
	}
}