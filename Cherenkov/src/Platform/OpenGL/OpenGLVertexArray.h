#pragma once
#include "Cherenkov/Renderer/VertexArray.h"

namespace Cherenkov {

	class OpenGLVertexArray : public VertexArray {
		std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
		uint32_t m_RendererID;
	public:
		OpenGLVertexArray();
		virtual void bind()	const override;
		virtual void unbind() const override;
		virtual void addVertexBuffer(const std::shared_ptr<VertexBuffer>& vBuffer) override;
		virtual void setIndexBuffer(const std::shared_ptr<IndexBuffer>& iBuffer) override;

		virtual const std::vector<std::shared_ptr<VertexBuffer>>& getVertexBuffers() const override { return m_VertexBuffers; }
		virtual const std::shared_ptr<IndexBuffer>& getIndexBuffer() const override { return m_IndexBuffer; }

		virtual ~OpenGLVertexArray();

	};

}