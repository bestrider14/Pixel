#include "pxpch.h"
#include "Texture.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Pixel
{
	Ref<Texture2D> Texture2D::Create(uint32_t p_Width, uint32_t p_Height)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: PX_CORE_ASSERT(false, "RendererAPI::None is curently not supported!") return nullptr;
		case RendererAPI::API::OpenGL: return CreateRef<OpenGLTexture2D>(p_Width, p_Height);
		}

		PX_CORE_ASSERT(false, "Unknow RendererAPI!");
		return nullptr;
	}

	Ref<Texture2D> Texture2D::Create(const std::string& p_Path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: PX_CORE_ASSERT(false, "RendererAPI::None is curently not supported!") return nullptr;
		case RendererAPI::API::OpenGL: return CreateRef<OpenGLTexture2D>(p_Path);
		}

		PX_CORE_ASSERT(false, "Unknow RendererAPI!");
		return nullptr;
	}
}// namespace Pixel