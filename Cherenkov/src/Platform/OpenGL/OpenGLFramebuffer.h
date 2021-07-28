#pragma once
#include "Cherenkov/Renderer/Framebuffer.h"


namespace Cherenkov {
	
	class OpenGLFramebuffer : public Framebuffer {
		Specification m_Specification;
		uint32_t m_RendererID;
		uint32_t m_ColourAttachment;
		uint32_t m_DepthAttachment;
	public:
		OpenGLFramebuffer(const Specification& spec);
		virtual ~OpenGLFramebuffer();

		void recreate();
		void bind() override;
		void unbind() override;
		const Specification& getSpecification() const { return m_Specification; }
		const uint32_t& getColourAttachment() const { return m_ColourAttachment; }
	};
}