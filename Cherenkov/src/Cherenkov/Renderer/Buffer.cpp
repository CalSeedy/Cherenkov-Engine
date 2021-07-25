#include "ckpch.h"
#include "Cherenkov/Renderer/Buffer.h"
#include "Cherenkov/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Cherenkov {

	Ref<VertexBuffer> VertexBuffer::init(float_t* vertices, uint32_t size) {
		switch (Renderer::getAPI()) {
		case RendererAPI::API::None:		return nullptr;
		case RendererAPI::API::OpenGL:		return CreateRef<OpenGLVertexBuffer>(vertices, size);
		default:
			CK_CORE_ASSERT(false, "Unknown Renderer!");
			return nullptr;
		}
	}

	Cherenkov::Ref<Cherenkov::VertexBuffer> VertexBuffer::init(uint32_t size) {
		switch (Renderer::getAPI()) {
		case RendererAPI::API::None:		return nullptr;
		case RendererAPI::API::OpenGL:		return CreateRef<OpenGLVertexBuffer>(size);
		default:
			CK_ASSERT(false, "Unknown Renderer!");
			return nullptr;
		}
	}

	Ref<IndexBuffer> IndexBuffer::init(uint32_t* indices, uint32_t count) {
		switch (Renderer::getAPI()) {
		case RendererAPI::API::None:		return nullptr;
		case RendererAPI::API::OpenGL:		return CreateRef<OpenGLIndexBuffer>(indices, count);
		default:
			CK_ASSERT(false, "Unknown Renderer!");
			return nullptr;
		}
	}

}