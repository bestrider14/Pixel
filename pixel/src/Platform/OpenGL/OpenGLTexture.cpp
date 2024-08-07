#include "pxpch.h"
#include "OpenGLTexture.h"

#include "stb_image.h"

namespace Pixel
{
	OpenGLTexture2D::OpenGLTexture2D(uint32_t p_Width, uint32_t p_Height)
		: m_Width(p_Width), m_Height(p_Height)
	{
		PX_PROFILE_FUNCTION();
		
		m_InternalFormat = GL_RGBA8;
		m_DataFormat = GL_RGBA;
		
		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	OpenGLTexture2D::OpenGLTexture2D(const std::string& p_Path)
		: m_Path(p_Path), m_Width(0), m_Height(0), m_RendererID(0)
	{
		PX_PROFILE_FUNCTION();
		
		int width, height, channels;
		stbi_set_flip_vertically_on_load(true);

		stbi_uc* data = nullptr;
		{
			PX_PROFILE_SCOPE("stbi_load - OpenGLTexture2D::OpenGLTexture2D(const std::string&)");
			data = stbi_load(p_Path.c_str(), &width, &height, &channels, 0);
		}

		PX_CORE_ASSERT(data, "Failed to load image!");
		m_Width = width;
		m_Height = height;

		GLenum internalFormat = 0, dataFormat = 0;
		if (channels == 4)
		{
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}
		else if (channels == 3)
		{
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}

		m_InternalFormat = internalFormat;
		m_DataFormat = dataFormat;
	
		PX_CORE_ASSERT(internalFormat & dataFormat, "Format not supported!");

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER,  GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER,  GL_NEAREST);

		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		PX_PROFILE_FUNCTION();
		
		glDeleteTextures(1, &m_RendererID);
	}

	void OpenGLTexture2D::SetData(void* p_Data, uint32_t p_Size)
	{
		PX_PROFILE_FUNCTION();
		
		uint32_t bpp = m_DataFormat == GL_RGBA ? 4 : 3;
		PX_CORE_ASSERT(p_Size == m_Width * m_Height * bpp, "Data must be entire Texture!")
		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, p_Data);
	}

	void OpenGLTexture2D::Bind(uint32_t p_Slot) const
	{
		PX_PROFILE_FUNCTION();
		
		glBindTextureUnit(p_Slot, m_RendererID);
	}
}// namespace Pixel