#pragma once
#include "Cherenkov/Renderer/VertexArray.h"

namespace Cherenkov {

	class OpenGLVertexArray : public VertexArray {
		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
		Ref<IndexBuffer> m_IndexBuffer;
		uint32_t m_RendererID;
	public:
		OpenGLVertexArray();
		virtual void bind()	const override;
		virtual void unbind() const override;
		virtual void addVertexBuffer(const Ref<VertexBuffer>& vBuffer) override;
		virtual void setIndexBuffer(const Ref<IndexBuffer>& iBuffer) override;

		virtual const std::vector<Ref<VertexBuffer>>& getVertexBuffers() const override { return m_VertexBuffers; }
		virtual const Ref<IndexBuffer>& getIndexBuffer() const override { return m_IndexBuffer; }

		virtual ~OpenGLVertexArray();

	};

}