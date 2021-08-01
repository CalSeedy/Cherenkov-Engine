#pragma once
#include "Cherenkov/Renderer/Framebuffer.h"


namespace Cherenkov {
	
	class OpenGLFramebuffer : public Framebuffer {
		FbSpecification m_Specification;
		uint32_t m_RendererID = 0;
		uint32_t m_ColourAttachment = 0;
		uint32_t m_DepthAttachment = 0;
	public:
		OpenGLFramebuffer(const FbSpecification& spec);
		virtual ~OpenGLFramebuffer();

		void recreate();
		void resize(uint32_t width, uint32_t height) override;
		void bind() override;
		void unbind() override;
		const FbSpecification& getSpecification() const { return m_Specification; }
		const uint32_t& getColourAttachment() const { return m_ColourAttachment; }
	};
}