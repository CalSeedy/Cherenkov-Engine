#include "ckpch.h"
#include "VertexArray.h"

#include "Cherenkov/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Cherenkov {

	Ref<VertexArray> VertexArray::init() {
		switch (Renderer::getAPI()) {
		case RendererAPI::API::None:		return nullptr;
		case RendererAPI::API::OpenGL:		return CreateRef<OpenGLVertexArray>();
		default:
			CK_CORE_ASSERT(false, "Unknown Renderer!");
			return nullptr;
		}
	
	}
}