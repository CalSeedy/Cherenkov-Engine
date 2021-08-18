#include "ckpch.h"
#include "Platform/OpenGL/OpenGLFramebuffer.h"

#include <glad/glad.h>

namespace Cherenkov {

	static const uint32_t s_MaxFramebufferSize = 8192;

	namespace Utils {
		static bool isDepthFormat(FbTextureFormat format) {
			switch (format) {
			case Cherenkov::FbTextureFormat::DEPTH24STENCIL8:	return true;
			default:											return false;
			}
		}

		static GLenum textureTarget(bool multi) {
			return multi ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;
		}

		static void createTextures(bool multi, uint32_t* ID, uint32_t count) {
			glCreateTextures(textureTarget(multi), count, ID);
		}

		static void bindTexture(bool multi, uint32_t ID) {
			glBindTexture(textureTarget(multi), ID);
		}

		static void attachColourTexture(uint32_t ID, int samples, GLenum internalFormat, GLenum accessFormat, uint32_t width, uint32_t height, int index) {
			bool multi = samples > 1;

			if (multi) glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, internalFormat, width, height, GL_FALSE);
			else { 
				glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, accessFormat, GL_UNSIGNED_BYTE, nullptr);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			}
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, textureTarget(multi), ID, 0);
		}

		static void attachDepthTexture(uint32_t ID, int samples, GLenum format, GLenum attachmentType, uint32_t width, uint32_t height) {
			bool multi = samples > 1;

			if (multi) glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, format, width, height, GL_FALSE);
			else {
				glTexStorage2D(GL_TEXTURE_2D, 1, format, width, height);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			}
			glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentType, textureTarget(multi), ID, 0);
		}

		static GLenum CKtoGLFormatConversion(FbTextureFormat& format) {
			switch (format)	{
			case FbTextureFormat::RED_INT:	return GL_RED_INTEGER;
			case FbTextureFormat::RGBA8:	return GL_RGBA8;
			default:						CK_CORE_ASSERT(false, "Unknown colour format for conversion!"); return GL_NONE;
			}
		}
	}

	OpenGLFramebuffer::OpenGLFramebuffer(const FbSpecification& spec) : m_Specification{ spec } {
		bool hasDepth = false;
		for (auto format : m_Specification.Attachments.Attachments) {
			if (!Utils::isDepthFormat(format.TextureFormat)) m_ColourAttachmentSpecifications.emplace_back(format);
			else {
				if (!hasDepth)
					m_DepthAttachmentSpecification = format;
				else
					CK_CORE_ASSERT(false, "Depth buffer already set!");
			}

		}
		 
		recreate();
	}


	OpenGLFramebuffer::~OpenGLFramebuffer()	{
		glDeleteFramebuffers(1, &m_RendererID);
		glDeleteTextures((GLsizei)m_ColourAttachments.size(), m_ColourAttachments.data());
		glDeleteTextures(1, &m_DepthAttachment);
	}

	void OpenGLFramebuffer::recreate() {

		if (m_RendererID) {
			glDeleteFramebuffers(1, &m_RendererID);
			glDeleteTextures((GLsizei)m_ColourAttachments.size(), m_ColourAttachments.data());
			glDeleteTextures(1, &m_DepthAttachment);

			m_ColourAttachments.clear();
			m_DepthAttachment = 0;
		}

		glCreateFramebuffers(1, &m_RendererID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
		
		bool multi = m_Specification.Samples > 1;

		if (m_ColourAttachmentSpecifications.size()) {
			m_ColourAttachments.resize(m_ColourAttachmentSpecifications.size());
			Utils::createTextures(multi, m_ColourAttachments.data(), (GLsizei)m_ColourAttachments.size());
			for (size_t i = 0; i < m_ColourAttachments.size(); i++) {
				Utils::bindTexture(multi, m_ColourAttachments[i]);
				switch (m_ColourAttachmentSpecifications[i].TextureFormat) {
				case FbTextureFormat::RGBA8:
					Utils::attachColourTexture(m_ColourAttachments[i], m_Specification.Samples, GL_RGBA8, GL_RGBA, m_Specification.Width, m_Specification.Height, (int)i);
					break;
				case FbTextureFormat::RED_INT:
					Utils::attachColourTexture(m_ColourAttachments[i], m_Specification.Samples, GL_R32I, GL_RED_INTEGER, m_Specification.Width, m_Specification.Height, (int)i);
					break;
				}
			}
		}

		if (m_DepthAttachmentSpecification.TextureFormat != FbTextureFormat::None) {
			Utils::createTextures(multi, &m_DepthAttachment, 1);
			Utils::bindTexture(multi, m_DepthAttachment);
			switch (m_DepthAttachmentSpecification.TextureFormat) {
			case FbTextureFormat::DEPTH24STENCIL8:
				Utils::attachDepthTexture(m_DepthAttachment, m_Specification.Samples, GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT, m_Specification.Width, m_Specification.Height);
				break;
			}
		}

		size_t numOfColourAttachments = m_ColourAttachments.size();
		if ( numOfColourAttachments > 1) {
			
			CK_CORE_ASSERT(numOfColourAttachments <= 4);
			GLenum buffers[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
			glDrawBuffers((GLsizei)numOfColourAttachments, buffers);
		}
		else if (m_ColourAttachments.empty()){
			glDrawBuffer(GL_NONE);
		}

		CK_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer incomplete!");

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFramebuffer::resize(uint32_t width, uint32_t height) {
		if (width == 0 || height == 0 || width > s_MaxFramebufferSize || height > s_MaxFramebufferSize)
		{
			CK_CORE_WARN("Attempted to rezize framebuffer to {0}, {1}", width, height);
			return;
		}
		m_Specification.Width = width;
		m_Specification.Height = height;
		recreate();
	}

	void OpenGLFramebuffer::bind() {
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
		glViewport(0, 0, m_Specification.Width, m_Specification.Height);
	}

	void OpenGLFramebuffer::unbind() {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFramebuffer::clearColourAttachment(uint32_t idx, int data) {
		glClearTexImage(m_ColourAttachments[idx], 0, Utils::CKtoGLFormatConversion(m_ColourAttachmentSpecifications[idx].TextureFormat), GL_INT, &data);
	}

	int OpenGLFramebuffer::readPixel(uint32_t attachmentID, int x, int y) {
		glReadBuffer(GL_COLOR_ATTACHMENT0 + attachmentID);
		int value;
		glReadPixels(x, y, 1, 1, GL_RED_INTEGER, GL_INT, &value);

		return value;
	}

}
