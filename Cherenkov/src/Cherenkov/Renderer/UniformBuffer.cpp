#include "ckpch.h"
#include "Cherenkov/Renderer/UniformBuffer.h"

#include "Cherenkov/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLUniformBuffer.h"

namespace Cherenkov {
	
	Ref<UniformBuffer> UniformBuffer::init(uint32_t size, uint32_t binding) {
		switch (Renderer::getAPI())	{
		case RendererAPI::API::None:	CK_CORE_ASSERT(false, "RendererAPI::None not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:	return CreateRef<OpenGLUniformBuffer>(size, binding);
		default:						CK_CORE_ASSERT(false, "Unknown RendererAPI"); return nullptr;
		}
	}
}
