#pragma once
#include "Cherenkov/Renderer/Texture.h"

namespace Cherenkov {
	

	class OpenGLTexture2D : public Texture2D {
		uint32_t	m_Height;
		std::string	m_Path;
		uint32_t	m_RendererID;
		uint32_t	m_Width;
	public:
		OpenGLTexture2D(const std::string& path);
		virtual ~OpenGLTexture2D();
		virtual void bind(uint32_t slot = 0) const override;

		virtual uint32_t height() const override { return m_Height; }
		virtual uint32_t width() const override { return m_Width; }


	};
}