#include "ckpch.h"
#include "VertexArray.h"

#include "Cherenkov/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Cherenkov {

	VertexArray* VertexArray::init() {
		switch (Renderer::getAPI()) {
		case RendererAPI::None:			return nullptr;
		case RendererAPI::OpenGL:		return new OpenGLVertexArray();
		default:
			CK_CORE_ASSERT(false, "Unknown Renderer!");
			return nullptr;
		}
	
	}
}