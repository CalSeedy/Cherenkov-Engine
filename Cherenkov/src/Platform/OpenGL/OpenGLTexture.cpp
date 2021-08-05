#include "ckpch.h"
#include "Platform/OpenGL/OpenGLTexture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace Cherenkov {
	OpenGLTexture2D::OpenGLTexture2D(const std::string& path) : m_Path{ path } {
		CK_PROFILE_FUNCTION();
		int width, height, channels;
		stbi_set_flip_vertically_on_load(true);
		stbi_uc* data = nullptr;
		{
			CK_PROFILE_SCOPE("Texture2D Load");
			data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		}
		char buff[256];
		sprintf_s(buff, sizeof(buff), "Failed to load Texture2D @ '%s'", path.c_str());
		CK_CORE_ASSERT(data, buff);
		m_Width = width;
		m_Height = height;

		switch (channels) {
		case 3:
			m_Format.InternalFormat = GL_RGB8;
			m_Format.GLFormat = GL_RGB;
			break;
		case 4:
			m_Format.InternalFormat = GL_RGBA8;
			m_Format.GLFormat = GL_RGBA;
			break;
		default:
			m_Format.InternalFormat = NULL;
			m_Format.GLFormat = NULL;
			break;
		}

		CK_CORE_ASSERT((m_Format.InternalFormat & m_Format.GLFormat), "Texture2D format not supported!");

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, m_Format.InternalFormat, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_Format.GLFormat, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}

	OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height) : m_Width{ width }, m_Height{ height } {
		CK_PROFILE_FUNCTION();
		m_Format.InternalFormat = GL_RGBA8;
		m_Format.GLFormat = GL_RGBA;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, m_Format.InternalFormat, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);

	}

	OpenGLTexture2D::~OpenGLTexture2D() {
		CK_PROFILE_FUNCTION();
		glDeleteTextures(1, &m_RendererID);
	}

	void OpenGLTexture2D::bind(uint32_t slot) const {
		CK_PROFILE_FUNCTION();
		glBindTextureUnit(slot, m_RendererID);
	}

	void OpenGLTexture2D::setData(void* data, uint32_t size) {
		CK_PROFILE_FUNCTION();
		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_Format.GLFormat, GL_UNSIGNED_BYTE, data);
	}

}
