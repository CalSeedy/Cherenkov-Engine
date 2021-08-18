#pragma once
#include "Cherenkov/Renderer/Framebuffer.h"


namespace Cherenkov {
	
	class OpenGLFramebuffer : public Framebuffer {
		FbSpecification m_Specification;
		uint32_t m_RendererID = 0;
		
		std::vector<uint32_t> m_ColourAttachments;
		uint32_t m_DepthAttachment = 0;

		std::vector<FbTextureSpecification> m_ColourAttachmentSpecifications;
		FbTextureSpecification m_DepthAttachmentSpecification = FbTextureFormat::None;
	public:
		OpenGLFramebuffer(const FbSpecification& spec);
		virtual ~OpenGLFramebuffer();

		void recreate();
		void resize(uint32_t width, uint32_t height) override;
		void bind() override;
		void unbind() override;

		void clearColourAttachment(uint32_t idx, int data) override;
		const FbSpecification& getSpecification() const { return m_Specification; }
		uint32_t getColourAttachment(uint32_t ind = 0) const override { CK_CORE_ASSERT(ind < m_ColourAttachments.size()); return m_ColourAttachments[ind]; }
		int readPixel(uint32_t attachmentID, int x, int y) override;
	};
}
