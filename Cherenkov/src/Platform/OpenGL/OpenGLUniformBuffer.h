#pragma once

#include "Cherenkov/Renderer/UniformBuffer.h"

namespace Cherenkov {
	
	class OpenGLUniformBuffer : public UniformBuffer {
		uint32_t m_RendererID;

	public:
		OpenGLUniformBuffer(uint32_t size, uint32_t binding);
		virtual ~OpenGLUniformBuffer();

		virtual void setData(const void* data, uint32_t size, uint32_t offset) override;
	};
}
