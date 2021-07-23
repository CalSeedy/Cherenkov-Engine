#pragma once
#include "Cherenkov/Renderer/Buffer.h"

namespace Cherenkov {
	
	class OpenGLVertexBuffer : public VertexBuffer {
		uint32_t m_RendererID;
		BufferLayout m_Layout;
	public:
		OpenGLVertexBuffer(float_t* vertices, uint32_t count);
		virtual ~OpenGLVertexBuffer();

		virtual void bind() const override;
		virtual void unbind() const override;

		virtual const BufferLayout& getLayout() const override { return m_Layout; }
		virtual void setLayout(const BufferLayout& layout) override { m_Layout = layout; }
	};

	class OpenGLIndexBuffer : public IndexBuffer {
		uint32_t m_Count;
		uint32_t m_RendererID;
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer();

		virtual void bind() const override;
		virtual void unbind() const override;
		virtual uint32_t count() const { return m_Count; }
	};
}