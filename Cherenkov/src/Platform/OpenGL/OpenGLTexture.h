#pragma once
#include "Cherenkov/Renderer/Texture.h"

#include <glad/glad.h>

namespace Cherenkov {
	

	class OpenGLTexture2D : public Texture2D {
		uint32_t	m_Height;
		std::string	m_Path;
		uint32_t	m_RendererID;
		uint32_t	m_Width;
		
		struct { 
			GLenum	GLFormat;
			GLenum	InternalFormat;
		} m_Format;

	public:
		OpenGLTexture2D(const std::string& path);
		OpenGLTexture2D(uint32_t width, uint32_t height);
		virtual ~OpenGLTexture2D();

		virtual void bind(uint32_t slot = 0) const override;

		virtual uint32_t height() const override { return m_Height; }
		virtual uint32_t width() const override { return m_Width; }

		void setData(void* data, uint32_t size) override;

		virtual bool operator==(const Texture& other) const override { return m_RendererID == ((OpenGLTexture2D&)other).m_RendererID; }
	};
}