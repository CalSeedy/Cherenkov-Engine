#pragma once

#include "Cherenkov/Renderer/Buffer.h"

namespace Cherenkov {
	class VertexArray {
	public:
		virtual void bind()	const = 0;
		virtual void unbind() const = 0;
		virtual void addVertexBuffer(const Ref<VertexBuffer>& vBuffer) = 0;
		virtual void setIndexBuffer(const Ref<IndexBuffer>& iBuffer) = 0;

		virtual const std::vector<Ref<VertexBuffer>>& getVertexBuffers() const = 0;
		virtual const Ref<IndexBuffer>& getIndexBuffer() const = 0;

		static VertexArray* init();

		virtual ~VertexArray() = default;
	};
}