#pragma once
#include "Cherenkov/Renderer/Buffer.h"

namespace Cherenkov {
	
	class OpenGLVertexBuffer : public VertexBuffer {
		uint32_t m_RendererID;
	public:
		OpenGLVertexBuffer(float_t* vertices, uint32_t count);
		virtual ~OpenGLVertexBuffer();

		virtual void bind() const;
		virtual void unbind() const;
	};

	class OpenGLIndexBuffer : public IndexBuffer {
		uint32_t m_Count;
		uint32_t m_RendererID;
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer();

		virtual void bind() const;
		virtual void unbind() const;
		virtual uint32_t count() const { return m_Count; }
	};
}