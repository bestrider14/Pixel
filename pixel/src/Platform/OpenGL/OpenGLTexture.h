#pragma once

#include <glad/glad.h>

#include "Pixel/Renderer/Texture.h"

namespace Pixel
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(uint32_t p_Width, uint32_t p_Height);
		OpenGLTexture2D(const std::string& p_Path);
		virtual ~OpenGLTexture2D();

		virtual uint32_t getWidth() const override { return m_Width; }
		virtual uint32_t getHeight() const override { return m_Height; }

		virtual void SetData(void* p_Data, uint32_t p_Size) override;

		virtual void Bind(uint32_t p_Slot = 0) const override;
	private:
		std::string m_Path;
		uint32_t m_Width, m_Height;
		uint32_t m_RendererID;
		GLenum m_InternalFormat, m_DataFormat;
	};
}// namespace Pixel