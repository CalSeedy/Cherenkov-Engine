#include "ckpch.h"
#include "Buffer.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Cherenkov {

	void VertexBuffer::loadData(std::vector<float> data) {
		m_Data = data;
	}

	VertexBuffer* VertexBuffer::init(float_t* vertices, uint32_t count) {
		switch (Renderer::getAPI()) {
		case RendererAPI::None:			return nullptr;
		case RendererAPI::OpenGL:		return new OpenGLVertexBuffer(vertices, count);
		default:
			CK_CORE_ASSERT(false, "Unknown Renderer!");
			return nullptr;
		}
	}

	IndexBuffer* IndexBuffer::init(uint32_t* indices, uint32_t count) {
		switch (Renderer::getAPI()) {
		case RendererAPI::None:			return nullptr;
		case RendererAPI::OpenGL:		return new OpenGLIndexBuffer(indices, count);
		default:
			CK_ASSERT(false, "Unknown Renderer!");
			return nullptr;
		}
	}

	void IndexBuffer::loadData(std::vector<unsigned int> data) {
		m_Data = data;
	}


}