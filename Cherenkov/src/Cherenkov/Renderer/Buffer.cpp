#include "ckpch.h"
#include "Cherenkov/Renderer/Buffer.h"
#include "Cherenkov/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Cherenkov {

	void VertexBuffer::loadData(std::vector<float> data) {
		m_Data = data;
	}

	Ref<VertexBuffer> VertexBuffer::init(float_t* vertices, uint32_t count) {
		switch (Renderer::getAPI()) {
		case RendererAPI::API::None:		return nullptr;
		case RendererAPI::API::OpenGL:		return CreateRef<OpenGLVertexBuffer>(vertices, count);
		default:
			CK_CORE_ASSERT(false, "Unknown Renderer!");
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

	void IndexBuffer::loadData(std::vector<unsigned int> data) {
		m_Data = data;
	}


}