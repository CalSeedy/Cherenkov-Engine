#include "ckpch.h"
#include "OpenGLTexture.h"

#include <glad/glad.h>
#include <stb_image.h>
namespace Cherenkov {
	OpenGLTexture2D::OpenGLTexture2D(const std::string& path) : m_Path{ path } {
		int width, height, channels;
		stbi_set_flip_vertically_on_load(true);
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		CK_CORE_ASSERT(data, "Failed to load Texture2D @ {0}", path.c_str());
		m_Width = width;
		m_Height = height;

		GLenum internalFormat = 0, glFormat = 0;

		switch (channels) {
		case 3:
			internalFormat = GL_RGB8;
			glFormat = GL_RGB;
			break;
		case 4:
			internalFormat = GL_RGBA8;
			glFormat = GL_RGBA;
			break;
		default:
			break;
		}

		CK_CORE_ASSERT((internalFormat & glFormat), "Texture2D format not supported!");

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, glFormat, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}

	OpenGLTexture2D::~OpenGLTexture2D()	{
		glDeleteTextures(1, &m_RendererID);
	}

	void OpenGLTexture2D::bind(uint32_t slot) const {
		glBindTextureUnit(slot, m_RendererID);
	}
}